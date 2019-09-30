#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 300 + 5;
char a[maxn], b[maxn];
int c[maxn], dp[maxn][maxn][maxn];
 
int main() {
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    int n = strlen(a + 1);
    int m = strlen(b + 1);
 
    for (int i = 0; i < 3; ++i) scanf("%d", &c[i]);
    int p; scanf("%d", &p);
 
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 'D') a[i] = 0;
        if (a[i] == 'S') a[i] = 1;
        if (a[i] == 'A') a[i] = 2;
    }
    for (int i = 1; i <= m; ++i) {
        if (b[i] == 'D') b[i] = 0;
        if (b[i] == 'S') b[i] = 1;
        if (b[i] == 'A') b[i] = 2;
    }
 
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            for (int k = 0; k < maxn; ++k)
                dp[i][j][k] = -1e9;
        }
    }
 
    dp[0][0][p] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= p; ++k) {
                if (i + 1 <= n && j + 1 <= m) {
                    if (a[i + 1] == b[j + 1])
                        dp[i + 1][j + 1][k] = max(dp[i + 1][j + 1][k], dp[i][j][k] + 1);
                }
               
                if (i + 1 <= n) {
                    dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                    if (k >= c[a[i + 1]])
                        dp[i + 1][j][k - c[a[i + 1]]] = max(dp[i + 1][j][k - c[a[i + 1]]], dp[i][j][k] + 1);
                }
 
                if (j + 1 <= m) {
                    dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k]);
                    if (k >= c[b[j + 1]])
                        dp[i][j + 1][k - c[b[j + 1]]] = max(dp[i][j + 1][k - c[b[j + 1]]], dp[i][j][k] + 1);
                }
            }
        }
    }
 
    int d = 1e9;
    for (int i = 0; i < 3; ++i) d = min(d, c[i]);
 
    int ans = 0;
    for (int i = 0; i <= p; ++i) {
        ans = max(ans, dp[n][m][i] + i / (2 * d));        
    }
 
    printf("%d\n", ans);
    return 0;
}