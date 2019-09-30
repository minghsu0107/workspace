#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int len[101][101];
// 若求輸出答案除以100007的餘數 則每次建構時都取餘數
// ex: len[i][j]=(len[i-1][j-1]+1)%100007

int lcs(char a[], char b[]){
   int alen = strlen(a);
   int blen = strlen(b);
   for (int i = 0; i <= alen; i++) {
      len[i][0] = 0;
   }
   for (int i = 0; i <= blen; i++) {
      len[0][i] = 0;
   }
   for (int i = 1;i <= alen; i++) {
     for (int j = 1; j <= blen; j++) {
       if (a[i-1] == b[j-1]) {
          len[i][j] = len[i-1][j-1] + 1;
       }
       else {
          len[i][j] = max(len[i-1][j], len[i][j-1]);
       }
     }
   }
   return len[alen][blen];
}

int main(){
   char a[101];
   char b[101];
   cin >> a >> b;
   cout << lcs(a,b);
}