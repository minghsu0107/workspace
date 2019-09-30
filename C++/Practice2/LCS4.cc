#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int len[101][101];
int arr[101][101];

int lcs(char a[],char b[],int alen,int blen){
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
          arr[i][j]=0;
       }
       else{
           if(len[i-1][j]>len[i][j-1]){
             len[i][j]=len[i-1][j];
             arr[i][j]=1;
         }else{
             len[i][j]=len[i][j-1];
             arr[i][j]=2;
         }
       }
     }
   }
   return len[alen][blen];
}

void prlcs(char a[],int i,int j){
    if(i==0 || j==0) return;
    if(arr[i][j]==0){
        prlcs(a,i-1,j-1);
        cout<<a[i-1];
    }
    else if(arr[i][j]==1){
        prlcs(a,i-1,j);
    }
    else if(arr[i][j]==2){
        prlcs(a,i,j-1);
    }
}
int main(){
   char a[101];
   char b[101];
   cin>>a>>b;
   int alen=strlen(a);
   int blen=strlen(b);
   cout<<lcs(a,b,alen,blen);
   cout<<endl;
   prlcs(a,alen,blen);
}