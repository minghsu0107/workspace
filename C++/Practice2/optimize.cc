#include <iostream>
using namespace std;

int dp[101];

//優化 f(n)=f(n-1)+f(n-2)+2[f(n-3)+f(n-4)+...+f(1)+f(0)]

void op1(int n){
   dp[0]=1;
   dp[1]=1;
   dp[2]=2;
   for(int i=3;i<=n;i++){
       int sum=0;
       for(int j=0;j<=i-3;j++){
           sum+=dp[j];
       }
       dp[i]=dp[i-1]+dp[i-2]+2*sum;
   }
   cout<<dp[n]<<endl;
}

void op2(int n){  // 使用變數記錄前綴和
   dp[0]=1;
   dp[1]=1;
   dp[2]=2;
   int tmp=dp[0];
   for(int i=3;i<=n;i++){
       dp[i]=dp[i-1]+dp[i-2]+2*tmp;
       tmp+=dp[i-2];
   }
   cout<<dp[n]<<endl; 
}

// f(n)=f(n-1)+f(n-2)+2[f(n-3)+f(n-4)+...+f(1)+f(0)]
// f(n-1)=f(n-2)+f(n-3)+2[f(n-4)+f(n-5)+...+f(1)+f(0)]
// f(n-1)+f(n-3)=f(n-2)+2[f(n-3)+f(n-4)+f(n-5)+...+f(1)+f(0)]
// 得到 2[f(n-3)+f(n-4)+...+f(1)+f(0)]=f(n-1)-f(n-2)+f(n-3)
// 轉移式變成 f(n)=2f(n-1)+f(n-3)，O(1)轉移

void op3(int n){
   dp[0]=1;
   dp[1]=1;
   dp[2]=2;
   for(int i=3;i<=n;i++){
       dp[i]=2*dp[i-1]+dp[i-3];
   }
   cout<<dp[n]<<endl;  
}

int main(){
   int n;
   cin>>n;
   //op1(n);
   op2(n);
   //op3(n);
}