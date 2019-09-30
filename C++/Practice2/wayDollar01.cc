#include <iostream>
using namespace std;

int c[]={7,3,9,6,4};
int arr[6][1001];

void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << arr[i][j] << ",";
    }
    cout<<endl;
  }
}

int find(int i,int m){
  for(int j=i;j<=5;j++){
     arr[j][0]=1;
  }
  for(int i=1;i<=m;i++){
      arr[5][i]=0;
  }
  for(int j=4;j>=i;j--){
    for (int k=1;k<=m;k++){
      if(k>=c[j]){
         arr[j][k]=arr[j+1][k]+arr[j+1][k-c[j]];
      }
      else arr[j][k]=arr[j+1][k];
    }
  }
  return arr[i][m];
}
int find2(int m){
  for(int j=0;j<=5;j++){
     arr[j][0]=1;
  }
  for(int i=1;i<=m;i++){
     arr[0][i]=0;
  }
  for(int j=0;j<5;j++){
    for (int k=1;k<=m;k++){
        if(k>=c[j]){
            arr[j+1][k]=arr[j][k]+arr[j][k-c[j]];
        }
        else arr[j+1][k]=arr[j][k];
    }
  }
  return arr[5][m];
}
int main(){
  int N;
  cin>>N;
  //cout<<find(0,N)<<endl;
  cout<<find2(N)<<endl;
  pr(5,N);
}