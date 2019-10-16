/*
** selectserver.c -- 一個 cheezy 的多人聊天室 server
** send message to everyone
## usage ##
terminal_1: 
    gcc selectserver.c -o selectserver
    ./selectserver 9034
terminal_2 ~ terminal_11(connecting to the server):
    telnet localhost 9034
*/
#include <stdio.h> // fprintf
#include <stdlib.h> // exit
#include <string.h> // memset
#include <errno.h>
#include <sys/time.h> // select
#include <unistd.h> // select, gethostname, getdtablesize
#include <sys/types.h> // addrinfo, getaddrinfo, socket, bind, connect, accept, select
                      // send, recv
#include <sys/socket.h> // addrinfo, getaddrinfo, socket, bind, connect, listen, accept
                       // socklen_t, sockaddr_storage, send, recv
#include <netinet/in.h> // Internet Protocol family: sa_family_t, in_addr_t, in_port_t...
#include <arpa/inet.h> // INET_ADDRSTRLEN, INET6_ADDRSTRLEN, inet_ntop
#include <netdb.h> // addrinfo, getaddrinfo, gai_strerror
#include <sys/wait.h>
#include <signal.h>
#define BACKLOG 10 // 有多少個特定的連線佇列（pending connections queue）
#define ERR_EXIT(a) { perror(a); exit(1); }

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;

typedef struct {
    char host[512];  // client's host
    int conn_fd;  // fd to talk with client
    char buf[512];  // data sent by/to client
    size_t buf_len;  // bytes used by buf
} request;

server svr;
request* requestP = NULL;  // point to a list of requests

static void init_request(request* reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
}

static void free_request(request* reqP) {
    init_request(reqP);
}

// 取得 pointer of sockaddr，IPv4 或 IPv6：
static void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// 給我們一個 socket，並且 bind 它
static void init_server(unsigned short port) {
    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;
    char PORT[12];
    sprintf(PORT, "%hu", port);

    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // 不用管是 IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;  // bind to any localhost IP

    // structure settings for afterward listening on PORT and IP address/url
    // if IP address/url is NULL and AI_PASSIVE is set, it means you are the server
    // and you want to execute listen on PORT of any localhost_IP
    // if you want a certain localhost_IP, 
    // 捨棄 AI_PASSIVE，並改放一個IP到 getaddrinfo() 的第一個參數
    // ai 指向一個或多個 struct addrinfo 的鏈結串列 where elements satisfy hints 
    int rv;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next) {
        // int socket(int domain, int type, int protocol); return a fd!
        // domain 是 PF_INET 或 PF_INET6，type 是 SOCK_STREAM 或 SOCK_DGRAM，
        // 而 protocol 可以設定為 0，用來幫給予的 type 選擇適當的協定。
        svr.listen_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (svr.listen_fd < 0) {
            continue;
        }

        // 避開這個錯誤訊息："address already in use"
        int yes = 1; // 供底下的 setsockopt() 設定 SO_REUSEADDR
        setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        // bind() is for for server
        // bind the socket to the port on localhost
        // int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
        // sockfd 是 socket() 傳回的 socket file descriptor。
        // my_addr 是指向包含你的位址資訊、名稱及 IP address 的 struct sockaddr 之指標。
        // addrlen 是以 byte 為單位的位址長度。
        if (bind(svr.listen_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(svr.listen_fd);
            continue;
        }
        break;
    }

    // 若我們進入這個判斷式，則表示我們 bind() 失敗
    if (p == NULL) {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(1);
    }
    freeaddrinfo(ai); // all done with this

    // int listen(int sockfd, int backlog);
    // backlog 是進入的佇列（incoming queue）中所允許的連線數目
    // 進入的連線將會在這個佇列中排隊等待，直到你 accept() 它們
    // 多數的系統預設將這個數值限制為 20
    if (listen(svr.listen_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
}

static void init_table(int *max_dtable_size) {
    // Get file descripter table size and initize request table
    *max_dtable_size = getdtablesize();
    requestP = (request*) malloc(sizeof(request) * (*max_dtable_size));
    if (requestP == NULL) {
        ERR_EXIT("out of memory allocating all requests");
    }
    for (int i = 0; i < *max_dtable_size; i++) {
        init_request(&requestP[i]);
    }
    requestP[svr.listen_fd].conn_fd = svr.listen_fd;
    strcpy(requestP[svr.listen_fd].host, svr.hostname);
}

static void sigchld_handler(int s) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

static void clean_process() {
    // 清理 zombie process（殭屍行程)
    // 當 parent process 所 fork() 出來的 child process 結束時
    // 且 parent process 沒有取得 child process 的離開狀態時，就會出現 zombie process
    struct sigaction sa;
    sa.sa_handler = sigchld_handler; // 收拾全部死掉的 processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

static int handle_read(request* reqP, char* buf) {
    char* p1 = strstr(buf, "\015\012");
    int newline_len = 2;
    // be careful that in Windows, line ends with \015\012
    if (p1 == NULL) {
        p1 = strstr(buf, "\012");
        newline_len = 1;
        if (p1 == NULL) {
            ERR_EXIT("this really should not happen...");
        }
    }
    size_t len = p1 - buf + 1;
    memmove(reqP->buf, buf, len);
    reqP->buf[len - 1] = '\0';
    reqP->buf_len = len - 1;
    return 1;
}

int main(int argc, char** argv) {
    // Parse args.
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    fd_set master; // master file descriptor 清單
    fd_set read_fds; // 給 select() 用的暫時 file descriptor 清單
    int fdmax; // 最大的 file descriptor 數目
    int max_dtable_size; // max file descripter table size

    int newfd; // 新接受的 accept() socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;
    char remoteIP[INET6_ADDRSTRLEN]; // save IP string of remoteaddr after inet_ntop()

    char buf[512]; // 儲存 client 資料的緩衝區
    char tmp[512];
    int nbytes;

    init_server((unsigned short) atoi(argv[1]));
    init_table(&max_dtable_size);
    clean_process();

    FD_ZERO(&master); // 清除 master 與 temp sets
    FD_ZERO(&read_fds);
    FD_SET(svr.listen_fd, &master); // 將 listener 新增到 master set
    fdmax = svr.listen_fd; // 持續追蹤最大的 file descriptor, 到此為止，就是它了
    
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", 
            svr.hostname, svr.port, svr.listen_fd, max_dtable_size);
    fprintf(stderr, "selectserver: waiting for connections...\n");
    
    // 主要迴圈
    int i, j;
    for (;;) {
        read_fds = master; // 複製 master

        // select() will return if:
        // 1. any event happens
        // 2. timeout (no event happens after a period of time)
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
            ERR_EXIT("select");

        // 在現存的連線(read_fds set)中尋找需要讀取的資料
        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // 我們找到一個！！
                if (i == svr.listen_fd) { // listen 的 socket 就緒可讀(有一個待處理的新連線)
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(svr.listen_fd, (struct sockaddr *)&remoteaddr, &addrlen);
                    if (newfd < 0) {
                        if (errno == EINTR || errno == EAGAIN) continue; // try again
                        if (errno == ENFILE) {
                            (void) fprintf(stderr, "out of file descriptor table ... (maxconn %d)\n", 
                                           max_dtable_size);
                            continue;
                        }
                        ERR_EXIT("accept")
                    }
                    else {
                        inet_ntop(remoteaddr.ss_family, 
                                  get_in_addr((struct sockaddr*)&remoteaddr),
                                  remoteIP, INET6_ADDRSTRLEN);
                        requestP[newfd].conn_fd = newfd;
                        strcpy(requestP[newfd].host, remoteIP);

                        FD_SET(newfd, &master); // 新增到 master set
                        if (newfd > fdmax) // 持續追蹤最大的 fd
                            fdmax = newfd;
                        // inet_ntop returns converted ip string (char*)
                        // here, it is ::1 (127.0.0.1 ipv6的形式)
                        fprintf(stderr, "selectserver: new connection from %s on socket %d\n",
                                requestP[newfd].host, newfd);
                    }
                } 
                else {
                    // 處理來自 client 的資料
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // 關閉連線
                            fprintf(stderr, "selectserver: socket %d hung up\n", i);
                        } 
                        else {
                            fprintf(stderr, "bad request from %s\n", requestP[i].host);
                            perror("recv");
                        }
                        close(i); // bye!
                        free_request(&requestP[i]);
                        FD_CLR(i, &master); // 從 master set 中移除
                    } 
                    else {
                        handle_read(&requestP[i], buf);
                        // 我們從 client 收到一些資料
                        for (j = 0; j <= fdmax; j++) {
                            // 送給大家！
                            if (FD_ISSET(j, &master)) {
                                if (j == i) {
                                    sprintf(tmp, "you send: %s, len = %zu\n", 
                                            requestP[i].buf, requestP[i].buf_len);
                                    /*
                                    if (write(requestP[i].conn_fd, tmp, strlen(tmp)) == -1)
                                        perror("write");
                                    */
                                    // When writing to a socket with write
                                    // it's same as calling send with the flags argument set to 0
                                    if (send(i, tmp, strlen(tmp), 0) == -1) 
                                        perror("send");
                                }
                                else if (j != svr.listen_fd) {
                                    sprintf(tmp, "%s\n", requestP[i].buf);
                                    if (send(j, tmp, strlen(tmp), 0) == -1) 
                                        perror("send");
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for( ; ; )--and you thought it would never end!
    free(requestP);
    return 0;
}