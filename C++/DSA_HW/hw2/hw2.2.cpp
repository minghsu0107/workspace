#include<bits/stdc++.h> 
#include<cstring>
using namespace std; 
 
#define ALPHABET_SIZE (26) 
#define MAX 200005
int n, q, l, x, y, d[MAX], fa[MAX][20];
char c;
struct TrieNode { 
    TrieNode *children[ALPHABET_SIZE]; 
    int id;
}; 
TrieNode *node[MAX];
 
struct TrieNode *getNode() { 
    TrieNode *pNode = new TrieNode; 
    pNode->id = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) 
        pNode->children[i] = NULL; 
    return pNode; 
} 
 
void insert(int parent, int v, char c) { 
    parent = node[parent]->id;
    if (node[parent]->children[c - 'a'] == NULL) {
        node[parent]->children[c - 'a'] = getNode();
        node[v] = node[parent]->children[c - 'a'];
        node[v]->id = v;
        fa[v][0] = parent;
        d[v] = d[parent] + 1; 
    }
    else node[v] = node[parent]->children[c - 'a'];
} 
 
int lca(int x, int y) {
    x = node[x]->id, y = node[y]->id;
    if (d[x] < d[y]) {
        swap(x, y);
    }
    for (int i = 18; i >= 0; --i) {
        if (fa[x][i] != -1 && d[fa[x][i]] >= d[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return d[x]; // y is the ancestor of x
    }
    for (int i = 18; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return d[fa[x][0]];
}
 
void init() {
    TrieNode *root = getNode();
    memset(fa, -1, sizeof(fa));
    node[0] = root;
    d[0] = 0;
    cin >> n;
    
    for (int i = 1; i <= n; ++i) {
        cin >> l >> c;
        insert(l, i, c);
    }
   
    for (int i = 1; i <= 18; ++i) {
        for (int j = 1; j <= n; ++j) {
            int v = node[j]->id;
            if (fa[j][i-1] != -1) {
                fa[v][i] = fa[fa[v][i-1]][i-1];
            }
        }
    }
}
void solve() {
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> x >> y;
        cout << lca(x, y) << '\n';
    }
}
int main() { 
    ios_base::sync_with_stdio(false); cin.tie(0);
    init();
    solve();
    return 0; 
}
// preparation: NlogN; query: logN