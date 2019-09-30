/*
給定一行n個整數，現在你可以選擇其中若幹個數，
但不能有連續k個數被選擇。你的任務是使得選出的數字的和最大
*/
#include<bits/stdc++.h>
#define maxn 2000005
#define ll long long
using namespace std;
int head = 0, tail = 1, n, k;
ll dp[maxn], f[maxn], sum[maxn];
int a[maxn], q[maxn];

// size of the deque should <= k+1
ll get_max(int i) {
    f[i] = dp[i-1] - sum[i];
    //維護單調隊列，將小於f[i]的數都踢出去
    while(head <= tail && f[q[tail]] <= f[i]) tail--;
    q[++tail] = i;

    //如果隊首的元素已經不在範圍裏 踢出隊列
    while(q[head] < i-k) head++;
    return f[q[head]];
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = get_max(i) + sum[i];
    }
    cout << dp[n] << endl;
    return 0;
}
/*
定義：dp[i]表示前i個人的最大收益，sum[i]表示前綴和

現在選的這一段區間和用sum[i]-sum[j]表示（i-k<=j<=i）

這段區間與 前一段長為k的區間 中間要空一個數（不能連續選k+1個數），
於是我們固定i點，不斷地枚舉j點，找到和的最大值
因為sum求的是閉區間的前綴和 ， sum[i]-sum[j]表示區間[ j+1 ,i ]的和，
中間空的數就是j，再加上dp[j-1]就可以更新dp[i]的值
我們可以得到狀態轉移方程

dp[i] = max(dp[j-1] + sum[i]-sum[j]) (i-k <= j <= i）
when j == i, it means the situation where we do not choose a[i]

定義f[j]=dp[j-1]-sum[j]，將f[j]丟進單調隊列裏面，每次取出隊首元素

對於一類dp，狀態轉移方程抽象為：dp[i]=max(f[j])+g[i] (l[i]<=j<=r[i])
並且l[i]~r[i]單調不減時，我們都可以考慮用單調隊列優化
步驟：踢出過時元素，更新dp值，新元素入隊並且維護單調隊列
*/