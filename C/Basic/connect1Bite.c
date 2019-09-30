#include <stdio.h>
int main(){
  int n;
  while(scanf("%d",&n)!=EOF){
    int max = 0, len = 0, last = -1;
    while(n != 0){
      if(n & 1 == 1){
        if(last == 1) len++;
        else len = 1;
        max = max > len ? max : len;
      }
      last = n & 1;
      n >>= 1;
    }
    printf("%d\n", max);
  }
  return 0;
}
