// O(nlogn)
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
#define ll long long
int n, s;
int main() {
	scanf("%d%d", &n, &s);
	vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    ll ans = 0;
	// for each i, find [0, l] and [r, n-1]
	for (int i = 1; i < n - 1; i++) {
		int l = lower_bound(a.begin(), a.end(), a[i] - s) - a.begin();
		int r = upper_bound(a.begin(), a.end(), a[i] + s) - a.begin();
		ans += 1ll * l * (n - r);
	}
	printf("%lld\n", ans);
    return 0;
}