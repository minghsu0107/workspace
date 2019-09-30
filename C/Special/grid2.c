#include <stdio.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
int main(void) {
    int n ,m, i, j;
    while (scanf("%d%d", &n, &m) == 2) {
          int map[102][102] = {0};
          map[1][1] = 1;
          for (i = 1; i <= n; i++) {
              for (j = 1; j <= m; j++){
                  int x;
                  scan(x);
                  if(!x) map[i][j] += (map[i-1][j] + map[i][j-1]) % 10000;
              }
          }
          printf("%d\n", map[n][m] % 10000);
    }
    return 0;
}