#include <iostream>
#include <string>
using namespace std;


void output(int *p,int n){
  for (int i=n-1;i>=0;i--){
    cout<<*(p+i)<<" ";
  }
  cout<<endl;
}
int main(){
    int N;
    cin>>N;
    int arr[N];
    for(int i=0;i<N;i++){
        int num;
        cin>>num;
        arr[i]=num;
    }
    output(arr,N);
}