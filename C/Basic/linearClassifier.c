#include <stdio.h>
int n,m;
int w[16][16];
int p[16][16];
int test[16][16];
int h(int p[16][16],int t){
   int sum=0;
   for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            sum+=p[i][j]*w[i][j];
        }
    } 
    if(sum>=t) return 1;
    else return 0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            w[i][j]=1;
        }
    }
    int T=2*m*m;
    int result;
    for(int k=0;k<n;k++){
        
       scanf("%d",&result);
       for(int i=0;i<m;i++){
           for(int j=0;j<m;j++){
               scanf("%d",&p[i][j]);
           }
       }
       if(h(p,T)==result) continue;
       if(result==1){
           for(int i=0;i<m;i++){
               for(int j=0;j<m;j++){
                   if(p[i][j]==1) w[i][j]*=2;
               }
           }
       }else if(result==0){
           for(int i=0;i<m;i++){
               for(int j=0;j<m;j++){
                   if(p[i][j]==1){
                       w[i][j]/=2;
                       if(w[i][j]<1) w[i][j]=1;
                   }
               }
           }
       }
    }
    int q;
    scanf("%d",&q);
    for(int k=0;k<q;k++){
        
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                scanf("%d",&test[i][j]);
            }
        }
        printf("%d\n",h(test,T));
    }
    return 0;
}