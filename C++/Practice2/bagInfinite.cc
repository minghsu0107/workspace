#include <iostream>
#include <vector>
#include <map>
using namespace std;

int filmlen[105];
int sat[505];
int arr[1005];

int bag(int m,int n){
  arr[0]=0;
  for(int k=0;k<=m;k++){
    bool found=false;
    int max=0;
    for (int i=0;i<n;i++){
      if(k>=filmlen[i]){
        int v=sat[i]+arr[k-filmlen[i]];
        if(!found||v>max) max=v;
        found=true;
      }
    }
    arr[k]=max;
  }
  return arr[m];
}
int bag2(int m,int n){
  if (m==0) return 0;
  if (arr[m]==0){
    bool found = false;
    int max=0;
    for (int i=0;i<n;i++){
      if(m>=filmlen[i]){
        int v = sat[i]+bag2(m-filmlen[i],n);
        if (!found||v>max) max = v;//view left first;if left=true,then not viewing right
        found = true;
      }
    }
    //int max=*max_element(mat,mat+105);
    arr[m]=max;
  }
  return arr[m];
}


int bag3(int m,int n){
  if (m==0) return 0;
  int max=0;
  if (arr[m]==0){
    for (int i=0;i<n;i++){
      if (m<filmlen[i]) continue;
      if (max==0){
        max=sat[i]+bag3(m-filmlen[i],n);
      }
    }
    for (int j=0;j<n;j++){
      if (m<filmlen[j]) continue;
      int k=sat[j]+bag3(m-filmlen[j],n);
      if (k>max){
        max=k;
      }
    }
    arr[m]=max;
  }
  return arr[m];
}

int f(int m,vector<int>&V,vector<int>&M, map<int,int>&arr){
  if (arr.count(m) == 0) {
    int max=0;
    for(int i=0;i<M.size();i++){
      if(V[i]<=m){
        int x=f(m-V[i],V,M,arr)+M[i];
        if(x>max){
          max=x;
        }
      }
    }
    arr[m]=max;
  }
  return arr[m];
}
int f2(int m,vector<int>&V,vector<int>&M, map<int,int>&arr){
  arr[0]=0;
  for(int k=0;k<=m;k++){
    int max=0;
    for (int i=0;i<M.size();i++){
      if(V[i]<=k){
        int x=arr[k-V[i]]+M[i];
        if(x>max){
          max=x;
        }
      }
    }
    arr[k]=max;
  }
  return arr[m];
}

int main(){
  int N;
  int M;
  cin>>N>>M;
  
  //vector<int> vecv;
  //vector<int> vecm;
  
  for (int i=0;i<N;i++){
    cin>>filmlen[i]>>sat[i];
    int v,m;
    //cin>>v>>m;
    //filmlen[i]=v;
    //sat[i]=m;
    
    //vecv.push_back(v);
    //vecm.push_back(m);
  }
  
  //std::map<int,int> cnts;
  cout<<bag(M,N)<<endl;
  
  //for (int i=0;i<=M;i++){
  //  arr[i]=0;
  //}
  //cout<<bag2(M,N)<<endl;
  
  //cout<<f(M,vecv,vecm,cnts)<<endl;
  
  //cout<<f2(M,vecv,vecm,cnts)<<endl;
}