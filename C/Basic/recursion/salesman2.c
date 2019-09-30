#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX 14
// d[i][j] saves the shortest distance from i to 0; 
// j indicates the visited citites
// i^th bit in j indicates whether the i^th city is visited (1 == visited)
int dist[MAX][MAX] = {};
int dp[MAX][(1 << MAX)];
int N;
int min(int x, int y) { return x < y ? x : y; }
// find returns the shortest distance from now to 0 after visiting every city once
int find(int now, int v) {
    if (v == (1 << N) - 1) { 
       return dist[now][0];
    }
    if (dp[now][v] == -1) {
       dp[now][v] = INT_MAX;
       for (int i = 1; i < N; i++) {
           if (i != now && !((v >> i) & 1)) {
              dp[now][v] = min(dp[now][v], dist[now][i] + find(i, v | (1 << i)));
           }
       }
    }
    return dp[now][v];
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &dist[i][j]); 
    memset(dp, -1, sizeof(dp));
    find(0, 1); // set 0 as the starting point; initial status: 0^th city is visited
    printf("%d", dp[0][1]);
    return 0;
}