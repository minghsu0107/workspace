#include <iostream>
#include <algorithm>
using namespace std;

int len[101][101];


int lcs(int a[],int b[],int alen, int blen){
   for(int i=0;i<=alen;i++){
      len[i][0]=0;
   }
   for(int i=0;i<=blen;i++){
      len[0][i]=0;
   }
   for(int i=1;i<=alen;i++){
     for(int j=1;j<=blen;j++){
       if(a[i-1]==b[j-1]){
          len[i][j]=len[i-1][j-1]+1;
       }
       else{
          len[i][j]=max(len[i-1][j],len[i][j-1]);
       }
     }
   }
   return len[alen][blen];
}

int findUniq(int arr[],int n){
    int k=0;
    for(int i=1;i<n;i++){
        if(arr[i]!=arr[k]){
            arr[++k]=arr[i];
        }
    } 
    return k+1;
}
int main(){
    int a[101];
    int b[101];
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b,b+N);
    int len=findUniq(b,N);
    cout<<lcs(a,b,N,len);
}