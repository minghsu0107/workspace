#include <stdio.h>
int main(){
    int k,num,q,flag,count;
    scanf("%d",&k);
    q=flag=count=0;
    while(scanf("%d",&num)!=EOF){
        q=q*10+num;
        if(flag!=0 || q/k!=0){
           printf("%d\n",q/k);
           flag=1;   
           count++;
        }
        q%=k;
    }
    if(!count) printf("%d",0);
    return 0;
}