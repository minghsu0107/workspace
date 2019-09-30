#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

std::map<int,bool> cnts;

void umap(const vector<int>&arr){
   for(int x: arr){
    if(!cnts[x]){
      cnts[x]=true;
      cout<<x<<" ";
    }
   }
   cout<<endl;
}
void usort(int arr[],int len){
   int mat[len];
   int length=0;
   sort(arr,arr+len);
   for(int i=1;i<len;i++){
     if (arr[i]!=arr[i-1]){
       mat[length]=arr[i];
       length++;
     }
   }
   for(int i=0;i<length;i++){
     cout<<mat[i]<<" ";
   }
}

int main(){
  int x;
  int Len=0;
  vector<int> vec;
  int arr[1000];
  while(cin>>x){
    vec.push_back(x);
    arr[Len]=x;
    Len++;
  }
  umap(vec);
  usort(arr,Len);
}