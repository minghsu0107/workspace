#include <bits/stdc++.h>
#define INF 1000000007
#define MAXN 110
#define MAXE 10010
using namespace std;

struct var {
	int A;
	int B;
	double f;
	bool operator < (const var& tmp) const {
		if (f == tmp.f) {
			if (B == tmp.B)
				return A < tmp.A;
			return B > tmp.B;
		}
		return f < tmp.f;
	}
};

int dp[2][MAXN][MAXE];
var p[MAXN];
int n, K, E;

int solve() {
	for (int i = 0; i <= 1; ++i) {
		for (int j = 0; j <= n; ++j) {
			for (int e = 0; e <= E; ++e) {
				dp[i][j][e] = -1;
			}
		}
	}
	bool bi; // 滾動
	int tmp;
	for (int i = 1; i <= n; ++i) {
		bi = i & 1;
		tmp = min(i, K); // k <= n
		for (int j = 1; j <= tmp; ++j) {
			if (j == 1) {
				for (int q = 1; q <= i; ++q)
					dp[bi][1][p[q].B] = 0;
				continue;
			}
			for (int e = 0; e <= E; ++e) {
				dp[bi][j][e] = max(dp[bi][j][e], dp[1 - bi][j][e]);
				if (e >= p[i].B && dp[1 - bi][j - 1][e - p[i].B] != -1) {
					dp[bi][j][e] = max(dp[bi][j][e], 
					dp[1 - bi][j - 1][e - p[i].B] + (e - p[i].B) * p[i].A);
				}
			}
		}
	}
	int M = -INF;
	for (int i = 0; i <= E; ++i)
		M = max(M, dp[bi][K][i]);
	return M;
}

int main() {
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &p[i].A, &p[i].B);
		if (p[i].B == 0)
			p[i].f = INF;
		else 
			p[i].f = ((double)p[i].A) / ((double)p[i].B);
		E += p[i].B;
	}
	sort(p + 1, p + n + 1);
	printf("%d\n", solve());
	return 0;
}
/*
dp[i][j][e]: have i pokemon choices, play j rounds, and have accumulated experience e

dp[i][j][e] = max(dp[i-1][j][e], dp[i-1][j-1][e-B[i]] + (e-B[i]) * A[i])
meaning that the maximum damage of dp[i][j][e], can be transfered from:
	1. dp[i-1][j][e], not choosing ith pokemon in this round
	2. dp[i-1][j-1][e-B[i]], choosing ith pokemon in this round,
	   so the maximum damage = the maximum damage of the last round + damage caused by i
	   (the last round has i-1 pokemon choices, not including i)

Note that dp[i][1][B[k]] = 0 for k from 1 to i for i from 1 to n (basic case)
This is because the damage in the first round is always 0 (experience = 0)

Also note that the value of current dp cannot be transfered from impossible status
such as statuses with impossible experience ie. those statuses with dp value of -1

To get the largest damage, we must sort all pokemon according to their
contribution to the total damage (applying greedy algorithm).
suppose i first then j:
	damage = E * Ai + (E + Bi) * Aj
suppose j first then i:
	damage = E * Aj + (E + Bj) * Ai
if placing i first do more damage:
	 BiAj > BjAi
  -> Aj/Bj > Ai/Bi

1. smaller ratio should be put first 
2. if the ratio is same, compare B (B is more important than A since B can affect experience
   and thus have more influence on the rest element), larger B should be put first
3. if B is same, compare A, larger A should be put last
*/