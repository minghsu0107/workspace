#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void prarr(int arr[],int N){
  for(int i=0;i<N;i++){
    if (i>=1) cout<<",";
    cout<<arr[i];
  }
}

void prisort(int arr[], int n){
  priority_queue<int, vector<int>, greater<int>> q(arr, arr+n);
  //for(int i=0;i<n;i++){
  //  int k=arr[i];
  //  q.push(k);
  //}
  for(int i=0;i<n;i++){
    arr[i]=q.top();
    q.pop();
  }
}

int main(){
  const int N=1000000;
  int arr[N],arr2[N];
  srand(time(NULL));
  for(int i=0; i<N; i++){
    arr[i]= arr2[i]= rand();
  }
  clock_t t=clock(); //time now
  prisort(arr,N);
  float dif1 =clock()-t;
  prarr(arr,5);

  t=clock();
  sort(arr2,arr2 +N);
  float dif2=clock()-t;
  //cout << endl << CLOCKS_PER_SEC << endl;
  cout<<endl<<dif1/CLOCKS_PER_SEC<<" "<<dif2/CLOCKS_PER_SEC<<endl;

  prarr(arr2,5);
  cout<<endl;


  //srand(123); // same every time
  //cout<<time(NULL)<<endl;
}