#include <stdio.h>
int main(void){
    int n,m,r;
    scanf("%d%d%d",&n,&m,&r);
    int w;
    while (scanf("%d",&w)!=EOF){
        if(r==0){
            if(n>=w){
               n-=w;
            } 
            else if(m>=w){
               m-=w;

            } 
        }else if(r==1){
            if(n>=w){
               if(n<=m || m<w) n-=w;
               else m-=w;
            }
            else{
               if(m>=w) m-=w; 
            }
        }
        printf("%d ",n);
        printf("%d\n",m);
    }
    return 0;
}