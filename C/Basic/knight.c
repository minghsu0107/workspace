#include <stdio.h>
int grid[105][105][2]={};
int canMove[10001];
int chess[10001][2];
int stepcnt[10001];

int judge(int m){
    int count=0;
    for(int i=1;i<=m;i++){
        if(canMove[i]==0) count++;
    }
    if(count==m) return 0;
    return 1;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&chess[i][0],&chess[i][1]);
        canMove[i]=1;
        stepcnt[i]=0;
        grid[chess[i][0]][chess[i][1]][0]=i;
        grid[chess[i][0]][chess[i][1]][1]=0;
    }
    int dx[9]={0,-2,-1,1,2,2,1,-1,-2};
    int dy[9]={0,1,2,2,1,-1,-2,-2,-1};
    //int dir[9][2]={{0,0},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
    
    while(judge(m)){
        for(int i=1;i<=m;i++){
           if(!canMove[i]) continue;
           int count=0;
           int minp=100;
           int s=-1;
           for(int k=1;k<=8;k++){
              int tmpr=chess[i][0]+dx[k];
              int tmpc=chess[i][1]+dy[k];
              if(tmpr < 0 ||
                 tmpr >=n || 
                 tmpc < 0 || 
                 tmpc >=n || 
                 grid[tmpr][tmpc][0]>0){
                   count++;
                   continue;
              }
              int p=0;
              for(int z=1;z<=8;z++){
                   if(tmpr+dx[z]< 0 ||
                      tmpr+dx[z]>=n || 
                      tmpc+dy[z]< 0 || 
                      tmpc+dy[z]>=n || 
                      grid[tmpr+dx[z]][tmpc+dy[z]][0]>0 ) continue;
                   p++;
              }
              if(p<minp){
                  minp=p;
                  s=k;
              }
           }
           if(count==8) canMove[i]=0;
           else{
                 chess[i][0]+=dx[s];
                 chess[i][1]+=dy[s];
                 stepcnt[i]++;
                 grid[chess[i][0]][chess[i][1]][0]=i;
                 grid[chess[i][0]][chess[i][1]][1]=stepcnt[i];
           }
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d",10000*grid[i][j][0]+grid[i][j][1]);
            if(j<n-1) printf(" ");
        }
        puts("");
    }
    return 0;
}
