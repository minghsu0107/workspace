#include<bits/stdc++.h> 
#include<cstring>
using namespace std; 
 
#define ALPHABET_SIZE 26 
#define MAXN 200010
int n, q, l, x, y;
char c;
int depth[MAXN<<1];
int id[MAXN];
int dfs_clock;
int dp[20][MAXN<<1];
struct TrieNode { 
    TrieNode *ch[ALPHABET_SIZE]; 
    int id;
};
TrieNode *node[MAXN]; 
struct TrieNode *getNode() { 
    TrieNode *pNode = new TrieNode; 
    pNode->id = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) 
        pNode->ch[i] = NULL; 
    return pNode; 
}  
void insert(int pa, int v, char c) { 
    if (node[pa]->ch[c - 'a'] == NULL) {
        node[pa]->ch[c - 'a'] = getNode();
        node[v] = node[pa]->ch[c - 'a'];
        node[v]->id = v; 
    }
    else node[v] = node[pa]->ch[c - 'a'];
} 
void DFS(int u, int d) {
    if (id[u] == -1) id[u] = dfs_clock;
    depth[dfs_clock++] = d;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node[u]->ch[i] != NULL) {
            DFS(node[u]->ch[i]->id, d+1);
            depth[dfs_clock++] = d;
        }
    }
}
void find_depth()
{
    dfs_clock = 1;
    memset(id, -1, sizeof(id));
    memset(depth, 0, sizeof(depth));
    DFS(0, 0);
}
void RMQ_init(int NN) {
    for (int i = 1; i <= NN; i++) {
        dp[0][i] = i;
    }
    for (int j = 1; (1<<j) <= NN; j++) {
        for (int i = 1; i + (1<<j) - 1 <= NN; i++) {
            int a = dp[j-1][i];
            int b = dp[j-1][i + (1<<(j-1))];
            if(depth[a] <= depth[b])
                dp[j][i] = a;
            else
                dp[j][i] = b;
        }
    }
}
int query(int L, int R) {
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    int a = dp[k][L];
    int b = dp[k][R - (1<<k) + 1];
    return min(depth[a], depth[b]);
}
int LCA(int u, int v) {
    u = node[u]->id, v = node[v]->id;
    int x = id[u];
    int y = id[v];
    if(x > y) {
        return query(y, x);
    }
    else {
        return query(x, y);
    }
} 
void init() {
    TrieNode *root = getNode();
    node[0] = root;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l >> c;
        insert(l, i, c);
    }
}
void solve() {
    find_depth();
    RMQ_init(dfs_clock - 1);
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> x >> y;
        cout << LCA(x, y) << '\n';
    }
}
int main() { 
    ios_base::sync_with_stdio(false); cin.tie(0);
    init();
    solve();
    return 0; 
}
// preparation:O(n*logn); query: O(1)