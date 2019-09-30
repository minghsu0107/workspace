#include <bits/stdc++.h>
#define maxn 101
using namespace std;

vector<int> G[maxn];
int p[maxn], n, root;
void read_tree() {
    int u, v;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        // tree is undirected
    }
    scanf("%d", &root);
}
void dfs(int u, int fa) {
    int d = G[u].size();
    for (int i = 0; i < d; i++) {
    	int v = G[u][i];
    	if (v != fa) {
    		p[v] = u;
    		dfs(v, u);
    		// dfs(v, p[v] = u);
    	}
    }
}
int main() {
    read_tree();
    p[root] = -1;
    dfs(root, -1);
    for (int i = 0; i < n; ++i)
    	cout << p[i] << " ";
    return 0;
}