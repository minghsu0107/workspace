#include <bits/stdc++.h>
#define maxn 12
#define MOD 1000000007
typedef long long LL;
char c;
int N, M, sum[maxn][maxn];
LL a[maxn][maxn][maxn][maxn][maxn*maxn], aug[maxn*maxn][maxn*maxn];
LL C(int n, int m) {
    if(m == 0 || n == 0 || n == 1 || m == n)  return 1;
    if(aug[n][m] != -1) return aug[n][m]%MOD;
    
    aug[n-1][m] = C(n-1, m);
    aug[n-1][m-1] = C(n-1, m-1);

    return (aug[n-1][m] + aug[n-1][m-1])%MOD;
}
int getSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}
LL dp(int x1, int y1, int x2, int y2, int k) {
    if (k == 0) return 1LL;
    if (x1 > x2 || y1 > y2) return 0LL;
    if (x1 == x2 && y1 == y2) return 0LL;

    if (a[x1][y1][x2][y2][k] == -1) {
        LL ans = 0;
        for (int i = x1; i <= x2; ++i) {
            if (x1 != x2 && !getSum(i, y1, i, y2)) {
                for (int j = 0; j < k; ++j) {
                    ans = (ans + (C(k-1, j)*(dp(x1, y1, i-1, y2, j)*dp(i+1, y1, x2, y2, k-1-j)%MOD)%MOD))%MOD;
                }
            }
        }
        for (int i = y1; i <= y2; ++i) {
            if (y1 != y2 && !getSum(x1, i, x2, i)) {
                for (int j = 0; j < k; ++j) {
                    ans = (ans + (C(k-1, j)*(dp(x1, y1, x2, i-1, j)*dp(x1, i+1, x2, y2, k-1-j)%MOD)%MOD))%MOD;
                }
            }
        }
        a[x1][y1][x2][y2][k] = ans;
    }
    return a[x1][y1][x2][y2][k];
}
void init() {
    memset(aug, -1, sizeof(aug));
    memset(a, -1, sizeof(a));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            sum[i][j] += sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
        }
    }
}
void solve() {
    LL ans = 0;
    int k = N * M;
    for (int i = 0; i <= k; ++i) {
        ans = (ans + dp(1, 1, N, M, i))%MOD;
    }
    printf("%lld\n", ans);
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            std::cin >> c;
            sum[i][j] = (c == 'O')? 0: 1;
        }
    }
    init();
    solve();
    return 0;
}