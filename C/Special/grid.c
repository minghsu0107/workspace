#include <stdio.h>
#include <string.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
int grid[105][105];
int d(int x, int y, int dp[][105]){
  for (int i = 0; i < x; i++) {
      if (dp[i][0] == -1) break;
      dp[i][0] = 1;
  }
  for (int i = 0; i < y; i++) {
      if (dp[0][i] == -1) break;
      dp[0][i] = 1;
  }
  for (int i = 1; i < x; i++) {
      for(int j = 1; j < y;j++) {
         if (dp[i][j] == -1)continue;
         if (dp[i-1][j] != -1) dp[i][j] += dp[i-1][j];
         if (dp[i][j-1] != -1) dp[i][j] += dp[i][j-1];
         dp[i][j] %= 10000;
      }
  }
  return dp[x-1][y-1];
}
int main(){
  int x, y;
  while (scanf("%d%d", &x, &y) == 2) {
        int dp[105][105] = {};
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                scan(grid[i][j]);
                if (grid[i][j]) dp[i][j] = -1;
            }
        }
        printf("%d\n", d(x, y, dp));
  }
  return 0;
}