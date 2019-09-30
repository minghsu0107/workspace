#include <stdio.h>
int grid[3][3]={};
int judge(){
  int ch, cnt=0;
  for(int i=0;i<3;i++){
       for(int j=0;j<2;j++){
          if(grid[i][j]!=grid[i][j+1]) break;
          else{
              if(grid[i][j]==0) break;
              cnt++;
              ch=grid[i][j];
          }
       }
       if(cnt==2) return ch;
   }
   cnt=0;
   for(int j=0;j<3;j++){
       for(int i=0;i<2;i++){
          if(grid[i][j]!=grid[i+1][j]) break;
          else{
              if(grid[i][j]==0) break;
              cnt++;
              ch=grid[i][j];
          }
       }
       if(cnt==2) return ch;
   }
   cnt=0;
   for(int i=0;i<2;i++){
       if(grid[i][i]!=grid[i+1][i+1]){
           break;
       }
       else{
           if(grid[i][i]==0) break;
           cnt++;
           ch=grid[i][i];
       }
   }
   if(cnt==2) return ch;
   cnt=0;
   for(int i=2;i>0;i--){
      if(grid[i][2-i]!=grid[i-1][3-i]) break;
      else{
          if(grid[i][2-i]==0) break;
          cnt++;
          ch=grid[i][2-i];
      }
   }
   if(cnt==2) return ch;
   return 0;
}
int main(){
   int n,x,y;
   scanf("%d",&n);
   int times=0;
   for(int i=0;i<n;i++){
       scanf("%d%d",&x,&y);
       if(x>2 || x<0 || y>2 || y<0) continue;
       if(grid[x][y]!=0) continue;
       if(times%2==0) grid[x][y]=1;
       else grid[x][y]=2;
       times++;
       if(times>=5){
          int p=judge();
          if(p==1){
              printf("Black wins.");
              break;
          } 
          else if(p==2){ 
              printf("White wins."); 
              break;
          }
       }
   }
   if (times<=9 && judge()==0) printf("There is a draw.");
   return 0;
}