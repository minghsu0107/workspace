#include <iostream>  
using namespace std; 

int maxSum(int arr[],int n){  
    int sum=0;  
    int M=0;  
    for (int i = 0;i<n;i++) {  
       sum=max(0,sum+arr[i]);  
       M=max(M,sum);  
    }  
    return M;  
}  
int maxSum2(int arr[],int n){
    int max = 0;
    for( int i = 0; i < n; i++ ){ 
        for( int j = i; j < n; j++ ){  
            int sum = 0;  
            for( int k = i; k <= j; k++ ){  
                sum += arr[k];  
                if( sum>max )  max = sum;
            }
        }  
    }
    return max;
}
int maxSum3(int arr[],int n){
    int max = 0;
    int sum = 0;
    for( int i = 0; i < n; i++ ){ 
        sum=0;
        for( int j = i; j < n; j++ ){  
             sum+=arr[j];
             if(sum>max) max=sum;
        }  
    }
    return max;
}
int main()  {  
    int n;
    cin>>n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<maxSum(arr,n)<<endl;
    cout<<maxSum2(arr,n)<<endl;
    cout<<maxSum3(arr,n)<<endl;
        
}  
