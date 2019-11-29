#include <bits/stdc++.h>
#define N 100005
#define M 500005
using namespace std;
typedef long long ll;
typedef pair<int, ll> ii;

int s1[M], s2[M], n, m;
ll t1[M], t2[M], dp[(N + M)<<1];
vector<ii> nodes;
vector<ii> v[(N + M)<<1];
int vis[(N + M)<<1];

void addEdge(int from, int to, ll w) {
    v[from].emplace_back(to, w);
}

void init() {
	sort(begin(nodes), end(nodes));
	nodes.resize(unique(begin(nodes), end(nodes)) - begin(nodes));
	int sz = nodes.size();

	for (int i = 0; i < sz; ++i) {
		vis[i] = 0;
		dp[i] = -1LL;
		v[i].clear();
	}

	for (int i = 0; i < sz; ++i) {
		if (i + 1 < sz && nodes[i].first == nodes[i + 1].first) {
			addEdge(i, i + 1, nodes[i + 1].second - nodes[i].second);
		}
	}
	for (int i = 0; i < m; ++i) {
		int song1 = lower_bound(begin(nodes), end(nodes), make_pair(s1[i], t1[i])) 
					- begin(nodes);
		int song2 = lower_bound(begin(nodes), end(nodes), make_pair(s2[i], t2[i])) 
					- begin(nodes);
		addEdge(song1, song2, 1LL);
	}
}

bool dfs(int s) {
	if (vis[s] == 1) return false;
	if (vis[s] == 2) return true;
	vis[s] = 1;
	for (auto &e: v[s]) {
		if (!dfs(e.first))
			return false;
	}
	vis[s] = 2;
	return true;
}

bool isDAG() {
	int sz = nodes.size();
	for (int i = 0; i < sz; ++i) {
		if (!dfs(i))
			return false;
	}
	return true;
}

ll find(int s) {
	if (dp[s] != -1LL) return dp[s];
	dp[s] = 0LL;
	for (auto &e: v[s]) {
		dp[s] = max(dp[s], find(e.first) + e.second);
	}
	return dp[s];
}

void solve() {
	if (!isDAG()) {
		cout << "LoveLive!" << '\n';
		return;
	}
	ll Max = 0;
	int sz = nodes.size();
	for (int i = 0; i < sz; ++i) {
		Max = max(Max, find(i));
	}
	cout << Max << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> n >> m;
		nodes.clear();
		for (int i = 1; i <= n; ++i) {
			ll len; cin >> len;
			nodes.emplace_back(i, 0);
			nodes.emplace_back(i, len);
		}
		for (int i = 0; i < m; ++i) {
			cin >> s1[i] >> t1[i] >> s2[i] >> t2[i];
			nodes.emplace_back(s1[i], t1[i]);
			nodes.emplace_back(s2[i], t2[i]);
		}
		init();
		solve();
	}
	return 0;
}