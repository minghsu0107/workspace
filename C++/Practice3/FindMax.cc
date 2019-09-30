#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int find(string line){
   int sum=0;
   istringstream iss(line);  
   int num;
   while (iss >> num) { 
      sum+=num;
   }
   return sum;
}

int main(){
  int n=0;
  string line;
  int max=0;
  int pos=0;
  while (getline(cin, line)) {
    ++n;
    if (find(line)>max){
        max=find(line);
        pos=n;
    }
  }
  cout<<pos<<" "<<max<<endl;
}