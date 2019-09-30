#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 5;

int arr[N], dp[N][N];

int main() {
	int t; 
	scanf("%d", &t);
	while (t--) {
		int n, m; 
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", arr+i);
		for (int i = 1; i <= n; i++) dp[i][i] = 1;
		for (int i = n; i >= 1; i--) {
			for(int j = i + 1; j <= n; j++) {
				dp[i][j] = 1<<25;
				for(int k = i; k + 1 <= j; k++)
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
				if(arr[i] == arr[j]) dp[i][j]--;
			}
		}
		printf("%d\n", dp[1][n]);
	}
	return 0;
}
// dp[i][j] = min(dp[i][k]+dp[k+1][j]) − [ai==aj](其中[]是艾佛森括號)，i≤k<j
// 然後dp[i][j]的意思是把[i,j]填滿的最小步數，
// 轉移方法就是枚舉中點，代表先把[i,k]填好再填[k+1,j]，
// 而減一的部份則是因為明顯若首尾相同，
// 那我們在填左邊的時候就可以順便拉一條過去到右邊，就不需要右邊又在畫一遍了。 