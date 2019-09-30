#include <iostream>
#include <vector>
using namespace std;

vector<int> children[100001];
int parents[100001];
int hs[100001];

int height(int node, vector<int> arr[], int hs[] ){
  if(arr[node].size()==0){
    hs[node]=0;
    return 0;
  }
  int max=0;
  for(int child: arr[node]){
    int h=height(child,arr,hs);
    if(h>max){
      max=h;
    }
  }
  hs[node]=max+1;
  return max+1;
}
long long int sum(int arr[],int len){
  long long int sum=0;
  for(int i=0;i<len;i++){
    sum+=arr[i];
  }
  return sum;
}
int main() {
  int n;
  cin >> n;

  fill(parents,parents+n,-1);

  for(int i=0;i<n;i++){
    int num;
    cin>>num;
    for(int j=0;j<num;j++){
      int k;
      cin>>k;
      children[i].push_back(k-1);
      parents[k-1]=i;
    }
  }
  int Root=-1;
  for(int i=0;i<n;i++){
    if(parents[i]<0){
      Root=i;
      break;
    }
  }
  cout<<Root+1<<endl;
  height(Root,children,hs);
  cout<<sum(hs,n)<<endl;
}