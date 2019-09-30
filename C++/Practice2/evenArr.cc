#include <iostream>
#include <vector>
using namespace std;

int collectEven(const vector<int>& arr, vector<int>& out){//可以更改out內容
   int sum=0;
   for (int i=0; i<arr.size(); i++) {
     if (arr[i]%2==0){
       out.push_back(arr[i]);
       sum+=1;
     }
   }
   return sum;
}
int even2(int arr[], int arrlen, int out[], int outlen) {
   int count=0;
   for(int i=0;i<arrlen;i++){
       if (arr[i]%2==0){
         out[outlen]=arr[i];
         outlen+=1;
         count+=1;
       }
   }
   return count;
}
int main(){
  vector<int> mat1;
  vector<int> mat2;
  int arr1[1000];
  int arr2[1000];
  int arr1len=0;
  int arr2len=0;
  int n;
  while(cin>>n){
    mat1.push_back(n);
    arr1[arr1len]=n;
    arr1len+=1;
  }

  int len = collectEven(mat1,mat2);
  cout << "vec:" << len << ":";
  int k= mat2.size();
  for (int i=0;i<k;i++){
    if (i > 0) cout << ",";
    cout<<mat2[i];
  }
  cout<<endl;

  int len2=even2(arr1,arr1len,arr2,arr2len);
  arr2len+=len2;
  cout << "arr:" << arr2len << ":";
  for (int i=0;i<arr2len;i++){
    if (i > 0) cout << ",";
    cout<<arr2[i];
  }
  cout<<endl;
}