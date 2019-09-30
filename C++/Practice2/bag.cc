#include <iostream>
#include <algorithm>
using namespace std;

int filmlen[105];
int sat[105];
int arr[105][1005];

void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << arr[i][j] << ",";
    }
    cout<<endl;
  }
}
int bag(int m,int i,int n){
  if (i==n) return 0;
  if (m==0) return 0;
  if (arr[i][m]==0){
    int b=bag(m,i+1,n);
    if(m>=filmlen[i]){
     int a=sat[i]+bag(m-filmlen[i],i+1,n);
     b=a>b? a:b;
     arr[i][m]=b;
    }
    else arr[i][m]=b;
  }
  return arr[i][m];
}
int bag2(int m,int i,int n){
  for(int j=i;j<=n;j++){
    arr[j][0]=0;
  }
  for(int k=1;k<=m;k++){
    arr[n][k]=0;
  }
  for (int j=n-1;j>=i;j--){                       // top-down由左到右(i to n) 則bottom-up由右到左(n to i)(注意邊界)
    for (int k=1;k<=m;k++){                       // top-down由m到0 則bottom-up由0到m
      int a=arr[j+1][k];
      if (k>=filmlen[j]){
        int b=sat[j]+arr[j+1][k-filmlen[j]]; 
        a=b>a? b:a;                               //這次選或不選　取大者為本次最大價值
        arr[j][k]=a;
      }
      else arr[j][k]=a;
    }
  }
  return arr[i][m];
}
int bag3(int m,int n){
  for(int j=0;j<=n;j++){
    arr[j][0]=0;
  }
  for(int k=1;k<=m;k++){
    arr[0][k]=0;
  }
  for (int j=0;j<n;j++){
    for (int k=1;k<=m;k++){
      int a=arr[j][k];
      if (k>=filmlen[j]){
        int b=sat[j]+arr[j][k-filmlen[j]]; 
        a=b>a? b:a;
        arr[j+1][k]=a;
      }
      else arr[j+1][k]=a;
    }
  }
  return arr[n][m];
}
int bag4(int m,int n){
  if (n==0) return 0;
  if (m==0) return 0;
  if (arr[n][m]==0){
    int b=bag4(m,n-1);
    if(m>=filmlen[n-1]){
     int a=sat[n-1]+bag4(m-filmlen[n-1],n-1);
     b=a>b? a:b;
     arr[n][m]=b;
    }
    else arr[n][m]=b;
  }
  return arr[n][m];
}
int main(){
  int N;
  int M;
  cin>>N>>M;

  for (int i=0;i<N;i++){
    cin>>filmlen[i]>>sat[i];
  }
  //cout<<bag2(M,0,N)<<endl;
  cout<<bag3(M,N)<<endl;
  pr(N,M);
  for (int i=0;i<=N;i++){
    for (int j=0;j<=M;j++){
      arr[i][j]=0;
    }
  }
  //cout<<bag(M,0,N)<<endl;
  cout<<bag4(M,N)<<endl;
  pr(N,M);
}