#include <bits/stdc++.h>
using namespace std;
const int MAXN = (1 << 18) + 5;

int v[MAXN], query[MAXN], inDeg[MAXN], reducedDeg[MAXN], n, m, q;

struct DisjointSet {
	int p[MAXN], sz[MAXN];

	void init(int n) {
		for (int i = 0; i <= n; ++i)
			p[i] = i, sz[i] = 1;
	}
	int find(int val) {
		return p[val] == val? val: p[val] = find(p[val]);
	}
	void merge(int v1, int v2) {
		v1 = find(v1);
		v2 = find(v2);
		if (v1 != v2) {
			p[v1] = v2;
			sz[v2] += sz[v1];
		}
	}
} djs;

void solve() {
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &q);
		vector<int> used;
		int tmp_p, ans = 0;

		for (int i = 1; i <= q; ++i) {
			scanf("%d", &query[i]);
		}
		for (int i = 1; i <= q; ++i) {
			while (inDeg[query[i]] - reducedDeg[query[i]] == 0) {
				// tmp_p = root of the set that query[i] is in
				tmp_p = djs.find(query[i]);
				ans += djs.sz[tmp_p];

				// next vertex to test whether to delete 
				// is the vertex that tmp_p points to
				query[i] = v[tmp_p];
				++reducedDeg[query[i]];
				// record vertices whose in-degree is reduced
				used.emplace_back(query[i]);
			}
		}
		// recover the state for the next query round
		for (auto &x: used)
			reducedDeg[x] = 0;
		printf("%d\n", ans);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (v[i])
			++inDeg[v[i]];
	}

	djs.init(n);
	for (int i = 1; i <= n; ++i) {
		if (inDeg[v[i]] == 1) // collapse the node with in-degree of 1
			djs.merge(i, v[i]); // only vertex i points to vertex v[i]
	}
	solve();
	return 0;
}