#include <stdio.h>
#include <limits.h>
#define MAXN 200
int w[MAXN], l[MAXN];
typedef struct rec {
    int num, sum;
} rec;
rec arr[MAXN];
rec max(rec x, rec y) { 
    if (y.num > x.num) return y;
    else if (y.num == x.num) return y.sum > x.sum ? y : x;
    else return x;
}
rec dp(int d, int n) {
    if (d == n - 1) {
       return arr[n - 1];
    }
    if (arr[d].num == -1) {
       rec M;
       M.num = 0, M.sum = 0;
       for (int j = d + 1; j < n; j++) {
           if (w[j] <= w[d] && l[j] <= l[d]) {
               M = max(M, dp(j, n));
           }
       }
       arr[d].num = 1 + M.num;
       arr[d].sum = d + M.sum;
    }
    return arr[d];
}
int main() {
    int n;
    scanf("%d", &n);
    int a, b;
    for ( int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        w[i] = a >= b ? a : b;
        l[i] = a < b ? a : b;
    }
    for (int i = 0; i < n - 1; i++) {
        arr[i].num = -1, arr[i].sum = -1;
    }
    arr[n - 1].num = 1, arr[n - 1].sum = n - 1;
    rec result = arr[n - 1];
    for (int i = 0; i < n; i++) {
        result = max(result, dp(i, n));
    }
    printf("%d %d\n", result.num, result.sum);
    return 0;
}