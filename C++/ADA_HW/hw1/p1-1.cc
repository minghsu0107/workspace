#include <bits/stdc++.h>
#define N 1000010
using namespace std;
typedef long long ll;
ll cnt = 0;
ll arr[N], p[N], f[N];

int low_bound(int x, int y, ll v) {
	return (lower_bound(begin(arr) + x, begin(arr) + y + 1, v) - begin(arr));
}

int up_bound(int x, int y, ll v) {
	return (upper_bound(begin(arr) + x, begin(arr) + y + 1, v) - begin(arr));
}

void merge(int left, int right) {
	if (left == right) return;
	int mid = (left + right) >> 1;
	merge(left, mid);
	merge(mid + 1, right);

	sort(begin(arr) + left, begin(arr) + mid + 1);
	for (int i = mid + 1; i <= right; ++i) {
		int l = p[i] - f[i];
		int r = p[i] + f[i];
		l = min(l, r), r = max(l, r);
		cnt += up_bound(left, mid, r) - low_bound(left, mid, l);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		arr[i] = p[i];
	}
	for (int i = 0; i < n; ++i) cin >> f[i];
	
	merge(0, n - 1);
	printf("%lld\n", cnt);
}