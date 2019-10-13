## 1
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

## 2
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

## 3
transfer IP string to numerical presentation
```C
struct sockaddr_in sa; // IPv4
struct sockaddr_in6 sa6; // IPv6
inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr)); // IPv4
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
```

## Note
### 1
```C
#include <netinet/in.h>

uint32_t htonl(uint32_t hostlong); // host to network long
uint16_t htons(uint16_t hostshort); // host to network short
uint32_t ntohl(uint32_t netlong); // network to host long
uint16_t ntohs(uint16_t netshort); // network to host short
```

### 2
用 socket 連線到 "www.example.com" 的 port 3490
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

### 3
```C
int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout);

FD_SET(int fd, fd_set *set);
FD_CLR(int fd, fd_set *set);
FD_ISSET(int fd, fd_set *set);
FD_ZERO(fd_set *set);
```
select() 函式讓你可以同步檢查多個 sockets，檢查它們是否有資料需要接收，或者是否你可以送出資料而不會發生 blocking，或者是否有例外發生。

你可以使用如上述的 FD_SET() macros（巨集）來調整 socket descriptors set。

如果你想要知道 set 上的哪些 sockets 有資料可以接收（就緒可讀），則將這個 set 放在 readfds 參數；
如果你想要知道 set 上的哪些 sockets 有資料可以傳送（就緒可寫），則將這個 set 放在 writefds 參數；
若你想知道哪些 sockets 有例外（錯誤）發生，則可以將 set 擺在 exceptfds 參數。
沒興趣知道的事件可以將 select() 相對應的參數設定為 NULL。
在 select() 返回之後，這些 sets 的值會改變，用以標示哪些 sockets 是就緒可讀、可寫，及有例外發生等事件。

第一個參數 n 的值是最大的那個 socket descriptor 數值在加上 1。