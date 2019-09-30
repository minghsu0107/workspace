#include <stdio.h>
int combination(int n,int m){
    if(m<n-m) m=n-m;
    int ans=1;
    for(int i=m+1;i<=n;i++) ans*=i;
    for(int i=1;i<=n-m;i++) ans/=i;
    return ans;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int sum=0;
    for(int i=0;i<=m;i++){
        sum+=combination(n,i);
    }
    printf("%d\n",sum);
}