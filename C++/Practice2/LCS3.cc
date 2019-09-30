#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int len[101][101];
int arr[101][101];
char mat[100];

//使用一個二維陣列arr 記錄每一格的結果是從哪一格而來
//往回追溯 每發現某一格 len[i][j] 是由 len[i-1][j-1] + 1 而來就印出 a[i-1] ( 也是 b[j-1] )

int lcs(char a[],char b[],int alen,int blen){
   if(alen==0 || blen==0) return 0;
   if(len[alen][blen]==-1){
     if(a[alen-1]==b[blen-1]){
       len[alen][blen]=lcs(a,b,alen-1,blen-1)+1;
       arr[alen][blen]=0;
     }
     else{
         if(lcs(a,b,alen-1,blen)>lcs(a,b,alen,blen-1)){
             len[alen][blen]=lcs(a,b,alen-1,blen);
             arr[alen][blen]=1;
         }else{
             len[alen][blen]=lcs(a,b,alen,blen-1);
             arr[alen][blen]=2;
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
void prlcs2(char a[],int p,int q){
    int l = len[p][q];           // LCS長度
    int tmp=l;
    while (tmp > 0){
        if (arr[p][q] == 0){       // 左上方
            tmp--;
            mat[tmp] = a[p-1];
            p--;
            q--;
        }
        else if (arr[p][q] == 1){   // 上方
            p--;
        }
        else if (arr[p][q] == 2){   // 左方
            q--;
        }
    }
    for (int k=0; k<l; ++k){
        cout << mat[k];
    }
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
       arr[i][j]=-1;
     }
   }
   cout<<lcs(a,b,alen,blen)<<endl;
   prlcs(a,alen,blen);
   cout<<endl;
   prlcs2(a,alen,blen);
   
}