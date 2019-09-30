#include <iostream>
#include <algorithm>
using namespace std;

void pr(int arr[], int len) {
  for (int i=0; i<len; i++) {
    cout << arr[i] << ",";
  }
  cout << endl;
}
long long int stair(long long int arr[], int n){
  if (n == 1){
    return 1;
  }
  else if (n == 2){
    return 2;
  }
  else{
    if (arr[n] > 0){
      return arr[n];
    }
    arr[n] = stair(arr,n-1) + stair(arr, n-2);
    return arr[n] ;
  }
}
long long int stair2( int n){
  long long int arr[95];
  arr[0]=1;
  arr[1]=1;
  for (int i=2;i<=n;i++){
    arr[i]=arr[i-1]+arr[i-2];
  }
  return arr[n];

}
int main() {
  int n;
  cin >> n;
  //long long int arr[95]={};

  //pr(arr,n+1);
  //cout << stair(arr,n)<<" ";
  //long long int k=stair(arr,n);
  //cout << stair(arr,k%n);
  cout << stair2(n)<<" ";
  long long int k=stair2(n);
  cout << stair2(k%n);
  //pr(arr,n+1);
}