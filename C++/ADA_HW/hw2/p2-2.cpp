#include <bits/stdc++.h>
#define MAXN 100001
#define MAXM 301
#define INF 1000000007
using namespace std;

int n, m, k, l, r;
int note[MAXN], dp[MAXN][MAXM];
int q, Min;
int solve() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!i) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			Min = INF;
			for (int p = max(j - k, 0); p <= min(j + k, m - 1); ++p) {
				if (dp[i][p] < Min) {
					Min = dp[i][p];
					q = p;
				}
			}
			l = abs(note[i + 1] - note[i]);
			l = l > k? l - k: 0;
			r = abs(j - q);
			r = r > k? r - k: 0;
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][q] + l + r);

			Min = INF;
			for (int p = max(note[i + 1] - k, 0); p <= min(note[i + 1] + k, m - 1); ++p) {
				if (dp[i][p] < Min) {
					Min = dp[i][p];
					q = p;
				}
			}
			l = abs(note[i + 1] - q);
			l = l > k? l - k: 0;
			r = abs(j - note[i]);
			r = r > k? r - k: 0;
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][q] + l + r);
		}
	}
	Min = INF;
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
Our goal is to find out the best q such that dp[i][q] + l + r is smallest
the best q may have two possible values because there are two cases
we should choose the one that makes dp[i+1][j] smallest

Intuitively, we can know that abs(dp[i][j] - dp[i][j+1]) <= 1 ... (1)

in case 1, l is constant, and by (1) we can know that 
if q is in [j - k, j + k], q' is outside [j - k, j + k], 
dp[i][q'] + r' will not smaller than dp[i][q] + r = dp[i][q] (r < k)
Therefore, the best q lies in [j - k, j + k]
case 2 can be discussed similarly

Therefore, the best q lies in [target - k, target + k], 
where target is the position q wants to go
*/