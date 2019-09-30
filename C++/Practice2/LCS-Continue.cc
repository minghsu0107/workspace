#include <iostream>
#include <string.h>
using namespace std;

int len[101][101];

void lcs(char a[], char b[]) {
   int alen = strlen(a);
   int blen = strlen(b);
   for (int i = 0; i <= alen; i++) {
      len[i][0] = 0;
   }
   for (int i = 0; i <= blen; i++) {
      len[0][i] = 0;
   }
   for (int i = 1; i <= alen; i++) {
     for (int j = 1;j <= blen; j++) {
       if (a[i-1] == b[j-1]) {
          len[i][j] = len[i-1][j-1] + 1;
       }
       else {
          len[i][j] = 0;
       }
     }
   }
   int M=0;
   int index=0;
   for(int i = 0; i <= alen; i++) {
       for(int j = 0;j <= blen; j++) {
          if(len[i][j] > M){
              M = len[i][j];
              index = i;
          }
          
       }
   }
   cout << M << endl;
   while(M) {
       cout << a[index-M];
       M--;
   }
   cout << endl;
}

int main() {
   char a[101];
   char b[101];
   cin >> a >> b;
   lcs(a,b);
}