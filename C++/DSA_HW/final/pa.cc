// O(n^2)
#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
#define ll long long
int a[maxn];
int n, s;
int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    ll ans = 0;
    // enumerate the middle point
    for (int i = 2, l = 1, r = 2; i < n; i++) {
            while (a[i] - a[l] > s) l++;
            while (r <= n && a[r] - a[i] <= s) r++;
            ans += 1ll*(l-1)*(n-r+1);
    }
    printf("%lld\n", ans);
    return 0;
}