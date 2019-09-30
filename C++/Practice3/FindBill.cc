#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int find(string line){
   string word;
   istringstream iss(line);  
   int count=0;
   while (iss >> word) { 
      count++;
      if(word=="BILL"){
          return count;
      }
   }
   return -1;
}

int main(){
  int nlines = 0;
  string line;
  int success=-1;
  while (getline(cin, line)) {
    ++nlines;
    success= find(line);
    if (success>0){
        cout<<nlines<<" "<<success<<endl;
        break;
    }
  }
  if(success<0) cout<<"NO"<<endl;
}