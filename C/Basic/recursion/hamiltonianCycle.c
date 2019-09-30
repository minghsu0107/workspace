#include <stdio.h>
#define maxn 1000
int adj[maxn][maxn];
void printsol(int sol[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", sol[i]);
    printf("0\n");
    return;
}
int mcl(int n, int now, int pick_n, int sol[maxn], int picked[maxn]) {
    if (pick_n == n) {
        if (adj[now][0] == 1) {
            printsol(sol, n);
            return 1;
        }
        else return 0;
    }
    for (int i = 0; i < n; i++) {
        if (!picked[i] && adj[now][i]) {
            sol[pick_n] = i;
            picked[i] = 1;
            if (mcl(n , i, pick_n+1, sol, picked) )
                return 1;
            picked[i] = 0;
        }
    }
    return 0;
}
int main() {
    int n, e;
    scanf("%d%d", &n, &e);
    while(e--) {
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x][y] = 1;
        adj[y][x] = 1;
    }
    int sol[maxn] ={}, picked[maxn] = {};
    sol[0] = 0;
    picked[0] = 1;
    if (!mcl(n, 0, 1, sol, picked))
        printf("NO SOLUTION\n");
    return 0;
}