// at least one element is separated from others
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int N = 1000000 + 5;
const lld INF = 1LL<<60;
lld arr[N], sum[N], dp[N];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	for(int i = 1; i <= n; i++) cin >> arr[i];

	lld cnt = 0, mm = -INF;
	for(int i = 1; i <= n; i++) {
		cnt += arr[i];
		mm = max(cnt, mm);
		if(cnt < 0) cnt = 0;
		sum[i] = mm;
	}

	dp[0] = -INF; dp[1] = -INF; dp[2] = -INF;
	lld mx = -INF;
	for(int i = 3; i <= n; i++) {
		dp[i] = max(mx + arr[i], sum[i-2] + arr[i]);
		mx = max(mx, dp[i]);
	}

	lld ans = -INF;
	for(int i = 1; i <= n; i++) ans = max(ans, dp[i]);
	cout << ans << '\n';
	return 0;
}

/*
用三個陣列來記錄，arr[i]記錄輸入的數字是多少，
sum[i]記錄從第一個數到第i個數取某些數字(至少取一個)的最大值是多少，(第i個不一定要取)，
sum[1] = arr[1]，
i=2~N時，sum[i] = max(A[i], sum[i-1], A[i] + sum[i-1]),
而 dp[i]記錄以第i個為最後一個的最大不連續和是多少，(第i個一定要取)
dp[3] = arr[1]+arr[3]，i=4~N時，dp[i] = max(dp[k], sum[i-2])+arr[i]，3<=k<=i-1
即可求出答案。

sol2:
枚舉斷點 𝑖 ，
則斷在 𝑖 的答案為 “在 [1,𝑖−1] 中至少選一個的最大值” + “在 [𝑖+1,𝑛] 中至少選一個的最大值” 
pref[1] = arr[1]
for (i = 2; i <= n; ++i) 
    pref[i] = max(arr[i], pref[i - 1], pref[i - 1] + arr[i]);
suff[n] = arr[n]
for (i = n-1; i >= 1; --i) 
    suff[i] = max(arr[i], suff[i + 1], suff[i + 1] + arr[i]);

ans = -inf;
for (i = 2; i < n; ++i) 
    ans = max(ans, pref[i - 1] + suff[i + 1]);
*/