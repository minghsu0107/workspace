#include <iostream>
#include <algorithm>
using namespace std;

void pr(int arr[], int len) {
  for (int i=0; i<len; i++) {
    cout << arr[i] << ",";
  }
  cout << endl;
}
int bsearch(int arr[], int len, int x){
  int start=0;
  int end=len;
  while(end>start){
    int t = start + (end - start) / 2;
    if (x==arr[t]){
      return t;
    }
    else if(x>arr[t]){
      start=t+1;
    }
    else{
      end=t;
    }
  }
  return -1;
}
int bSearch2(int arr[], int x,int start, int end){
  if (end>start){
    int t= start+((end-start)/2);
    if (x == arr[t]) return t;
    else if (x > arr[t]){
      return bSearch2(arr, x, t + 1, end);
    }
    else{
      return bSearch2(arr, x, start, t);
    }
  }
  return -1;
}
int main() {
  int len;
  cin >> len;

  int arr[len];
  for (int i=0; i<len; i++) {
    cin >> arr[i];
  }

  //pr(arr, len);

  sort(arr, arr+len);

  //pr(arr, len);
  int n;

  while(cin>> n){
    cout<<bSearch2(arr,n,0,len)<<endl;
  }
}