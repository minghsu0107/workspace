#include<iostream>  
#include<string>  
#include<sstream>  
#include<map>  
using namespace std;  
  
  
int main(){  
  std::map<int,string> vec;  
  int nlines = 0;  
  string line;  
  while (getline(cin, line)) {  
    vec[++nlines]=line;  
  }  
  cout<<vec[3]<<endl<<vec[1]<<endl<<vec[2]<<endl;  
}  