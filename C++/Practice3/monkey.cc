#include <iostream>
#include <string>
using namespace std;

void mon(string &a,string &b){
  int i,j;
  int alen=a.length();
  int blen=b.length();
  bool mem=true;
  int pos=-1;
  for (i=0;i<alen&&mem==true;i++){
    for (j=pos+1;j<blen;j++){
      if(a[i]==b[j]){
         pos=j;
         break;
      } 
      else if (j==blen-1){
          mem=false;
          cout<<"NO";
      }
    }
  }  
  if(mem) cout<<"YES";
} 

int main(){
  string a,b;
  cin>>a>>b;
  mon(a,b);
}