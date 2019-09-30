#include <iostream>
#include <algorithm>
using namespace std;

bool cover(int p[], int len, int k, int d) {
  int rightmost = p[0] + d;
  k-=1;
  for (int i = 1; i < len; i++) {
    if (p[i] > rightmost) {
      rightmost = p[i] + d;
      k--;
      if(k < 0) return false;
    }
  }
  return true;
}

int search(int p[],int len, int k, int sd, int ld) {
   if(sd < ld) {
     int d = (sd + ld) / 2;
     if(ld - sd == 1) return ld;
     else if(cover(p, len, k, d)) return search(p, len, k, sd, d);
     else {
       return search(p, len, k, d, ld);
     }
   }
}
int search2(int p[], int len, int k){
  int sd = 0; // shortest d
  int ld = p[len-1] - p[0]; // longest d
  while(sd < ld) { // [sd, ld]
     int d = (sd + ld) / 2;
     if(cover(p, len, k, d)) {
       ld = d; // 上界仍有可能為d
     }
     else {
       sd = d + 1;
     }
  }
  return ld;
}
int main() {
  int n,k;
  cin >> n >> k;
  int p[n];
  int len = 0;
  for(int i = 0; i < n; i++) {
    int pos;
    cin >> pos;
    p[len] = pos;
    len++;
  }
  sort(p, p + len);
  cout << search(p, len, k, 0, p[len-1] - p[0]) << endl;
  cout<<search2(p, len, k);
  return 0;
}