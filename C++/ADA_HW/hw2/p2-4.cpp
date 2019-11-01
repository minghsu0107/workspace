#include <bits/stdc++.h>
#define MAXN 100001
#define MAXM 301
#define INF 1000000007
using namespace std;

int n, m, k, l, r, window, low, up;
int note[MAXN], dp[MAXN][MAXM] = {};
int q, Min;
int qmin[MAXM], pmin[MAXM], mi[MAXM];

void get_min(int t) {
    int tail = 0, head = 1;

    // put k - 1 elements first
    for (int i = 0; i < window - 1; ++i) {
        while (head <= tail && qmin[tail] > dp[t][i])
            --tail;   
        qmin[++tail] = dp[t][i];
        pmin[tail] = i;
    }
    for (int i = window - 1; i < m; ++i) {
        while (head <= tail && qmin[tail] > dp[t][i])
            --tail;
        qmin[++tail] = dp[t][i];
        pmin[tail] = i;
        while (pmin[head] < i - window + 1) // outdated
            ++head;
        // idx of the minimum element in this window (starts from 0)
        mi[i - window + 1] = pmin[head];
    }
}

int solve() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!i) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
	window = k + 1; // size of sliding window
	for (int i = 0; i < n - 1; ++i) {
		get_min(i);
		for (int j = 0; j < m; ++j) {
			// case 1
			low = max(j - k, 0);
			if (j + k > m - 1)
				up = m - 1 - k;
			else up = j;
			q = dp[i][mi[low]] < dp[i][mi[up]]? mi[low]: mi[up];

			l = abs(note[i + 1] - note[i]), r = abs(j - q);
			l = l > k? l - k: 0;
			r = r > k? r - k: 0;
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][q] + l + r);

			// case 2
			low = max(note[i + 1] - k, 0);
			if (note[i + 1] + k > m - 1)
				up = m - 1 - k;
			else up = note[i + 1];
			q = dp[i][mi[low]] < dp[i][mi[up]]? mi[low]: mi[up];

			l = abs(note[i + 1] - q), r = abs(j - note[i]);
			l = l > k? l - k: 0;
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
we can also use deque optimization to get min of each sliding window
*/