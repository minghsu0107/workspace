#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 9;
int a[maxn][maxn];
int main() {
	int i, j, k, n, m, q;
	cin >> n >> m >> q;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++)
		cin >> a[i][j];
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			a[i][j] += a[i][j-1] + a[i-1][j] - a[i-1][j-1];
		}
	}
	for (i = 1; i <= q; i++) {
		int x1, y1, x2, y2;
		cin>> x1 >> y1 >> x2 >> y2;
		int ans=a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1];
		cout << ans << endl;
	}
}