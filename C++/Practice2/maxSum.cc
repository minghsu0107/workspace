#include<iostream>
#include<algorithm>
using namespace std;

int dp[100];

int maxSum(int arr[],int n){
    dp[0]=max(0,arr[0]);
    for (int i = 1;i<n;i++) {
       dp[i]=max(0,dp[i-1]+arr[i]);
    }
    int M=0;
    for(int i=0;i<n;i++){
        M=max(M,dp[i]);
    }
    return M;
}

int main(){
    int n;
    cin>>n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<maxSum(arr,n);
}