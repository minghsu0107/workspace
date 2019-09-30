#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAXN 64
typedef struct Pt {
    int x, y;
} Pt;
int N, M, K;
int C[MAXN], R[MAXN], D1[MAXN*2], D2[MAXN*2];
int g[MAXN][MAXN];
int isvalid(int x, int y) {
    return R[x] < K && C[y] < K && D1[x+y] < K && D2[x-y+MAXN] < K;
}
int dfs(Pt list[], int n, int k) {
    if (k == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%c", g[i][j] ? 'o' : '.');
            puts("");
        }
        return 1;
    }
    if (n < k || n == 0)
        return 0;
    Pt next[256];
    int m = 0, x = list[0].x, y = list[0].y;
    R[x]++, C[y]++;
    D1[x+y]++, D2[x-y+MAXN]++;
    g[x][y] = 1;
    for (int i = 1; i < n; i++) {
        if (isvalid(list[i].x, list[i].y))
            next[m++] = list[i];
    }
    if (dfs(next, m, k-1))
        return 1;
    R[x]--, C[y]--;
    D1[x+y]--, D2[x-y+MAXN]--;
    g[x][y] = 0;
    return dfs(list+1, n-1, k);
}
int main() {
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
        memset(C, 0, sizeof(C));
        memset(R, 0, sizeof(R));
        memset(D1, 0, sizeof(D1));
        memset(D2, 0, sizeof(D2));
        memset(g, 0, sizeof(g));
 
        Pt list[1024];
        int n = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                list[n].x = i, list[n].y = j;
                n++;
            }
        }
        int ret = dfs(list, n, M);
        if (!ret)
            puts("N");
    }
    return 0;
}