#include<stdio.h>
int N;
void upperRight(int x, int y, int* newX, int* newY){
    *newX = (x-1+N)%N, *newY = (y+1)%N;
}
void down(int x, int y, int* newX, int* newY){
    *newX = (x+1)%N;
    *newY = y;
}
void lowerLeft(int x, int y, int* newX, int* newY){
    *newX = (x+1)%N;
    *newY = (y-1+N)%N;
}
//void up(int x, int y, int* newX, int* newY){
//    *newX = (x-1+N)%N;
//    *newY = y;
//}
int main()
{
  int grid[1000][1000]={},k,x,y;
  scanf("%d%d%d%d",&N,&k,&x,&y);
  for(int i=1;i<k;i++){
      int newX,newY;
      lowerLeft(x,y,&newX,&newY);
      x= newX, y=newY;
      //if(grid[x][y]) up(x,y,&newX,&newY); 
      //x = newX, y = newY;
  }
  grid[x][y]=1;
  int count=1;
  while(count<N*N){
     int newX,newY;
     upperRight(x,y,&newX,&newY);
     if(grid[newX][newY]) down(x,y,&newX,&newY);
     x=newX, y=newY;
     grid[x][y]=++count;
  }
  for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
          printf("%d%c",grid[i][j]," \n"[j==N-1]);
  return 0;
}
