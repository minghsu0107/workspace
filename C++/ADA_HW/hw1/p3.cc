#include <bits/stdc++.h>
#define N 500010
using namespace std;
typedef long long  ll;
const int INF = 1e9;
ll ans = 0;
int n, M, m, low, up, p1, p2;
int arr[N], Max[N], Min[N], query[N<<1];

void get_min_max(int l, int mid, int r) {
	M = -INF, m = INF;
	for (int i = mid; i >= l; --i) {
		M = max(M, arr[i]), m = min(m, arr[i]);
		Max[i] = M, Min[i] = m;
	}
	M = -INF, m = INF;
	for (int i = mid + 1; i <= r; ++i) {
		M = max(M, arr[i]), m = min(m, arr[i]);
		Max[i] = M, Min[i] = m;
	}
}

void solve(int l, int r) {
	if (l == r) {
		++ans;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	get_min_max(l, mid, r);
	
	// case1: m left, M left
	for (int i = l; i <= mid; ++i) {
		up = i + Max[i] - Min[i];
		if (up <= r && up > mid && Max[i] > Max[up] && Min[i] < Min[up])
			++ans;
	}
	// case2: m right, M left 
	for (int i = mid + 1; i <= r; ++i) {
		low = i - Max[i] + Min[i];
		if (low >= l && low <= mid && Max[i] > Max[low] && Min[i] < Min[low])
			++ans;
	}
	
	// case3: m left, M right
	p1 = p2 = mid;
	for (int i = mid + 1; i <= r; ++i) {		
		while (p1 >= l && Max[p1] < Max[i]) {
			query[p1 - Min[p1] + n] = 0;
			--p1;
		}
		while (p2 >= l && Min[p2] > Min[i]) {
			query[p2 - Min[p2] + n] = 0;
			--p2;
		}
		query[i - Max[i] + n] = 0;
	}
	p1 = p2 = mid;
	for (int i = mid + 1; i <= r; ++i) {
		// valid
		while (p1 >= l && Max[p1] < Max[i]) {
			++query[p1 - Min[p1] + n];
			--p1;
		}
		// invalid
		while (p2 >= l && Min[p2] > Min[i]) {
			--query[p2 - Min[p2] + n];
			--p2;
		}
		if (p1 == -1 && p2 == -1) break;
		if (p1 <= p2)
			ans += query[i - Max[i] + n];
	}
	
	// case4: m right, M left
	p1 = p2 = mid + 1;
	for (int i = mid; i >= l; --i) {
		while (p1 <= r && Max[p1] < Max[i]) {
			query[p1 + Min[p1]] = 0;
			++p1;
		}
		while (p2 <= r && Min[p2] > Min[i]) {
			query[p2 + Min[p2]] = 0;
			++p2;
		}
		query[i + Max[i]] = 0;
	}
	p1 = p2 = mid + 1;
	for (int i = mid; i >= l; --i) {
		// valid
		while (p1 <= r && Max[p1] < Max[i]) {
			++query[p1 + Min[p1]];
			++p1;
		}
		// invalid
		while (p2 <= r && Min[p2] > Min[i]) {
			--query[p2 + Min[p2]];
			++p2;
		}
		if (p1 == r + 1 && p2 == r + 1) break;
		if (p1 >= p2)
			ans += query[i + Max[i]];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	solve(0, n - 1);
	cout << ans << '\n';
}
/*
if r - l = max([l, r]) - min([l, r]), this segment is good

we first maintain two arrays Max[] and Min[], 
where Max[i] = max([i, mid]) if l <= i <= mid, 
and Max[j] = max([mid+1, j]) if mid + 1 <= j <= r
same is Min[]

using divide and conquer
base case: l == r gives 1 solution 
when combining left and right, there are 4 cases
case 1:
min and max of [i, j] are both on the left interval([l, mid])
where l <= i <= mid, mid + 1 <= j <= r
case 2:
both on the right
case 3:
min on the left and max on the right
case 4:
min on the right and max on the left

for case 1 and case2, we iterate through left / right interval
we are given (li, M, m) / (ri, M, m) during each iteration, and
we can get possible r' / l' by r' = li + M - m / l' = ri - M + m for each li / ri
however, we should check wether:
1. r' / l' is on [mid + 1, r] / [l, mid]
2. Max[li] > Max[r'] && Min[li] < Min[r'] / Max[ri] > Max[l'] && Min[ri] < Min[l']
if both conditions are reached, this r' / l' is a solution

for case 3 and case 4, we still iterate through right / left interval
we discover that Max is increasing / Min is decreasing when we move away from mid(monotone)
so we can use two pointers to maintain the possible interval on the left / right interval
one pointer for checking Max and one pointer for checking min
the direction of the pointers should be in consistency with the direction of iteration
so that we can update the pointers in next iteration

we can see that r - M = l - m / l + M = r + m
so we use query[] to save the count of l' - m / r' + m 
where l' / r' are in the possible left / right interval
in this way, we can use query[r - M] / query[l + M] to get the number of solutions in O(1)

note
case3: since we iterate right inteval, we should query r - M not r + m 
(M is on the right so it is already given during each iteration)
case4: since we iterate left interval, we should query l + M not l - m
*/