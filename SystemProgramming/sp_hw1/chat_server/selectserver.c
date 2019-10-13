/*
** selectserver.c -- 一個 cheezy 的多人聊天室 server
** send message to everyone
## usage ##
terminal_1: 
    gcc selectserver2.c -o selectserver
    ./selectserver
terminal_2 ~ terminal_11(connecting to the server):
    telnet localhost 9034
*/
#include<stdio.h> // fprintf
#include<stdlib.h> // exit
#include<string.h> // memset
#include<sys/time.h> // select
#include<unistd.h> // select
#include<sys/types.h> // addrinfo, getaddrinfo, socket, bind, connect, accept, select
                      // send, recv
#include<sys/socket.h> // addrinfo, getaddrinfo, socket, bind, connect, listen, accept
                       // socklen_t, sockaddr_storage, send, recv
#include<netinet/in.h> // Internet Protocol family: sa_family_t, in_addr_t, in_port_t...
#include<arpa/inet.h> // INET_ADDRSTRLEN, INET6_ADDRSTRLEN, inet_ntop
#include<netdb.h> // addrinfo, getaddrinfo, gai_strerror

#define MYPORT "9034" // 我們正在 listen 的 port

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;
server svr;

// 取得 pointer of sockaddr，IPv4 或 IPv6：
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// 給我們一個 socket，並且 bind 它
void init_server(unsigned short port) {
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
        exit(2);
    }
    freeaddrinfo(ai); // all done with this

    // int listen(int sockfd, int backlog);
    // backlog 是進入的佇列（incoming queue）中所允許的連線數目
    // 進入的連線將會在這個佇列中排隊等待，直到你 accept() 它們
    // 多數的系統預設將這個數值限制為 20
    if (listen(svr.listen_fd, 10) == -1) {
        perror("listen");
        exit(3);
    }
}

int main() {
    fd_set master; // master file descriptor 清單
    fd_set read_fds; // 給 select() 用的暫時 file descriptor 清單
    int fdmax; // 最大的 file descriptor 數目

    int newfd; // 新接受的 accept() socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256]; // 儲存 client 資料的緩衝區
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN]; // save IP string of remoteaddr after inet_ntop()

    int i, j;

    FD_ZERO(&master); // 清除 master 與 temp sets
    FD_ZERO(&read_fds);

    init_server((unsigned short) atoi(MYPORT));

    // 將 listener 新增到 master set
    FD_SET(svr.listen_fd, &master);
    // 持續追蹤最大的 file descriptor
    fdmax = svr.listen_fd; // 到此為止，就是它了

    // 主要迴圈
    for (;;) {
        read_fds = master; // 複製 master

        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // 在現存的連線中尋找需要讀取的資料
        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // 我們找到一個！！
                if (i == svr.listen_fd) {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(svr.listen_fd, (struct sockaddr *)&remoteaddr, &addrlen);
                    if (newfd == -1) {
                        perror("accept");
                    }
                    else {
                        FD_SET(newfd, &master); // 新增到 master set
                        if (newfd > fdmax) // 持續追蹤最大的 fd
                            fdmax = newfd;
                        // inet_ntop returns converted ip string (char*)
                        // here, it is ::1 (127.0.0.1 ipv6的形式)
                        printf("selectserver: new connection from %s on socket %d\n",
                                inet_ntop(remoteaddr.ss_family, 
                                          get_in_addr((struct sockaddr*)&remoteaddr),
                                                       remoteIP, INET6_ADDRSTRLEN),
                                newfd);
                    }
                } 
                else {
                    // 處理來自 client 的資料
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // 關閉連線
                            printf("selectserver: socket %d hung up\n", i);
                        } 
                        else perror("recv");
                        close(i); // bye!
                        FD_CLR(i, &master); // 從 master set 中移除
                    } 
                    else {
                        // 我們從 client 收到一些資料
                        for (j = 0; j <= fdmax; j++) {
                            // 送給大家！
                            if (FD_ISSET(j, &master)) {
                                // 不用送給 listener 跟我們自己
                                if (j != svr.listen_fd && j != i)
                                    if (send(j, buf, nbytes, 0) == -1) perror("send");
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for( ; ; )--and you thought it would never end!
    return 0;
}