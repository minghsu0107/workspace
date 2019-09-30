#include <iostream>
#include <algorithm>
using namespace std;

void pr(int sortedArr[],int len){  
  int maxCount=0;  
  int maxNum=0;  
  int i=0;  
  while(i<len-1){  
      if (sortedArr[i]!=sortedArr[i+1]) {  
          i++;  
          continue;  
      }  
      int j=i;  
      int count=1;  
      while (sortedArr[j]==sortedArr[j+1]){  
          count++;  
          j++;  
      }  
      if (count>maxCount){  
          maxCount=count;  
          maxNum=sortedArr[i];  
      }  
      i=j+1;  
  }  
  cout<<maxNum<<" "<<maxCount<<endl;  
}  

void pr2(int sortedArr[],int len){
  int count=1;
  int maxCount=0;
  int maxNum=0;
  int i=0;
  while(i<len-1){
      if (sortedArr[i]!=sortedArr[i+1]) {
         if (count>maxCount){
            maxCount=count;
            maxNum=sortedArr[i];
         }
         count=1;
      }
      else{
         count++;
      }
      i++;
  }
  if (count>maxCount){
     maxCount=count;
     maxNum=sortedArr[i];
  }
  cout<<maxNum<<" "<<maxCount<<endl;
}
  
int main(){
  int N;
  cin>>N;
  int arr[N];
//for(int i=0;i<N;i++){
//  int num;
//  cin>>num;
//  arr[i]=num;
//}
  int num;
  int i=0;
  while(cin>>num){ //use crtl-d to end loop
      arr[i]=num;
      i++;
  }
  sort(arr,arr+N);
  pr2(arr,N);
}