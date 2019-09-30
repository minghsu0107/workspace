#include <iostream>
#include<algorithm>
using namespace std;

// divide-and-conquer
int maxsum(int *A,int x,int y){
    if(y-x==1) return A[x];
    int m=x+(y-x)/2;
    int maxs=max(maxsum(A,x,m),maxsum(A,m,y));
    int v,L,R;
    v=0; L=A[m-1];
    for(int i=m-1;i>=x;i--){
        L=max(L,v+=A[i]);
    }
    v=0; R=A[m];
    for(int i=m;i<y;i++){
        R=max(R,v+=A[i]);
    }
    return max(maxs,L+R);
}

int main(){
    int n;
    cin>>n;
    int arr[100];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<maxsum(arr,0,n);
}