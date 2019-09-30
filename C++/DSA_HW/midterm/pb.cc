#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#define MAXN 250010
#define buf_size 400010
inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x );
inline void writeWord( const char *s );
 
/** Read */
inline int getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}
 
inline int readChar() {
    int c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}
 
template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}
 
/** Write */
 
static int write_pos = 0;
static char write_buf[buf_size];
 
inline void writeChar( int x ) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}
 
template <class T>
inline void writeInt( T x, char end ) {
    if (x < 0)
        writeChar('-'), x = -x;
 
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}
inline void writeWord( const char *s ) {
    while (*s)
        writeChar(*s++);
}
struct Flusher {
    ~Flusher() {
        if (write_pos)
            fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;
int t, n, q, x, y;
int arr[MAXN], p[MAXN][20], d[MAXN];
vector<int> stk;
void init() {
    stk.clear();
    memset(p, -1, sizeof(p)); // initialize p as -1
    for (int i = n - 1; i >= 0; --i) {
        if (stk.empty()) {
            p[i][0] = -2; // index -2 is the virtual root
            d[i] = 1;
        }
        else {
            if (arr[i] < arr[stk.back()]) {
                p[i][0] = stk.back();
                d[i] = d[stk.back()] + 1;
            }
            else {
                while (!stk.empty() && arr[i] >= arr[stk.back()]) {
                    stk.pop_back();
                }
                if (!stk.empty()) {
                    p[i][0] = stk.back();
                    d[i] = d[stk.back()] + 1;
                }
                else {
                    p[i][0] = -2;
                    d[i] = 1;
                }
            }
        }
        stk.push_back(i);
    }
    for (int i = 1; i <= 18; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[j][i-1] >= 0) {
                p[j][i] = p[p[j][i-1]][i-1];
            }
        }
    }
}
int LCA(int x, int y) {
    if (d[x] < d[y]) {
        swap(x, y);
    }
    for (int i = 18; i >= 0; --i) {
        if (p[x][i] >= 0 && d[p[x][i]] >= d[y]) {
            x = p[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 18; i >= 0; i--) {
        if (p[x][i] != p[y][i]) {
            x = p[x][i];
            y = p[y][i];
        }
    }
    if (p[x][0] == -2) return -1;//lca == -2 means they are on different trees
    return p[x][0];
}
int main() {
    t = readInt();
    while(t--) {
        n = readInt();
        q = readInt();
        for (int i = 0; i < n; ++i) {
            arr[i] = readInt();
        }
        init();
        for (int i = 0; i < q; ++i) {
            x = readInt();
            y = readInt();
            printf("%d\n", LCA(x, y));
        }
    }
    return 0;
}