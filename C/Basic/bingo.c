#include <stdio.h>
#include "omp.h"
int arr[256][256][10],n,m;
int pos[10][256*256][2];
char name[10][65];

int checkJ(int i,int j,int k){
   int good=1;
   for(unsigned int y=0;y<m;y++){
      if(arr[i][y][k]!=0){
          good=0;
          break;
      }
   }
   if(good==1) return 1;
   else return 0;
}
int checkI(int i,int j,int k){
   int good=1;
   for(unsigned int x=0;x<m;x++){
      if(arr[x][j][k]!=0){
          good=0;
          break;
      }
   }
   if(good==1) return 1;
   else return 0;
}
int checkCross(int i,int j,int k){
   if(!(i==j) && !(i==m-1-j) ) return 0;
   int good=1;
   for(unsigned int x=0;x<m;x++){
       if(arr[x][x][k]!=0){
           good=0;
           break;
       }
   }
   if(good==1) return 1;
   good=1;
   for(unsigned int x=0;x<m;x++){
      if(arr[x][m-1-x][k]!=0){
          good=0;
          break;
      }
   }
   if(good==1) return 1;
   return 0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%s",name[i]);
        for(int p=0;p<m;p++){
            for(int q=0;q<m;q++){
                scanf("%d",&arr[p][q][i]);
                pos[i][arr[p][q][i]][0]=p;
                pos[i][arr[p][q][i]][1]=q;
            }
        }
    }
    int num,bingo=0;
    for(int z=0;z<m*m && !bingo;z++){
        scanf("%d",&num);
        for(int k=0;k<n;k++){
            arr[pos[k][num][0]][pos[k][num][1]][k]=0;
             if(checkJ(pos[k][num][0],pos[k][num][1],k) || 
                checkI(pos[k][num][0],pos[k][num][1],k) || 
                checkCross(pos[k][num][0],pos[k][num][1],k)){
                if(bingo==0){
                    printf("%d",num);
                    bingo=1;
                }
                printf(" %s",name[k]);
             }
        }
    }
    return 0;
}
