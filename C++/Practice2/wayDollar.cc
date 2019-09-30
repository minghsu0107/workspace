#include <iostream>
using namespace std;

int c[5]={2,5,10,20,25};
int arr[1001];

int find(int m){
  arr[0]=1;
  for(int i=1;i<=m;i++){
      arr[i]=0;
  }
  for(int i=0;i<5;i++){
    for (int k=0;k<=m;k++){
      if(k>=c[i]){
         arr[k]+=arr[k-c[i]];
      }
    }
  }
  return arr[m];
}

int main(){
  int N;
  cin>>N;
  cout<<find(N)<<endl;
  for (int i = 0; i < N; i++)
    cout<<arr[i]<<endl;
}