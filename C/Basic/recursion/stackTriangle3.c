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
void dp(int n) {
    arr[n - 1].num = 1, arr[n - 1].sum = n - 1;
    rec result = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        rec M;
        M.num = 0, M.sum = 0;
        for (int j = i + 1; j < n; j++) {
            if (w[j] <= w[i] && l[j] <= l[i]) {
                M = max(M, arr[j]);
            }
        }
        arr[i].num = 1 + M.num;
        arr[i].sum = i + M.sum;
        result = max(result, arr[i]);
    }
    printf("%d %d\n", result.num, result.sum);
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
    dp(n);
    return 0;
}