#include <stdio.h>
#include <string.h>
int grid[16][16], x, y; // 全域陣列內容自動初始為0
int count = 0;
void grid2(int i,int j){
  if (i == x-1 && j == y-1){
      count++;
      return;
  }
  if(i < x && grid[i+1][j]==1) grid2(i+1,j);
  if(j < y && grid[i][j+1]==1) grid2(i,j+1);
}
int dfs(int i,int j){
  int k = 0;
  if (i == x-1 && j == y-1){
      return 1;
  }
  if(i < x && grid[i+1][j]==1) k += dfs(i+1,j);
  if(j < y && grid[i][j+1]==1) k += dfs(i,j+1);
  return k;
}
int main(){
  scanf("%d%d",&x,&y);
  for(int i = x-1; i >= 0; i--){
      for(int j = 0; j < y; j++){
          scanf("%d",&grid[i][j]);
      }
  }
  grid2(0,0);
  printf("%d\n",count);
  printf("%d\n",dfs(0,0));
  return 0;
}
