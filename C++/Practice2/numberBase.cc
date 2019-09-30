#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

string base(int n){
  if (n==0) return "0";

  string s = "";

  char cs[100];
  int len = 0;

  while(n>0){
    //1:s = to_string(n%2)+s;

    //2:s.insert(0,to_string(n%2));

    char c=(n%2==1) ? '1':'0';
    //3:s=c+s;

    //4:s.insert(0,1,c);
    cs[len] = c;
    len ++;
    n=n/2;
  }
  for (int i=0; i<len/2; i++) {
    char tmp = cs[i];
    cs[i] = cs[len-i-1];
    cs[len-i-1] = tmp;
  }
  cs[len] = '\0';
  return string(cs);
  //return string(cs, len);
  //return s;
}

int main(){
  int n;

  while(cin>> n){
    cout<<base(n)<<endl;
  }

}