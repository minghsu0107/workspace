#include <stdio.h>
int main(void){
  char a[5],b[4];
  int A,B;
  for (int i=0;i<5;i++){
    scanf("%c",&a[i]);
  }
  
  for (int i=0;i<4;i++){
    scanf("%c",&b[i]);
  }
  A=0;
  for (int i=0;i<4;i++){
    if(a[i]-'0'==b[i]-'0') A++;
  }
  B=0;
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
       if(a[i]-'0'==b[j]-'0'&& i!=j) B++;
    }
  }
  printf("%dA%dB",A,B);
  return 0;
}