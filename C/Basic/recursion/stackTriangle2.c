#include <stdio.h>
#define MAXN 200
// dp method 
int main()
{
    int n;
    scanf("%d", &n);
    int w[MAXN], l[MAXN];
    int a, b;
    for ( int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        w[i] = a >= b ? a : b;
        l[i] = a < b ? a : b;
    }
    int num[MAXN], sum[MAXN];
    int max_num = 0, max_sum = 0;
    for ( int i = n - 1; i >= 0; i--) {
        int num_add = 0, sum_add = 0;
        for ( int j = i + 1; j < n; j++)
            if ( w[j] <= w[i] && l[j] <= l[i] )
                if ( num[j] > num_add || (num[j] == num_add && sum[j] > sum_add) ) {
                    num_add = num[j];
                    sum_add = sum[j];
                }
        num[i] = 1 + num_add;
        sum[i] = i + sum_add;
        if ( num[i] > max_num || (num[i] == max_num && sum[i] > max_sum ) ) {
            max_num = num[i];
            max_sum = sum[i];
        }
    }
    printf("%d %d\n", max_num, max_sum);
    return 0;
}