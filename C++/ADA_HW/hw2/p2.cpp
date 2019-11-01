#include <bits/stdc++.h>
#define MAXN 100001
#define MAXM 301
#define INF 1000000007
using namespace std;

int n, m, k, l, r;
int note[MAXN], dp[MAXN][MAXM];

int solve() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!i) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int q = 0; q < m; ++q) {
				l = abs(note[i + 1] - note[i]);
				l = l > k? l - k: 0;
				r = abs(j - q);
				r = r > k? r - k: 0;
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][q] + l + r);

				l = abs(note[i + 1] - q);
				l = l > k? l - k: 0;
				r = abs(j - note[i]);
				r = r > k? r - k: 0;
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][q] + l + r);
			}
		}
	}

	int Min = INF;
	for (int i = 0; i < m; ++i) {
		Min = min(Min, dp[n - 1][i]);
	}
	return Min;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
		cin >> note[i];
	cout << solve() << '\n';
}
/*
dp[i][j]: the lowest effort when one hand puts on note[i]
		  and the other puts on j at i-th second
ans: max{dp[n - 1][i]}

time
i    	note[i]		q
i + 1	note[i + 1] j

dp[i + 1][j] is tranferred from dp[i][j],
and there are two cases:
	1. hand on note[i] moves to note[i+1]
	2. another hand at time t moves to note[i+1]
we should choose the minimum one
*/