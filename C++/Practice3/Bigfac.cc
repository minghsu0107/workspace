#include <iostream>
#include<vector>
using namespace std;

void times(vector<int> &digits, int n){
   int tmp=0;
   for(int i=0;i<digits.size();i++){
     tmp+=digits[i]*n;
     digits[i]=tmp%10;
     tmp/=10;
   }
   while(tmp>0){
     digits.push_back(tmp%10);
     tmp/=10;
   }
}

vector<int> fac(int n){
  vector<int>digits;
  digits.push_back(1);
  for(int i=2;i<=n;i++){
    times(digits,i);
  }
  return digits;
}

int main(){
  int n;
  cin>>n;
  vector<int> digits=fac(n);
  for(int i=digits.size()-1;i>=0;i--){
    cout<<digits[i];
  }
}