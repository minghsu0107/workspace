#include <iostream>  
using namespace std;  
 
void py(int n){
  for (int i=1;i<=n;i++){ 
    for (int k=1;k<=n-i;k++){
      cout<<"_";
    }
    for (int j=1;j<=2*i-1;j++){  
      cout<<i;  
    }  
    cout<<endl;  
  }  
}
int main(){  
  int n;  
  cin>>n;  
  py(n);
}  