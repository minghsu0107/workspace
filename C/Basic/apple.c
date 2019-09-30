#include <stdio.h>
int main(){
  int a,b,total,outer;
  scanf("%d%d",&a,&b);
  total=0;
  for(int i=a;i<=b;i++){
    total+=i;
  }
  int inside=0;
  int num=a-1;
  for(int i=0;i<b-a+1-2;i++){
      inside+=num;
      num++;
  }
  outer=total-inside;
  printf("%d\n%d\n",total,outer);
  return 0;
}