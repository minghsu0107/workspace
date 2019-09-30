#include <stdio.h>
int gcd(int a,int num){ return ((num==0)? a:gcd(num,a%num));}
int main(){
    int a,num;
    scanf("%d",&a);
    while(scanf("%d",&num)!=EOF) a=a*num/gcd(a,num);
    printf("%d",a);
    return 0;
}
