#include <stdio.h>
int donation[64], adjac[64][64], chosen[64] = {};
int n, d, max = 0;
int check(int intput, int dimension) {
    for (int j = 0; j < dimension; j++) {
        if (chosen[j] && adjac[intput][j]) return 0;
    }
    return 1;
}
void dfs(int d, int m) {
    if (m > max) max = m;
    for (int i = d; i < n; i++) {
        if (check(i, d)) {
            chosen[i] = 1;
            dfs(i + 1, m + donation[i]);
            chosen[i] = 0;
        }        
    }
}
int main(int argc, char const *argv[])
{
 
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &donation[i]);
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &adjac[i][j]);
        }
    }
    dfs(0, 0);
    printf("%d", max);
    return 0;
}
// 如果已經知道將某個人放入目前集合會導致集合內至少兩個人彼此討厭
// 麼就停止讓函式再遞迴下去以免做沒意義的函式呼叫