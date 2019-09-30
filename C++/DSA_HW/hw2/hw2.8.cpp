#include<bits/stdc++.h> 
#include<cstring>
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
using namespace std; 
#define ALPHABET_SIZE 26 
#define MAXN 200010
#define MAXQ 5000010
#define buf_size 5000010
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
int n, q, dfs_clock = 1;
int depth[MAXN];
int euler[MAXN<<1];
int id[MAXN];
int dp[20][MAXN<<1];
int node[MAXN];
int trie[MAXN][ALPHABET_SIZE];
int x[MAXQ];
int y[MAXQ];
inline void insert(int pa, int v, char c) { 
    pa = node[pa];
    if (trie[pa][c-'a'] == -1) {
        trie[pa][c-'a'] = v;
        depth[v] = depth[pa] + 1;
    }
    node[v] = trie[pa][c-'a'];
} 
 
inline void DFS(int u) {
    id[u] = dfs_clock;
    euler[dfs_clock++] = u;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (trie[u][i] != -1) {
            DFS(trie[u][i]);
            euler[dfs_clock++] = u;
        }
    }
}
inline void RMQ_init(int NN) {
    for (int i = 1; i <= NN; ++i)
        dp[0][i] = depth[euler[i]];
    for (int j = 1; (1<<j) <= NN; ++j)
        for (int i = 1; i + (1<<j) - 1 <= NN; ++i)
            dp[j][i] = min(dp[j-1][i], dp[j-1][i + (1<<(j-1))]);
}
inline int query(int L, int R) {
    int k = 0;
    while((1<<(k+1)) <= R-L+1) ++k;
    return min(dp[k][L], dp[k][R - (1<<k) + 1]);
}
inline int LCA(int u, int v) {
    if (u > v) swap(u, v);
    return query(u, v);
} 
int main() { 
    memset(trie, -1, sizeof(trie));
    n = readInt();
    for (int i = 1; i <= n; ++i) {
        register int l;
        register char c;
        l = readInt();
        c = readChar();
        insert(l, i, c);
    }
    DFS(0);
    RMQ_init(dfs_clock - 1);
    for (int i = 0; i <= n; ++i) {
        id[i] = id[node[i]];
    }
    q = readInt();
    for (int i = 0; i < q; ++i) {
        x[i] = readInt();
        y[i] = readInt();
 
    }
    for (int i = 0; i < q; ++i) {
        x[i] = id[x[i]]; 
        y[i] = id[y[i]];
    }
    for (int i = 0; i < q; i++) {
        writeInt(LCA(x[i], y[i])), writeChar('\n');
    }
    return 0; 
}