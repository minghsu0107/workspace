#include <iostream>
#include <algorithm>
using namespace std;

int dp[100];

//lis(arr,n)為從arr[0]到arr[n]中取出數字 且以arr[n]做結尾的最大遞增子序列長度
void lis(int arr[],int n){  
    for(int i=0;i<n;i++){  
        dp[i]=1;  
    }  
    for(int i=0;i<n;i++){  
        for(int j=0;j<i;j++){  
            if(arr[j]<arr[i]){  
               dp[i]=max(dp[i],dp[j]+1);   
            }  
        }  
    }  
    int longest=0;  
    for(int i=0;i<n;i++){  
        longest=max(longest,dp[i]);  
    }  
    cout<<longest;  
}  

void lis2(int arr[],int n){
    int longest=0;
    for(int i=0;i<n;i++){
        dp[i]=1;
    }
    for(int i=0;i<n;i++){
        int l=0;
        for(int j=0;j<i;j++){
            if(dp[j]>l&&arr[j]<arr[i]){
               l=dp[j];
            }
            dp[i]=l+1;
            longest=dp[i]>longest? dp[i]:longest;
        }
    }
    cout<<longest;
}

int main(){
    int arr[100];
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    
    lis2(arr,N);
}