#include <iostream>
#include <algorithm>
using namespace std;
int sumDigits(int n){
  int sum=0;
  while(n>0){
    int p=n%10;
    sum+=p;
    n=n/10;
  }
  return sum;
}

int sumDigits2(int n){
  if (n/10==0) return n;
  return sumDigits2(n/10)+n%10;
}
int main() {
  int n;
  while (cin >> n) {
    cout << sumDigits2(n) << endl;
  }
}