#include<iostream>
#include<queue>
using namespace std;

int dp[100];

int maxSum(int arr[],int n,int k){
    priority_queue<int> q;
    dp[0]=max(0,arr[0]);
    q.push(dp[0]);
    
    for (int i = 1;i<n;i++) {
       dp[i]=max(0,dp[i-1]+arr[i]);
       q.push(dp[i]);
    }
    int num;
    for(int i=0;i<k;i++){
       num=q.top();
       q.pop();
    }
    return num;
}
int main(){
    int n,k;
    cin>>n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cin>>k;
    cout<<maxSum(arr,n,k);
}