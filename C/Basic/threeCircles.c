#include <stdio.h>
#include <stdlib.h>
int isIn(int x, int y,int r, int i, int j){
    if(abs(x-i)>10 || abs(y-j)>10) return 0;
    if((x-i)*(x-i)+(y-j)*(y-j)<=r*r) return 1;
    else return 0;
}

int main(){
    int number;
    int x1,y1,r1,x2,y2,r2,x3,y3,r3;
    scanf("%d",&number);
    while(number--){
        scanf("%d%d%d%d%d%d%d%d%d",&x1,&y1,&r1,&x2,&y2,&r2,&x3,&y3,&r3);
        int cA=0;
        int cB=0;
        int cC=0;
        int cABC=0;
        for(int i=x1-r1;i<=x1+r1;i++){
            for(int j=y1-r1;j<=y1+r1;j++){
               if(isIn(x1,y1,r1,i,j) && !isIn(x2,y2,r2,i,j) && !isIn(x3,y3,r3,i,j) ){
                   cA++;
               } 
               if(isIn(x1,y1,r1,i,j) && isIn(x2,y2,r2,i,j) && isIn(x3,y3,r3,i,j) ){
                   cABC++;
               } 
            }
        }
        for(int i=x2-r2;i<=x2+r2;i++){
            for(int j=y2-r2;j<=y2+r2;j++){
              if(isIn(x2,y2,r2,i,j) && !isIn(x1,y1,r1,i,j) && !isIn(x3,y3,r3,i,j) ){
                  cB++;
              }  
            }
        }
        for(int i=x3-r3;i<=x3+r3;i++){
            for(int j=y3-r3;j<=y3+r3;j++){
                if(isIn(x3,y3,r3,i,j) && !isIn(x2,y2,r2,i,j) && !isIn(x1,y1,r1,i,j) ){
                  cC++;
                }
            }
        }
        //printf("%d %d %d %d",cA,cB,cC,cABC);
        printf("%d\n",cA+cB+cC+cABC);
    }
    return 0;
}