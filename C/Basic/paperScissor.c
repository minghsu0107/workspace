#include <stdio.h>
int main(){
    int x,a,b,c,y,d,e,f,N;
    scanf("%d%d%d%d%d%d%d%d%d",&x,&a,&b,&c,&y,&d,&e,&f,&N);
    for(int i=0;i<N;i++){
        int winner=-1;
        int pairs=1;
        int next=1;
        while(next){
           int xs=x%3,ys=y%3;
           if(xs+1==ys || (xs==2&&ys==0)){
                winner=1;
                printf("%d %d\n",winner,pairs);
                next=0;
            }
            else if(ys+1==xs || (ys==2&&xs==0)){
                winner=0;
                printf("%d %d\n",winner,pairs);
                next=0;
            }
            else{
                pairs++;
                next=1;
            } 
            x=(a*x+b)%c;
            y=(d*y+e)%f;
        }
       
    }
    return 0;
}