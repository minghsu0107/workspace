/*
** client.c -- 一個 stream socket client 的 demo, simulating telnet
## usage ##
    gcc client.c -o cli
    ./cli localhost 9034
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define STDIN 0
#define MAXDATASIZE 100 // 我們一次可以收到的最大位原組數（number of bytes）

static void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s [hostname] [port]\n", argv[0]);
        exit(1);
    }

    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    fd_set read_fds, master;
    int fdmax;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    fprintf(stderr, "Trying %s...\n", argv[1]);
    // 用迴圈取得全部的結果，並先連線到能成功連線的
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));
    fprintf(stderr, "Connected to %s\n", s);
    fprintf(stderr, "Escape character is '^]'.\n");
    freeaddrinfo(servinfo); // 全部皆以這個 structure 完成

    FD_ZERO(&read_fds);
    FD_SET(STDIN, &master);
    FD_SET(sockfd, &master);
    fdmax = sockfd;
    
    while(1) {
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }
        for (int i = 0; i <= fdmax; ++i) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == sockfd) {
                    if ((numbytes = recv(i, buf, MAXDATASIZE - 1, 0)) <= 0) {
                        if (numbytes == 0) {
                            // 關閉連線
                            fprintf(stderr, "Connection closed by foreign host.\n");
                        } 
                        else {
                            perror("recv");
                        }
                        exit(1);
                    }
                    else {
                        buf[numbytes] = '\0';
                        fprintf(stderr, "%s", buf);
                    }
                }
                else {
                    if ((numbytes = read(i, buf, MAXDATASIZE - 1)) == -1) {
                        perror("read");
                        exit(1);
                    }
                    else {
                        if (send(sockfd, buf, numbytes, 0) == -1) 
                            perror("send");
                    }   
                }
            }
        }
    }
    return 0;
}