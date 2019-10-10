#include <bits/stdc++.h>
using namespace std;
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
typedef long long ll;
ll cnt = 0;
vector<ll> arr, p, f;

void merge(int left, int right) {
	if (right - left <= 2) {
		for (int i = left + 1; i <= right; ++i) {
			for (int j = left; j < i; ++j)
				if (abs(p[i] - p[j]) <= f[i]) ++cnt;
		}
		return;
	}
	int mid = (left + right) >> 1;
	merge(left, mid);
	merge(mid + 1, right);

	sort(begin(arr) + left, begin(arr) + mid + 1);
	for (int i = mid + 1; i <= right; ++i) {
		int l = p[i] - f[i], r = p[i] + f[i];
		if (l > r) swap(l, r);
		cnt += upper_bound(begin(arr) + left, begin(arr) + mid + 1, r) 
		     - lower_bound(begin(arr) + left, begin(arr) + mid + 1, l);
	}
}

int main() {
	int n;
	scan(n);
    arr.resize(n);
    p.resize(n);
    f.resize(n);

	for (int i = 0; i < n; ++i) {
		scan(p[i]);
		arr[i] = p[i];
	}
	for (int i = 0; i < n; ++i) scan(f[i]);
	
	merge(0, n - 1);
	printf("%lld\n", cnt);
}