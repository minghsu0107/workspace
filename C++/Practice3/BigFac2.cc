#include <iostream>
using namespace std;

int times(char digits[], int len, int n) {
  int tmp=0;
  for(int i=0;i<len;i++){
    tmp+=digits[i]*n;
    digits[i]=tmp%10;
    tmp/=10;
  }
  while(tmp>0){
    digits[len++] = tmp%10;
    tmp/=10;
  }
  return len;
}

int fac(char digits[], int n){
  digits[0] = 1;
  int len = 1;
  for(int i=2;i<=n;i++){
    len = times(digits, len, i);
  }
  return len;
}

int main(){
  int n;
  cin>>n;
  char digits[1000];
  int len = fac(digits, n);
  //for(int i=len-1;i>=0;i--){
  //  cout <<char('0' + digits[i]); //把digits[i]由字元碼變字母
  //}
  for (int i=0; i<len; i++) {
    digits[i] = '0' + digits[i];
  }
  for (int i=0; i<len/2; i++) {
    char tmp = digits[i];
    digits[i] = digits[len-i-1];
    digits[len-i-1] = tmp;
  }
  digits[len] = '\0';

  cout<<digits<< endl;
}