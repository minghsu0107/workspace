#include <stdio.h>
int validMoveNum(int r, int c, int n, int visited[100][100]){    
     if(r < 0 || r >=n || c < 0 || c >=n || visited[r][c]>0) return -1;
     int dx[9]={0,-2,-1,1,2,2,1,-1,-2};
     int dy[9]={0,1,2,2,1,-1,-2,-2,-1};
     int count=0;
     for(int k=1;k<=8;k++){
              int tmpr=r+dx[k];
              int tmpc=c+dy[k];
              if(tmpr < 0 ||
                 tmpr >=n ||
                 tmpc < 0 ||
                 tmpc >=n ||
                 visited[tmpr][tmpc]>0){
                   continue;
              }
              count++;
     }
     return count;
}
int nextMove(int r, int c, int n, int visited[100][100]){
     int dx[9]={0,-2,-1,1,2,2,1,-1,-2};
     int dy[9]={0,1,2,2,1,-1,-2,-2,-1};
     int minp=10000;
     int s=-1;
     for(int k=1;k<=8;k++){
              int tmpr=r+dx[k],tmpc=c+dy[k];
              int p=validMoveNum(tmpr,tmpc,n,visited);
              if(p!=-1&&p<minp){
                  minp=p;
                  s=k;
              }
    }  
    return s;
}
 
int main(){
    int grid[105][105][2]={};
    int chess[10001][2];
    int stepcnt[10001];
    int visited[100][100];
    int canMove[10001];
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&chess[i][0],&chess[i][1]);
        canMove[i]=1;
        stepcnt[i]=0;
        grid[chess[i][0]][chess[i][1]][0]=i;
        grid[chess[i][0]][chess[i][1]][1]=0;
        visited[chess[i][0]][chess[i][1]]=1;
    }
    int dx[9]={0,-2,-1,1,2,2,1,-1,-2};
    int dy[9]={0,1,2,2,1,-1,-2,-2,-1};
    int judge=1;
    while(judge){
        for(int i=1;i<=m;i++){
           if(!canMove[i]) continue;
           int s=nextMove(chess[i][0],chess[i][1],n,visited);
           if(s!=-1){
                 chess[i][0]+=dx[s];
                 chess[i][1]+=dy[s];
                 stepcnt[i]++;
                 grid[chess[i][0]][chess[i][1]][0]=i;
                 grid[chess[i][0]][chess[i][1]][1]=stepcnt[i];
                 visited[chess[i][0]][chess[i][1]]=1;
           }
           else canMove[i]=0;
           int ct=0;
           for(int i=1;i<=m;i++){
              if(canMove[i]==0) ct++;
           }
           if(ct==m)  judge=0;
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