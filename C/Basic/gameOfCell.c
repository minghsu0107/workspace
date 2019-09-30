#include<stdio.h>
void game_of_cell(int grid[50][50],int outcome[50][50],int N)
{
  int changeTable[3][9]={      // 查要變成什麼=[原先狀態][四周鄰居存活數量]
  {0,0,0,2,0,0,0,0,0},
  {1,1,2,1,1,1,1,1,1},
  {0,0,2,2,1,1,1,1,1}};
  int boundArray[52][52]={0};
  for(int i=0;i<50;i++)
        for(int j=0;j<50;j++)
                boundArray[i+1][j+1]=grid[i][j];
  for(int n=0;n<N;n++){
      int numAlive[52][52]={0}; // numAlive[i][j]表boundArray[i][j]四周healthy者的數量
      for(int i=1;i<51;i++)
          for(int j=1;j<51;j++)
          {
              numAlive[i][j]+=(boundArray[i-1][j-1]/2);
              numAlive[i][j]+=(boundArray[i-1][j]/2);
              numAlive[i][j]+=(boundArray[i-1][j+1]/2);
              numAlive[i][j]+=(boundArray[i][j-1]/2);
              numAlive[i][j]+=(boundArray[i][j+1]/2);
              numAlive[i][j]+=(boundArray[i+1][j-1]/2);
              numAlive[i][j]+=(boundArray[i+1][j]/2);
              numAlive[i][j]+=(boundArray[i+1][j+1]/2);
 
          }
      for(int i=1;i<51;i++)
          for(int j=1;j<51;j++)
             boundArray[i][j]=changeTable[boundArray[i][j]][numAlive[i][j]];
             //所有cells在當回合結束時才會同時變換狀態 更新boundArray
   }
   for(int i=0;i<50;i++)
      for(int j=0;j<50;j++)
           outcome[i][j]=boundArray[i+1][j+1];

      return;
}
int main()
{
    int grid[50][50]={0},outcome[50][50]={0},N;
    scanf("%d",&N);
    for(int i=0;i<50;i++)
        for(int j=0;j<50;j++)
            scanf("%d",&grid[i][j]);
    game_of_cell(grid,outcome,N);
    for(int i=0;i<50;i++)
        for(int j=0;j<50;j++)
            printf("%d%c",outcome[i][j]," \n"[j==49]);
    return 0;
}
