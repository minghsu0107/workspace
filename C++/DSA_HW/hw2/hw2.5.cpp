#include<bits/stdc++.h> 
#include<cstring>
using namespace std; 
 
#define ALPHABET_SIZE 26 
#define MAXN 200010
int n, q, l, x, y, dfs_clock = 1;
char c;
int depth[MAXN<<1];
int id[MAXN];
int dp[20][MAXN<<1];
int node[MAXN];
int trie[MAXN][ALPHABET_SIZE];
inline void write(int x) {
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
template <typename T>
inline bool ret(T& x) {
    char c = 0; bool flag = false;
    while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
    c == '-' ? (flag = true, x = 0) : (x = c - '0');
    while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
    if (flag) x = -x;
    return true;
}
template <typename T, typename ...Args>
inline bool ret(T& x, Args& ...args) { return ret(x) && ret(args...); }
inline void insert(int pa, int v, char c) { 
    if (trie[node[pa]][c-'a'] == -1) {
        trie[node[pa]][c-'a'] = v;
    }
    node[v] = trie[node[pa]][c-'a'];
} 

int d = 0;
inline void DFS(int u) {
    id[u] = dfs_clock;
    depth[dfs_clock++] = d;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (trie[u][i] != -1) {
            d++;
            DFS(trie[u][i]);
            depth[dfs_clock++] = --d;
        }
    }
}
inline void RMQ_init(int NN) {
    for (int i = 1; i <= NN; ++i)
        dp[0][i] = depth[i];
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
    if (id[u] > id[v]) swap(u, v);
    return query(id[u], id[v]);
} 
int main() { 
    memset(trie, -1, sizeof(trie));
    ret(n);
    for (int i = 1; i <= n; ++i) {
        ret(l), c = getchar();
        insert(l, i, c);
    }
    DFS(0);
    RMQ_init(dfs_clock - 1);
    // handle node-to-id matching in advance to be faster
    for (int i = 0; i <= n; ++i) {
        id[i] = id[node[i]];
    }
    ret(q);
    for (int i = 0; i < q; ++i) {
        ret(x, y);
        write(LCA(x, y)), puts("");
    }
    return 0; 
}
