#include <iostream>
using namespace std;

int lot1(int n,int m){
    int sum=0;
    if (m==2||m==5||m==8){
        sum+=200;
    }
    if (n%2!=0){
        sum+=100;
    }
    if (n==m){
       sum+=50; 
    }
    return sum;
}

int main(){
  int N;
  int M;
  cin>>N>>M;
  cout<<lot1(N,M)<<endl;
}