#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#define MAXACCOUNT 20
#define BACKLOG 20
#define ERR_EXIT(a) { perror(a); exit(1); }

typedef struct {
    char hostname[512];
    unsigned short port;
    int listen_fd;
} server;

typedef struct {
    char host[512];
    int conn_fd;
    char buf[512];
    size_t buf_len;
    int item;
    int wait_for_write;
} request;

typedef struct {
    int id;
    int balance;
} Account;

server svr;
request *requestP = NULL;
Account *accounts = NULL;
int accounts_fd, locked_id;
#ifndef READ_SERVER
int islocked[MAXACCOUNT + 1] = {};
#endif

void fetch() {
    FILE *fp = fopen("./account_list", "r");
    int rv, i, ret;
    i = 0;
    for (; i < MAXACCOUNT * 2; ++i) {
        rv = fread(&ret, sizeof(int), 1, fp);
        if (i & 1)
            accounts[i / 2 + 1].balance = ret;
        else
            accounts[i / 2 + 1].id = ret;
        if (rv != 1)
            break;
    }
    fclose(fp);
}

void update_database(int accounts_fd) {
    lseek(accounts_fd, 0, SEEK_SET);
    write(accounts_fd, &accounts[1], sizeof(Account) * MAXACCOUNT);
}

static void init_request(request *reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
    reqP->item = 0;
    reqP->wait_for_write = 0;
}

static void free_request(request *reqP) {
    init_request(reqP);
}

static void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void init_server(unsigned short port) {
    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;
    char PORT[12];
    sprintf(PORT, "%hu", port);

    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int rv;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "server: %s\n", gai_strerror(rv));
        exit(1);
    }
    for (p = ai; p != NULL; p = p->ai_next) {
        svr.listen_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (svr.listen_fd < 0) {
            continue;
        }

        int yes = 1;
        setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(svr.listen_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(svr.listen_fd);
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    freeaddrinfo(ai);
    if (listen(svr.listen_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
}

static void init_table(int *max_dtable_size) {
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

    accounts = (Account*) malloc(sizeof(Account) * (MAXACCOUNT + 1));
    fetch();
}

static int handle_read(request* reqP) {
    int r;
    char buf[512];

    // Read in request from client
    r = read(reqP->conn_fd, buf, sizeof(buf));
    if (r < 0) return -1;
    if (r == 0) return 0;
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
#ifdef READ_SERVER
static int check_read(int fd) {
    char tmp[512];
    int query_id = (int)strtol(requestP[fd].buf, NULL, 10);
    struct flock lock;

    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (query_id - 1) * sizeof(Account);
    lock.l_len = sizeof(Account);

    if (fcntl(accounts_fd, F_GETLK, &lock) == -1)
        ERR_EXIT("fcntl");
    
    if (lock.l_type == F_UNLCK) {
        lock.l_type = F_RDLCK;
        if (fcntl(accounts_fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("fcntl");
        requestP[fd].item = query_id;
        fetch();
        sprintf(tmp, "%d %d\n", accounts[query_id].id, accounts[query_id].balance);
        write(fd, tmp, strlen(tmp));
        return 0;
    }
    return -1;
}
#else
static int check_write(int fd) {
    char tmp[512];
    int query_id = (int)strtol(requestP[fd].buf, NULL, 10);
    struct flock lock;

    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (query_id - 1) * sizeof(Account);
    lock.l_len = sizeof(Account);

    if (fcntl(accounts_fd, F_GETLK, &lock) == -1)
        ERR_EXIT("fcntl");
   
    if ((islocked[query_id] == 0) && (lock.l_type == F_UNLCK)) {
        lock.l_type = F_WRLCK;
        if (fcntl(accounts_fd, F_SETLKW, &lock) == -1)
            ERR_EXIT("fcntl");

        islocked[query_id] = 1;
        requestP[fd].item = query_id;
        requestP[fd].wait_for_write = 1;
        sprintf(tmp, "This account is modifiable\n");
        write(fd, tmp, strlen(tmp));
        return 0;
    }
    return -1;
}

static int serve_write(int fd) {
    char cmd[512], *ptr;
    int id, amount;
    
    if (strstr(requestP[fd].buf, "transfer") != NULL) {
        sscanf(requestP[fd].buf, "%s %d %d", cmd, &id, &amount);
        if ((amount > accounts[requestP[fd].item].balance) || (amount < 0))
            return -1;
        accounts[requestP[fd].item].balance -= amount;
        accounts[id].balance += amount;
        update_database(accounts_fd);
    }
    else {
        sscanf(requestP[fd].buf, "%s %d", cmd, &amount);
        if (!strcmp(cmd, "save")) {
            if (amount < 0)
                return -1;
            accounts[requestP[fd].item].balance += amount;
        }
        else if (!strcmp(cmd, "withdraw")) {
            if ((amount > accounts[requestP[fd].item].balance) || (amount < 0))
                return -1;
            accounts[requestP[fd].item].balance -= amount;
        }
        update_database(accounts_fd); 
    }
    return 0;
}
#endif
void unlock(int query_id) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (query_id - 1) * sizeof(Account);
    lock.l_len = sizeof(Account);
    if (fcntl(accounts_fd, F_SETLKW, &lock) == -1)
        ERR_EXIT("fcntl");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    fd_set master, read_fds;
    int fdmax, max_dtable_size, newfd, nbytes, res;
    socklen_t addrlen;
    struct sockaddr_storage remoteaddr;
    char buf[512], tmp[512], remoteIP[INET_ADDRSTRLEN];

    init_server((unsigned short) atoi(argv[1]));
    init_table(&max_dtable_size);
    accounts_fd = openat(AT_FDCWD, "./account_list", O_RDWR);

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(svr.listen_fd, &master);
    fdmax = svr.listen_fd;
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", 
            svr.hostname, svr.port, svr.listen_fd, max_dtable_size);
    
    int i, j;
    for (;;) {
        read_fds = master;
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
            ERR_EXIT("select");
        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                // handle new connection
                if (i == svr.listen_fd) { 
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(svr.listen_fd, (struct sockaddr *)&remoteaddr, &addrlen);
                    if (newfd < 0) {
                        if (errno == EINTR || errno == EAGAIN) continue;
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
                                  remoteIP, INET_ADDRSTRLEN);
                        requestP[newfd].conn_fd = newfd;
                        strcpy(requestP[newfd].host, remoteIP);

                        FD_SET(newfd, &master);
                        if (newfd > fdmax)
                            fdmax = newfd;
                        fprintf(stderr, "getting a new request... fd %d from %s\n", 
                                newfd, requestP[newfd].host);
                    }
                } 
                else {
                    // handle existing client
                    res = handle_read(&requestP[i]);
                    if (res < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[i].host);
                        continue;
                    }
                    if (FD_ISSET(i, &master)) {
#ifdef READ_SERVER
                        if ((res = check_read(i)) < 0) {
                            sprintf(tmp, "This account is locked.\n");
                            write(i, tmp, strlen(tmp));
                        }
                        else {
                            unlock(requestP[i].item);
                        }
#else
                        if (!requestP[i].wait_for_write) {
                            if ((res = check_write(i)) < 0) {
                                sprintf(tmp, "This account is locked.\n");
                                write(i, tmp, strlen(tmp));
                            }

                        }
                        else {     
                            if ((res = serve_write(i)) < 0) {
                                sprintf(tmp, "Operation failed.\n");
                                write(i, tmp, strlen(tmp));
                            }
                            unlock(requestP[i].item);
                            islocked[requestP[i].item] = 0;
                            requestP[i].wait_for_write = 0;
                        }
#endif              
                        if (!requestP[i].wait_for_write) {
                            close(i);
                            free_request(&requestP[i]);
                            FD_CLR(i, &master);  
                        }     
                    }         
                }
            }
        }
    }
    close(accounts_fd);
    free(requestP);
    free(accounts);
    return 0;
}