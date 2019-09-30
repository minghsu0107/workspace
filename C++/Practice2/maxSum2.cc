#include<iostream>
#include<algorithm>
using namespace std;

int dp[100];

int maxSum(int arr[],int n){
    if(n==1){
        if(arr[n-1]<0) return 0;
        return arr[n-1];
    }
    if(dp[n-1]==-1){
       dp[n-1]=max(0,maxSum(arr,n-1)+arr[n-1]); 
    }
    return dp[n-1];
}

int main(){
    int n;
    cin>>n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin>>arr[i];
        dp[i]=-1;
    }
    maxSum(arr,n);
    int M=0;
    for(int i=0;i<n;i++){
        M=max(M,dp[i]);
    }
    cout<<M;
}