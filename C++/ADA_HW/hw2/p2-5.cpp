#include <bits/stdc++.h>
#define MAXN 100001
#define MAXM 301
#define INF 1000000007
using namespace std;

int n, m, k, l, r, q, Max, Min;
int note[MAXN], dp[2][MAXM];
int solve() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!i) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
	bool bi;
	for (int i = 0; i < n - 1; ++i) {
		bi = i & 1;
		for (int j = 0; j < m; ++j) {
			// case 1
			Min = max(j - k, 0), Max = min(j + k, m - 1);
			q = dp[bi][Min] < dp[bi][Max]? Min: Max;
			l = abs(note[i + 1] - note[i]), r = abs(j - q);
			l = l > k? l - k: 0;
			r = r > k? r - k: 0;
			dp[1 - bi][j] = min(dp[1 - bi][j], dp[bi][q] + l + r);

			// case 2
			Min = max(note[i + 1] - k, 0), Max = min(note[i + 1] + k, m - 1);
			q = dp[bi][Min] < dp[bi][Max]? Min: Max;
			l = abs(note[i + 1] - q), r = abs(j - note[i]);
			l = l > k? l - k: 0;
			r = r > k? r - k: 0;
			dp[1 - bi][j] = min(dp[1 - bi][j], dp[bi][q] + l + r);
		}
		for (int j = 0; j < m; ++j)
			dp[bi][j] = INF;
	}
	Min = INF;
	for (int i = 0; i < m; ++i) {
		Min = min(Min, dp[1 - bi][i]);
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