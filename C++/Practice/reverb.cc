#include <iostream>
#include <string>
using namespace std;

string rev(int n){
  string s="";
  while(n>0){
      s+=to_string(n%10);
      n/=10;
  }
  return s;
}
int rev2(int n){
    int m=0;
    while(n>0){
        m*=10;
        m+=n%10;
        n/=10;
    }
    return m;
}
int main(){
    int N;
    cin>>N;
    cout<<rev2(N)<<endl;
}