#include <stdio.h>
#include <stdlib.h>
#define INF 500000; 
typedef struct rice {
    int price, weight, num;
} rice;
 
void dynamic(rice *rices, int n, int m)
{
    int i, j, cur, k, **dp;
 
    // 动态申请二维数组
    dp = (int **)malloc(sizeof(int *)*(n+1));
    for (i = 0; i <= n; i ++)
        dp[i] = (int *)malloc(sizeof(int)*(m+1));
 
    // 初始化
    for (i = 0; i <= n; i ++)
      for (j = 0; j <= m; j ++) 
         dp[i][j] = 0;
 
    // 动态规划
    for (i = 0; i < n; i ++) {
        for (j = 1; j <= m; j ++) {
            for (k = 0; k <= rices[i].num; k ++) {
                if (j >= k * rices[i].weight ) {
                    cur = dp[i][j - k * rices[i].weight] + k * rices[i].price;
                    dp[i+1][j] = dp[i+1][j] > cur ? dp[i+1][j] : cur;
                } 
            }
        }
    }
 
    printf("%d\n", dp[n][m]);
    free(dp);
}
 
 
int main(void)
{
    int i, c, n, m;
     
    rice rices[2010];
 
    scanf("%d", &c);
 
    while (c --) {
        scanf("%d %d", &n, &m);
 
        for (i = 0; i < n; i ++) {
            int price, weight, num;
            scanf("%d %d %d", &price, &weight, &num);
            rices[i].price = price;
            rices[i].weight = weight;
            rices[i].num = num;
        }
 
        // 多重背包 (01 bag 變形)
        dynamic(rices, n, m);
    }
 
 
    return 0;
}
