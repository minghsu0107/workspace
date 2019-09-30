#include<stdio.h>
int a,n=0,num[105];
int check(int ini,int bot){
    if(ini==bot) return 1;
    int k=bot-ini+1;
    for(int i=0;i<k/2;i++)
    {
        if(num[ini+i]!=num[bot-i]) return 0;
    }
    return 1;
}
int main()
{
    while(scanf("%d",&a)!=EOF)
    {
        num[n]=a;
        n++;
    }
    int flag=0;
    for(int i=0;i<n-1&&!flag;i++){
        for(int head=i;head>=0&&!flag;head--){
            for(int len=0;len<n&&!flag;len++){
                int t1=check(head,head+len);
                int t2=check(head+len+1,head+n-i-1);
                if(t1==1&&t2==1){
                    for(int q=head;q<head+n-i-1;q++)
                        printf("%d ",num[q]);
                    printf("%d",num[head+n-i-1]);
                    flag=1;
                }
            }
        }
    }
    return 0;
}