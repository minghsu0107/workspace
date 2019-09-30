#include <bits/stdc++.h> 
using namespace std; 
const int MAXX=100000+5; 
const int INF=INT_MAX; 
int a[MAXX],dp[MAXX]; // a数组为数据，dp[i]表示长度为i+1的LIS结尾元素的最小值 
int n;
int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = INF;
    }

    int pos = 0; // 记录dp当前最后一位的下标
    dp[0] = a[0]; // dp[0]值显然为a[0]
    for (int i = 1; i < n; i++) { 
        if (a[i] > dp[pos]) // 若a[i]大于dp数组最大值，则直接添加 
            dp[++pos] = a[i]; 
        else // 否则找到dp中第一个大于等于a[i]的位置，用a[i]替换之。 
            dp[lower_bound(dp,dp+pos+1,a[i])-dp] = a[i]; // 二分查找 
    } 
    cout << pos+1 << endl; 
    return 0;

}
// O(nlogn)