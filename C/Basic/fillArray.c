#include <stdio.h>
void fill_array(int *ptr[], int n){
   for(int i=0;i<=n-1;i++){
      *ptr[i]=i;
   }
   int prev = 0;
   for(int* k=ptr[0]+1;k<ptr[n-1];k++){
      if(*k!=0) prev=*k;
      else{
         int* r=k+1;
         while(*r==0) r++; 
         *k = prev+ *r;
      }
   }
   return;
}
int main() {
    int arr[100] = {};
    int *ptr[100];
    int n = 6, m = 0; // n is the length of ptr[]; m is the biggest index of arr[]
    int A[100] = {0, 5, 6, 9, 3, 12}; // index of elements in arr that are pointed
    for (int i = 0; i < n; i++) {
        ptr[i] = &arr[A[i]];
        if (A[i] > m)    m = A[i];
    }
    fill_array(ptr, n);
    for (int i = 0; i <= m; i++)
        printf("%d%c", arr[i], " \n"[i==m]);
    return 0;
}