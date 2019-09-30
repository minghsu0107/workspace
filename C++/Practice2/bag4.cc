#include <iostream>
#include <algorithm>
using namespace std;

int filmlen[105];
int sat[105];
int arr[2][1005];

void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << arr[i][j] << ",";
    }
    cout<<endl;
  }
}

int bag(int m,int n){
  for(int j=0;j<=1;j++){
    arr[j][0]=0;
  }
  for(int k=1;k<=m;k++){
    arr[0][k]=0;
  }
  for (int j=0;j<n;j++){
    for (int k=1;k<=m;k++){
      int a=arr[j%2][k];
      if (k>=filmlen[j]){
        int b=sat[j]+arr[j%2][k-filmlen[j]]; 
        a=b>a? b:a;
        arr[(j+1)%2][k]=a;
      }
      else arr[(j+1)%2][k]=a;
    }
  }
  return max(arr[0][m],arr[1][m]);
}

int main(){
  int N;
  int M;
  cin>>N>>M;

  for (int i=0;i<N;i++){
    cin>>filmlen[i]>>sat[i];
  }
  cout<<bag(M,N)<<endl;
  pr(1,M);
}