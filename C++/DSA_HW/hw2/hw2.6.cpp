#include<bits/stdc++.h> 
#include<cstring>
using namespace std; 
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
#define ALPHABET_SIZE 26 
#define MAXN 200010

int n, q, l, x, y, dfs_clock = 1;
char c;
int depth[MAXN];
int euler[MAXN<<1];
int id[MAXN];
int dp[20][MAXN<<1];
int node[MAXN];
int trie[MAXN][ALPHABET_SIZE];
inline void write(int x) {
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
inline void insert(int pa, int v, char c) { 
    pa = node[pa];
    if (trie[pa][c-'a'] == -1) {
        trie[pa][c-'a'] = v;
        depth[v] = depth[pa] + 1;
    }
    node[v] = trie[pa][c-'a'];
} 
 
inline void DFS(int u) {
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
    if (id[u] > id[v]) swap(u, v);
    return query(id[u], id[v]);
} 
int main() { 
    memset(trie, -1, sizeof(trie));
    scan(n);
    for (int i = 1; i <= n; ++i) {
        scan(l);
        c = getchar();
        insert(l, i, c);
    }
    DFS(0);
    RMQ_init(dfs_clock - 1);
    for (int i = 1; i <= 2 * n - 1; ++ i) {
        if (!id[euler[i]]) id[euler[i]] = i;
    }
    for (int i = 0; i <= n; ++i) {
        if (!id[i]) id[i] = id[node[i]];
    }
    scan(q);
    for (int i = 0; i < q; ++i) {
        scan(x);
        scan(y);
        write(LCA(x, y)), puts("");
    }
    return 0; 
}