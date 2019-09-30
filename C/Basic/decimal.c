#include <stdio.h>
int main(){
    int n;
  int count=0;
  int k;
  int zeros=0;
  int sumodd=0;
  int sumeven=0;
  int flag=0;
  while(scanf("%d",&n)!=EOF){
    count++;
    k=n;
    if(n==0) zeros++;
    if(flag==0){
       sumodd+=n;
       flag=1;
    }
    else if(flag==1){
       sumeven+=n;
       flag=0;
    }
  }
  int p= (k%2==0)? 1:0;
  printf("%d\n%d\n%d\n",count,p,zeros);
  if((sumeven-sumodd)%11==0) printf("%d\n",1);
  else printf("%d\n",0);
  return 0;
}