#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2e3 + 10;
char s[maxn], t[maxn];
int dp[2][maxn];

int main() {
	scanf("%s%s", s, t);
	int n = strlen(s), m = strlen(t);
	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			if (s[i] != t[j]) dp[1][j] = dp[0][j + 1];
			else {
				dp[1][j] = min({dp[0][j], dp[0][j + 1], dp[1][j + 1]}) + 1;
			}
		}
		for (int j = 0; j < m; j++) dp[0][j] = dp[1][j]; 
	}
	printf("%d\n", dp[0][0]);
	return 0;
}
