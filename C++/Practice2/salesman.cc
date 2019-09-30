#include <bits/stdc++.h>
using namespace std;

int d[15][(1<<15)]; 
int dist[15][15], n;

int dp(int i, int s) {
    // printf("%d %d\n", i, s);
    if(__builtin_popcount(s) == 1) return dist[i][0];
    if (d[i][s] == -1) {
       d[i][s] = 1e9; // 10 ^ 9
       for (int j = 0 ; j < n ; j++) {
           if (j != i && (s & (1 << j))) {
              d[i][s] = min(d[i][s], dp(j, s ^ (1 << i)) + dist[i][j]); 
              //  or using s & ~(1 << i)
           }
       }
    }
    return d[i][s];
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    memset(d, -1, sizeof(d));
    printf("%d", dp(0, (1 << n) - 1));
}