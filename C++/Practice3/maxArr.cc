#include <iostream>
#include <string>
using namespace std;

#include <iostream>
#include <string>
using namespace std;


void out(int *p,int n){
  int max=p[0];
  int pos=0;
  for(int i=1;i<n;i++){
     if(p[i]>max){
        max=p[i];
        pos=i;
     }
  }
  cout<<(pos+1)<<" "<<max;
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
    out(arr,N);
}
