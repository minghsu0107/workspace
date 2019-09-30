#include <iostream>  
using namespace std;  
  
int c[6]={1,5,4,2,7,3};  
int val[6]={1,1,1,1,1,1};  
int arr[101];  
int print[101];
  
int find(int m){  
  arr[0]=0;  
  for(int k=0;k<=m;k++){  
    bool found=false;  
    int min=0;  
    for (int i=0;i<6;i++){  
      if(k>=c[i]){  
        int v=val[i]+arr[k-c[i]];  
        if(!found||v<min){
           min=v;
           print[k]=c[i];
           found=true;
        }   
      }  
    }  
    arr[k]=min;  
  }  
  return arr[m];  
} 
int find2(int m){  
  arr[0]=0;  
  for(int k=0;k<=m;k++){  
    bool found=false;  
    for (int i=0;i<6;i++){  
      if(k>=c[i]){  
        int v=val[i]+arr[k-c[i]];  
        if(!found||v<arr[k]){
           arr[k]=v;
           print[k]=c[i];
           found=true;
        }   
      }  
    }  
  }  
  return arr[m];  
} 
//print[m]儲存達成目標金額m的最後加入的硬幣面額
void pr(int m){
  while(m>0){
    cout<<print[m]<<" ";
    m-=print[m];
  }
  cout<<endl;
} 
int main(){  
  int N;  
  cin>>N;  
  //cout<<find(N)<<endl;
  cout<<find2(N)<<endl;
  pr(N);  
}  