#include <bits/stdc++.h>
using namespace std;
#define N 200010
typedef long long LL;
const LL INF = 1LL<<60;
struct node {
	int v, nxt;
} edge[N*2];
LL dp[N], sum[N], w[N], head[N], tot, ans; 
void add (int u, int v) {
	edge[tot].v = v; edge[tot].nxt = head[u]; head[u] = tot++;
} 
void dfs(int u, int fa) {
	sum[u] = w[u];
	for(int i = head[u]; i != -1; i = edge[i].nxt) {
	    int v = edge[i].v;
	    if(v == fa) continue;

	    dfs(v, u);
	    sum[u] += sum[v];

	    // if dp[u] has been updated,
	    // it means that u has at least 2 children
	    // if u has more than 1 child, we can update ans
	    if(dp[u] > -INF) ans = max(ans, dp[u] + dp[v]);

	    dp[u] = max(dp[u], dp[v]);
	}
	dp[u] = max(dp[u], sum[u]);
}
int main() {
	int n;
	cin >> n;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++) cin >> w[i];
	for(int i = 1; i < n; i++) {
	    int u, v;
	    cin >> u >> v;
	    add(u, v); add(v, u);
	}
	ans = -INF;
	for(int i = 1; i <= n; i++) dp[i] = -INF;
	dfs(1, -1);
	if(ans <= -INF) puts("Impossible");
	else cout << ans << endl;
	return 0;
}
/*
求最大两个的不相交子树的点权和，如果没有两个不相交子树，那么输出Impossible

dp[u]: 以u為根的所有子樹中的最大權和(including u)
sum[u]: 以u為根的子樹的權和 (including u)

dp[u] = max(sum[u], dp[i]), 
where i is the neighbor node of u with largest dp value

ans = dp[x] + dp[y], 
x and y are the two neighbor vertice of u with largest dp value
where u belongs to the set of all nodes with at least two children nodes
*/