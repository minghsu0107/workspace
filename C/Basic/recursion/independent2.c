#include <stdio.h> 
#define MAXN 128
int n, m, g[MAXN][MAXN], sol[MAXN];
int findIndepSet(int d, int A[], int sz) {
    if (sz + n - d < m)
        return 0;
    if (sz == m) {
        for (int i = 0; i < sz; i++)
            printf("%d%c", sol[i], i != sz-1 ? ' ' : '\n');
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int next[MAXN], tn = 0;
        for (int j = i + 1; j < n - d; j++) {
            if (g[A[j]][A[i]] == 0)
                next[tn++] = A[j];
        }
        sol[sz] = A[i];
        if (findIndepSet(n - tn, next, sz+1)) return 1;
    }
    return 0;
}

int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        }
        int A[MAXN];
        for (int i = 0; i < n; i++)
            A[i] = i;
        int f = findIndepSet(0, A, 0);
        if (!f)
            printf("no solution\n");
    }
    return 0;
}
// 在遞迴過程中，維護可選的候選名單
// 當加入某一個人 𝑃 進入 independent set 𝑆，則候選名單中若與 𝑃 認識都應替除