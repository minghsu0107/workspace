#include <iostream>
#include <algorithm>
using namespace std;

long long int arr[35][35];

void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << arr[i][j] << ",";
    }
    cout<<endl;
  }
}
long long int grid(int x,int y){
  //for (int i=0;i<=x;i++){
  //  for (int j=0;j<=y;j++){
  //    arr[i][j]=0;
  //  }
  //}
  for (int i=0;i<=x;i++){
    arr[i][0]=1;
  }
  //pr(x,y);
  for (int j=0;j<=y;j++){
    arr[0][j]=1;
  }
  //pr(x,y);
  for (int i=1;i<=x;i++){
    for (int j=1;j<=y;j++){
      arr[i][j]=arr[i-1][j]+arr[i][j-1];
    }
  }
  return arr[x][y];
}
long long int grid2(int i,int j){
  if (i==0) return 1;
  if (j==0) return 1;
  if (arr[i][j]==0){
    arr[i][j]=grid(i-1,j)+grid(i,j-1);
  }
  return arr[i][j];
}

int main(){
  int x;
  int y;
  cin>>x;
  cin>>y;
  cout<<grid(x,y)<<endl;
  //for (int i=0;i<=x;i++){
  //  for (int j=0;j<=y;j++){
  //    arr[i][j]=0;
  //  }
  //}
  //cout<<grid2(x,y)<<endl;
  //pr(x,y);
}