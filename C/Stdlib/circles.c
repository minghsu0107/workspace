#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
int arr[1000101];
int cmp (void *a, void *b) {
   return *(int*)a < *(int*)b;
}
int main() {
   int N, x, y;
   scan(N);  
   for (int i = 0; i < N; i++) {
       scan(x);
       scan(y);
       arr[i] = x*x + y*y;
   }
   qsort(arr, N, sizeof(int), cmp);
   int maxCount = 0, max = 0, count = 0, last = 0;
   for (int i = 0; i < N; i++) {
       if (last != arr[i])
         last = arr[i], count = 1;
       else count++;
       if (maxCount < count)
          maxCount = count, max = arr[i];
   }
   printf("%d\n", max);
}