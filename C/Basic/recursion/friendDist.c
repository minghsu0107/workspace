#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

char isFriend[16][16] = {0};
int N, M, bound = INT_MAX;
int test[16], ans[16];
bool Used[16];

void Ordering(int d, int dist) {
    if (dist >= bound) return;
    if (d == N) {
        if (dist < bound) {
            bound = dist;
            for (int i = 0; i < N; i++) ans[i] = test[i];
        }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (Used[i]) continue;
        int tmpDist = dist;
        for (int j = 0; j < d; j++) {
            if (isFriend[i][test[j]])
               if (d - j > tmpDist) tmpDist = d - j;
        }
 
        Used[i] = true;
        test[d] = i;
        Ordering(d + 1, tmpDist);
        Used[i] = false;
    }
}
 
int main(){
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        char x[2], y[2];
        scanf("%s%s", x, y);
        int a = x[0] - 'A', b = y[0] - 'A';
        isFriend[a][b] = isFriend[b][a] = 1;
    }
    Ordering(0, 0);
    printf("%d\n", bound);
    for (int i = 0; i < N; i++) 
        printf("%c%c", ans[i] + 'A', (i != N - 1) ? ' ': '\n');
    return 0;
}