#include <stdio.h>
int main(void){
  int n;
  while(scanf("%d",&n)!=EOF){
    int count=0;
    int max=-10000;
    int min=10000;
    int num;
    for(int i=0;i<n;i++){
        if(scanf("%d",&num)==EOF) break;
        if(num>max) max=num;
        if(num<min) min=num;
        count++;
    }
    if(count==n) printf("%d\n",max);
    else printf("%d\n",min);
  }
 
  return 0;
}