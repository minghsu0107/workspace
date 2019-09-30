#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAXN 64
int N, M, K;
int C[MAXN], R[MAXN], D1[MAXN*2], D2[MAXN*2];
int g[MAXN][MAXN];
int isvalid(int x, int y) {
    return R[x] < K && C[y] < K && D1[x+y] < K && D2[x-y+MAXN] < K;
}
int dfs(int x, int y, int k) {
    if (k == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%c", g[i][j] ? 'o' : '.');
            puts("");
        }
        return 1;
    }
    if (y == N)
        x++, y = 0;
    if (x == N)
        return 0;
    if (isvalid(x, y)) {
        R[x]++, C[y]++, D1[x+y]++, D2[x-y+MAXN]++;
        g[x][y] = 1;
        if (dfs(x, y+1, k-1))
            return 1;
        g[x][y] = 0;
        R[x]--, C[y]--, D1[x+y]--, D2[x-y+MAXN]--;
    }
    return dfs(x, y+1, k);
}
int main() {
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
        memset(C, 0, sizeof(C));
        memset(R, 0, sizeof(R));
        memset(D1, 0, sizeof(D1));
        memset(D2, 0, sizeof(D2));
        memset(g, 0, sizeof(g));
        int ret = dfs(0, 0, M);
        if (!ret)
            puts("N");
    }
    return 0;
}