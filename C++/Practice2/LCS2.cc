#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int len[101][101];

int lcs(char a[],char b[],int alen,int blen){
   if(alen==0 || blen==0) return 0;
   if(len[alen][blen]==-1){
     if(a[alen-1]==b[blen-1]){
       len[alen][blen]=lcs(a,b,alen-1,blen-1)+1;
     }
     else{
       len[alen][blen]=max(lcs(a,b,alen-1,blen),lcs(a,b,alen,blen-1));
     }
   }
   return len[alen][blen];
}

int main(){
   char a[101];
   char b[101];
   cin>>a>>b;
   int alen=strlen(a);
   int blen=strlen(b);
   for(int i=0;i<=alen;i++){
     for(int j=0;j<=blen;j++){
       len[i][j]=-1;
     }
   }
   cout<<lcs(a,b,alen,blen);
}