#include <stdio.h>
#include <string.h>
int arr[16][16];
int grid2(int i,int j){
  if (i==0) return 1;
  if (j==0) return 1;
  if (arr[i][j]==-1){
    arr[i][j]=grid2(i-1,j)+grid2(i,j-1);
  }
  return arr[i][j];
}
 
int main(){
  int x,y;
  scanf("%d%d",&x,&y);
  memset(arr,-1,sizeof(arr));
  printf("%d",grid2(x-1,y-1));
  return 0;
}
