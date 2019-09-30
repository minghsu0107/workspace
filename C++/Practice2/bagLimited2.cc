#include <iostream>
#include <algorithm>
using namespace std;

int filmlen[105];
int sat[105];
int num[105];
int arr[105][1005];

void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << arr[i][j] << ",";
    }
    cout<<endl;
  }
}

int f(int n,int m){
  for(int i=0;i<=n;i++){
      for(int j=0;j<=m;j++){
          arr[i][j]=0;
      }
  }
  for (int i=0;i<n;i++){
    for (int j=1;j<=m;j++){
      for(int k=0;k<=num[i];k++){
          if (j>=k * filmlen[i]){
             int cur = arr[i][j- k * filmlen[i]]+ k * sat[i]; 
             arr[i+1][j]=arr[i+1][j]>cur? arr[i+1][j]:cur;
          }
      }
    }
  }
  return arr[n][m];
}

int main(){
  int N;
  int M;
  cin>>N>>M;

  for (int i=0;i<N;i++){
    cin>>sat[i]>>filmlen[i]>>num[i];
  }
  cout<<f(N,M)<<endl;
  pr(N,M);
}