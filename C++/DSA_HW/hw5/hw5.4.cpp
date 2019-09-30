#include <bits/stdc++.h>
#define maxn 11
#define MOD 1000000007
#pragma GCC optimize("03")
using namespace std;
typedef long long LL;
char c;
int N, M, sum[maxn][maxn], con[maxn][maxn][maxn][maxn];
LL a[maxn][maxn][maxn][maxn][maxn*maxn], aug[maxn*maxn][maxn*maxn];
LL C(int n, int m) {
    if (aug[n][m] == -1) {
        register int i, j;
        for(i = 0; i <= m; ++i)
            aug[0][i] = aug[1][i] = 1;
        for(i = 0; i <= n; ++i)
            aug[i][0] = 1;
        for(i = 0; i <= m; ++i) {aug[i][i] = 1;}
        for(i = 1; i <= n; ++i) {
            for(j = 1; j <= m; ++j) {
                if(i != j)
                    aug[i][j] = (aug[i-1][j] + aug[i-1][j-1])%MOD;
            }
        }
    }
    return aug[n][m];
}
LL dp(int x1, int y1, int x2, int y2, int k) {
    if (k == 0) return 1LL;
    if (x1 > x2 || y1 > y2 || (x1 == x2 && y1 == y2)) return 0LL;

    if (a[x1][y1][x2][y2][k] == -1) {
        if (con[x1][y1][x2][y2] != -1 && k >= con[x1][y1][x2][y2]) return 0LL;
        else {
            LL ans = 0;
            register int i, j;
            for (i = x1; i <= x2; ++i) {
                if (x1 != x2 && !(sum[i][y2] - sum[i-1][y2] - sum[i][y1-1] + sum[i-1][y1-1])) {
                    for (j = 0; j < k; ++j) {
                        LL x = C(k-1, j); if (!x) break;
                        LL y = dp(x1, y1, i-1, y2, j); if (!y) break;
                        ans = (ans + x*y%MOD*dp(i+1, y1, x2, y2, k-1-j)%MOD)%MOD;
                    }
                    
                }
            }
            for (i = y1; i <= y2; ++i) {
                if (y1 != y2 && !(sum[x2][i] - sum[x1-1][i] - sum[x2][i-1] + sum[x1-1][i-1])) {        
                    for (j = 0; j < k; ++j) {
                        LL x = C(k-1, j); if (!x) break;
                        LL y = dp(x1, y1, x2, i-1, j); if (!y) break;
                        ans = (ans + x*y%MOD*dp(x1, i+1, x2, y2, k-1-j)%MOD)%MOD;
                    }   
                }
            }
            a[x1][y1][x2][y2][k] = ans;
            if (!ans) con[x1][y1][x2][y2] = k;
        }
    }
    return a[x1][y1][x2][y2][k];
}
int main() {
    scanf("%d%d", &N, &M);
    register int i, j;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            cin >> c;
            sum[i][j] = (c == 'O')? 0: 1;
        }
    }
    memset(aug, -1, sizeof(aug));
    memset(a, -1, sizeof(a));
    memset(con, -1, sizeof(con));
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            sum[i][j] += sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
    LL ans = 0;
    int k = N * M;
    for (i = 0; i <= k; ++i) {
        ans = (ans + dp(1, 1, N, M, i))%MOD;
    }
    printf("%lld\n", ans);
}