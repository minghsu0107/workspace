#include <stdio.h>
int findLength (int arr[][256], int n, int r, int c, int dr, int dc){
    int max=0, len=0;
    if(dr == 0 && dc == 1){
        if(arr[r][c]==1){
            len = 1, max = len;
        }
        for(int j=c+1;j<n;j++){
          if(arr[r][j]==1){
              if(arr[r][j]==arr[r][j-1]) len++;
              else len=1;
              max=len>max? len: max;
          }
        }
        return max;
    }
    else if(dr == 1 && dc == 0){
          if(arr[r][c]==1){
              len = 1, max = len;
          }
          for(int i=r+1;i<n;i++){
             if(arr[i][c]==1){
                  if(arr[i][c]==arr[i-1][c]) len++;
                  else len=1;
                  max=len>max? len: max;
             }
          }
          return max;
    }
    else if(dr == 1 && dc == 1){
      if(arr[r][c]==1){
          len = 1, max = len;
      }
      int x=r+1,y=c+1;
      while(x<n && y<n){
        if(arr[x][y]==1){
          if(arr[x][y]==arr[x-1][y-1]) len++;
          else len=1;
          max=len>max? len:max;
        }
        x++;
        y++;
      }
      return max;
    }
    else{
      if(arr[r][c]==1){
          len = 1, max = len;
      }
      int x=r-1,y=c+1;
      while(x>=0 && y<n){
        if(arr[x][y]==1){
          if(arr[x][y]==arr[x+1][y-1]) len++;
          else len=1;
          max=len>max? len:max;
        }
        x--;
        y++;
      }
      return max;
    }
}
int main() {
    int n,r,c;
    int arr[256][256];
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&arr[i][j]);
        }
    }
    scanf("%d%d",&r,&c);
    int dirr[4] = {1,0,1,-1};
    int dirc[4] = {0,1,1,1};
    int max=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           for(int k=0;k<4;k++){
              int tmp = findLength(arr, n, i, j, dirr[k], dirc[k]);
              max = tmp > max ? tmp : max;
           }
        }
    }
    printf("%d",max);
    return 0;
}
