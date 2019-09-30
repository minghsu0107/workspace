#include<iostream>
#include<cstring>
#include<sstream>
using namespace std;

int find(char line[]){
   int sum=0;
   for(int i=0;line[i]!='\0';i++){
       if(line[i]>='0' and line[i]<='9'){
           int num=line[i]-'0';
           sum*=10;
           sum+=num;
       }
   }
   return sum;
}
int main(){
  int total=0;
  char line[100];
  while(cin>>line){
     total+=find(line);
  }
  cout<<total;
}