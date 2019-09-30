#include <stdio.h>
#include <stdlib.h>

int mat[16][16];
int pat[16][16];
int main(){
    int n, k, m, d;
    int msum=0;
    int psum=0;
    scanf("%d%d%d%d",&n,&k,&m,&d);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            scanf("%d",&pat[i][j]);
            psum+=pat[i][j];
        }
    }
    int lastr=-1;
    int lastc=-1;
    for(int i=0;i<n-k+1;i++){
        for(int j=0;j<n-k+1;j++){
            int count=0;
            
            for(int x=i;x<i+k;x++){
               for(int y=j;y<j+k;y++){
                   msum+=mat[x][y];
                   if(mat[x][y]!=pat[x-i][y-j]) count++; 
               } 
            }
            if(abs(msum-psum)<=d && count<=m){
                if(i>lastr){
                    lastr=i;
                    lastc=j;
                }
                else if(i==lastr){
                    if(j>lastc) lastc=j;
                }
            }
            msum=0;
            //printf("count: %d\n",count);
            //printf("%d %d\n",msum, psum);
            //printf("%d %d\n",lastr, lastc);
        }
    }
    printf("%d %d",lastr, lastc);
    return 0;
}