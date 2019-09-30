#include<bits/stdc++.h>
using namespace std;
int dp[2][4][4][4][4];// 滾動數組
int n, s, k, mx;
inline void scan(int &x) {
    x=0;
    while(x!='B'&&x!='F'&&x!='M')x=getchar();
    x=(x=='B'?1:(x=='F'?2:3));
}
inline int PC(int x,int y,int z) {
    int tot = 0;
    if(x) tot++;
    if(y && y != x) tot++;
    if(z && z!=y && z!=x) tot++;
    return tot;
}
/*
inline int PC2(int x, int y, int z) {
    int tot = 0;
    for (int i = 1; i <= 3; ++i)
        if (x == i || y == i || z == i) tot++;
    return tot;
}
*/
int main(){
    scanf("%d", &n);
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= n; i++, k^=1) {
        scan(s);
        if(i == 1) {
            dp[k^1][0][s][0][0] = dp[k^1][0][0][0][s] = 1;
            continue;
        }
        for (int a = 0; a <= 3; a++)
            for (int b = 0; b <= 3; b++)
                for (int c = 0; c <= 3; c++)
                    for (int d = 0; d <= 3; d++) {
                        if (dp[k][a][b][c][d] != -1) {
                            dp[k^1][b][s][c][d] = max(dp[k][a][b][c][d]+PC(a,b,s), dp[k^1][b][s][c][d]);
                            dp[k^1][a][b][d][s] = max(dp[k][a][b][c][d]+PC(c,d,s), dp[k^1][a][b][d][s]);
                        }
        }
        memset(dp[k], -1,sizeof(dp[k]));
    }
    for (int a = 0; a <= 3; a++)
        for (int b = 0; b <= 3; b++)
            for (int c = 0; c <= 3; c++)
                for (int d = 0; d <= 3; d++)
                    mx = max(mx, dp[k][a][b][c][d]);
    printf("%d\n",mx);
    return 0;
}
/*
我们令一个数字表示一种食物。

设dp(i,a,b,c,d)
表示运完第i辆食物,煤矿1的上次食物是b,上上次是a,煤矿2的上次食物是d,上上次是c

设第x次的食物是fx,令i,j,k中不同食物的数量是PC(i,j,k),我们枚举a,b,c,d

,得到转移

dp(x,b,fx,c,d)=max{dp(x−1,a,b,c,d)+PC(a,b,fx)}

dp(x,a,b,d,fx)=max{dp(x−1,a,b,c,d)+PC(a,b,fx)}

*/