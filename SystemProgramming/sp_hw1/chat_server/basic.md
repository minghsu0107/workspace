# Homework 1 note
###### tags: `system programming`
## Data structure-1
```C
struct sockaddr_in{
    sa_family_t     sin_family;   //地址族（Address Family），也就是地址类型, 2 bytes
    uint16_t        sin_port;     //16位的端口号, 2 bytes
    struct in_addr  sin_addr;     //32位IP地址, 4 bytes
    char            sin_zero[8];  //不使用，一般用0填充
};
struct in_addr{
    in_addr_t  s_addr;  //32位的IP地址(unsigned long, 4 bytes)
};
struct sockaddr{
    sa_family_t  sin_family;   //地址族（Address Family），也就是地址类型, 2 bytes
    char         sa_data[14];  //IP地址和端口号, 14 bytes
};
```
we use inet_ntop() [network to presentation] to transfer s_addr to IP string

sockaddr 和 sockaddr_in 的长度相同，都是16字节，只是将IP地址和端口号合并到一起，用一个成员 sa_data 表示。要想给 sa_data 赋值，必须同时指明IP地址和端口号，例如”127.0.0.1:80“，遗憾的是，没有相关函数将这个字符串转换成需要的形式，也就很难给 sockaddr 类型的变量赋值，所以使用 sockaddr_in 来代替。这两个结构体的长度相同，强制转换类型时不会丢失字节，也没有多余的字节。

```C
struct sockaddr_in6 { 
    sa_family_t sin6_family;  //(2)地址类型，取值为AF_INET6
    in_port_t sin6_port;  //(2)16位端口号
    uint32_t sin6_flowinfo;  //(4)IPv6流信息
    struct in6_addr sin6_addr;  //(4)具体的IPv6地址
    uint32_t sin6_scope_id;  //(4)接口范围ID
};
struct in6_addr {
    unsigned char s6_addr[16]; // IPv6 address
};
```

## Data structure-2
對於某些 calls，你有時無法事先知道它是否會使用 IPv4 或 IPv6 address 來填好你的 struct sockaddr。所以你用這個平行的 structure 來傳遞
```C
struct sockaddr_storage {
    sa_family_t ss_family; // address family
    // 這裡都是填充物（padding），依實作而定，請忽略它：
    char __ss_pad1[_SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[_SS_PAD2SIZE];
};
```
你可以在 ss_family 欄位看到位址家族（address family），檢查它是 AF_INET 或 AF_INET6（是 IPv4 或 IPv6）。之後如果你願意的話，你就可以將它轉型為 sockaddr_in 或 struct sockaddr_in6。

## IP String Transformation
transform IP string to numerical presentation
```C
struct sockaddr_in sa; // IPv4
struct sockaddr_in6 sa6; // IPv6
inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr)); // IPv4
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
```

## Note
### network byte order
```C
#include <netinet/in.h>

uint32_t htonl(uint32_t hostlong); // host to network long
uint16_t htons(uint16_t hostshort); // host to network short
uint32_t ntohl(uint32_t netlong); // network to host long
uint16_t ntohs(uint16_t netshort); // network to host short
```

### connect
用 socket 連線到 "www.example.com" 的 port 3490 [telnet]
```C
struct addrinfo hints, *res;
int sockfd;

// 首先，用 getaddrinfo() 載入 address structs：

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

getaddrinfo("www.example.com", "3490", &hints, &res);

// 建立一個 socket：

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

// connect!
connect(sockfd, res->ai_addr, res->ai_addrlen);
```
我們不會呼叫 bind()。基本上，我們不用管我們的 local port number；我們只在意我們的目地［遠端 port］。Kernel 會幫我們選擇一個 local port，而我們要連線的站台會自動從我們這裡取得資訊
### accept
很遠的人會試著 connect() 到你的電腦正在 listen() 的 port。他們的連線會排隊等待被 accept()。你呼叫 accept()，並告訴它要取得擱置的（pending）連線。它會傳回給你專屬這個連線的一個新 socket file descriptor

你突然有了兩個 socket file descriptor！原本的 socket file descriptor 仍然正在 listen 後續的連線，而新建立的 socket file descriptor 則是在最後要準備給 send() 與 recv() 用的

```C
#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
sockfd 是正在進行 listen() 的 socket descriptor。addr 通常是一個指向 local struct sockaddr_storage 的指標，儲存進來的連線的資訊［你可以用它來得知client是哪一台主機從哪一個 port 呼叫你的］。addrlen 是一個 local 的整數變數，應該在將它的位址傳遞給 accept() 以前，將它設定為 sizeof(struct sockaddr_storage)。accept() 不會存放更多的 bytes（位元組）到addr。若它存放了較少的 bytes 進去，它會改變 addrlen 的值來表示

accept() 通常會 block（阻塞），而你可以使用 select() 事先取得 listen 中的 socket descriptor 狀態，檢查 socket 是否就緒可讀（ready to read）。若為就緒可讀，則表示有新的連線正在等待被 accept()！另一個方式是將 listen 中的 socket 使用 fcntl() 設定 O_NONBLOCK 旗標，然後 listen 中的 socket descriptor 就不會造成 block，而是傳回 -1，並將 errno 設定為 EWOULDBLOCK。
### send and recv
這兩個用來通信的函式是透過 stream socket 或 connected datagram socket
#### send
```C
#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int s, const void *buf, size_t len, int flags);
```
- MSG_OOB:
以 "out of band" 送出，TCP支援這項功能，而這個方法可以用來告訴接收端，有高優先權的資料需要接收。接收端會收到 SIGURG 訊號，並且可以先從佇列中接收這筆資料。

- MSG_DONTROUTE: 
不要透過 router 送出這筆資料，只將它留在區域網路內部。

- MSG_DONTWAIT:
若 send() 會因為外部流量堵塞而導致 block，讓它直接傳回 EAGAIN。這類似＂只針對這次的 send() 啟用 non-blocking＂

- MSG_NOSIGNAL:若你 send() 的遠端主機不再接收資料了，一般你會收到 SIGPIPE 訊號，新增這個 flag 可以避免觸發這個訊號。

```C
#include <sys/types.h>
#include <sys/socket.h>

int sendall(int s, char *buf, int *len)
{
    int total = 0; // 我們已經送出多少 bytes 的資料
    int bytesleft = *len; // 我們還有多少資料要送
    int n;

    while (total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // 傳回實際上送出的資料量

    return n == -1? -1: 0; // 失敗時傳回 -1、成功時傳回 0
}
```
```C
char buf[10] = "Beej!";
int len;

len = strlen(buf);
if (sendall(s, buf, &len) == -1) {
    perror("sendall");
    printf("We only sent %d bytes because of the error!\n", len);
}
```
#### recv
```C
#include <sys/types.h>
#include <sys/socket.h>

ssize_t recv(int s, void *buf, size_t len, int flags);
```
當你呼叫 recv() 時，它會 block，直到讀到了一些資料，如果你希望它不會 block，那麼可以將 socket 設定為 non-blocking、或者是在呼叫 recv() 或 recvfrom() 以前，使用 select() 或 poll() 檢查 socket 上是否有資料。

### select
```C
int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout);

FD_SET(int fd, fd_set *set);      // 將 fd 新增至 set。
FD_CLR(int fd, fd_set *set);      // 從 set 中移除 fd。
FD_ISSET(int fd, fd_set *set);    // 若 fd 在 set 中(something happen in fd)則傳回 true。
FD_ZERO(fd_set *set);             // 將 set 清為零。
// 成功時傳回 set 中的 descriptors 數量，若發生 timeout 時傳回 0，
// 錯誤時傳回 -1（並設定相對應的errno），還有 sets 會被改過，用以表示哪幾個 sockets 是已經就緒的
```
select() 函式讓你可以同步檢查多個 sockets，檢查它們是否有資料需要接收，或者是否你可以送出資料而不會發生 blocking，或者是否有例外發生。
select() 會在有任何事件發生或 timeout 之後返回。

你可以使用如上述的 FD_SET() macros（巨集）來調整 socket descriptors set。

如果你想要知道 set 上的哪些 sockets 有資料可以接收（就緒可讀），則將這個 set 放在 readfds 參數；
如果你想要知道 set 上的哪些 sockets 有資料可以傳送（就緒可寫），則將這個 set 放在 writefds 參數；
若你想知道哪些 sockets 有例外（錯誤）發生，則可以將 set 擺在 exceptfds 參數。
沒興趣知道的事件可以將 select() 相對應的參數設定為 NULL。
在 select() 返回之後，這些 sets 的值會改變，用以標示哪些 sockets 是就緒可讀、可寫，及有例外發生等事件。

第一個參數 n 的值是最大的那個 socket descriptor 數值在加上 1。

最後，struct timeval 可以設定 timeout 的時間，用來告訴 select() 要等待多久的時間。 struct timeval 有兩個欄位：tv_sec 設定秒（second）、tv_usec 設定微秒（microsecond）［一秒鐘有 1,000,000 微秒］。
#### example1
```C
int s1, s2, n;
fd_set readfds;
struct timeval tv;
char buf1[256], buf2[256];

// 假裝我們此時已經都連線到 server 了
//s1 = socket(...);
//s2 = socket(...);
//connect(s1, ...)...
//connect(s2, ...)...

// 事先清除 set
FD_ZERO(&readfds);

// 將我們的 descriptors 新增到 set
FD_SET(s1, &readfds);
FD_SET(s2, &readfds);

// 因為 s2 是後來才取得的，所以它的數值會＂比較大＂，所以我們用它作為 select() 中的 n 參數

n = s2 + 1;

// 在 timeout 以前會一直等待，看是否已經有資料可以接收的 socket（timeout 時間是 10.5 秒）
tv.tv_sec = 10;
tv.tv_usec = 500000;
rv = select(n, &readfds, NULL, NULL, &tv);

if (rv == -1) {
    perror("select"); // select() 發生錯誤
} else if (rv == 0) {
    printf("Timeout occurred!  No data after 10.5 seconds.\n");
} else {
    // 至少一個 descriptor(s) 有資料
    if (FD_ISSET(s1, &readfds)) {
        recv(s1, buf1, sizeof buf1, 0);
    }
    if (FD_ISSET(s2, &readfds)) {
        recv(s2, buf2, sizeof buf2, 0);
    }
}
```
#### example2
```C
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define STDIN 0 // standard input 的 file descriptor
int main()
{
  struct timeval tv;
  fd_set readfds;

  tv.tv_sec = 2;
  tv.tv_usec = 500000;

  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);

  // 不用管 writefds 與 exceptfds：
  select(STDIN+1, &readfds, NULL, NULL, &tv);

  if (FD_ISSET(STDIN, &readfds))
    printf("A key was pressed!\n");
  else
    printf("Timed out.\n");
  return 0;
}
```