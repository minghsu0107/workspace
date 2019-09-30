#include <stdio.h>
int main(){
  int N,M;
  int index;
  int x=0;
  int y=0;
  int flag=0;
  scanf("%d%d",&N,&M);
  printf("%d\n%d\n",x,y);
  while(scanf("%d",&index)!=EOF){
     int move=index%5;
     switch(move){
       case 0:
         flag=0;
         break;
       case 1:
         if (x+index < N){
             x+=index; 
             flag=1;
             break;
         }else{
             flag=0;
             break;
         }
       case 2:
         if (x-index >= 0){
             x-=index; 
             flag=1;
             break;
         }else{
             flag=0;
             break;
         }
       case 3:
         if (y+index < M){
             y+=index; 
             flag=1;
             break;
         }else{
             flag=0;
             break;
         }
       case 4:
         if (y-index >= 0){
             y-=index; 
             flag=1;
             break;
         }else{
             flag=0;
             break;
         }
       default:
         break;
     }
     if(flag) printf("%d\n%d\n",x,y);
  }
  
  return 0;
}