#include <stdio.h>
int main() {
    int n;
    int lastend=-1,lastSumLen=0;
    int thisfront,thisend,thissiz;
    int max=0;   
    while(scanf("%d",&n)!=EOF){
        thisend=n%10;
        thissiz=0;
        while(n>0){
            thisfront=n%10;
            n/=10;
            thissiz++;
        }
        if(lastend==thisfront){
            lastSumLen+=thissiz;
        }   
        else{
            lastSumLen=thissiz;
        }
        if(lastSumLen>max) max=lastSumLen;
        lastend=thisend;
 
    }
    printf("%d",max);
    return 0;
}