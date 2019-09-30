#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

void bin(int n){
  if (n<=1){
    cout<<n;
  }
  else{
    bin(n/2);
    cout<<(n%2==1 ? '1' : '0');
  }
}
int main() {
  int n;
  while (cin >> n) {
    bin(n) ;
  }
}
