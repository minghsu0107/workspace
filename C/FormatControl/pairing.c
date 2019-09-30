#include <stdio.h>
#include <stdlib.h>
#define swap(x,y) {int t; t=x; x=y; y=t; }
typedef struct {
  int num, idx; 
} Ptr;
typedef struct {
  int sum, first, second; 
} Data;

int cmp(const void *a, const void* b) {
   return ((Ptr*)a)->num - ((Ptr*)b)->num;
}
int cmp_sum(const void *a, const void* b) {
   Data *ptr1 = (Data*)a;
   Data *ptr2 = (Data*)b;
#if defined(INC)
  return ptr1->sum != ptr2->sum ? ptr1->sum - ptr2->sum : ptr1->first - ptr2->first;
#elif defined(DEC)
  return ptr1->sum != ptr2->sum ? ptr2->sum - ptr1->sum : ptr2->first - ptr1->first;
#endif
}
void pairPrint(int numbers[], int n) {
  Ptr *p = (Ptr*)malloc(sizeof(Ptr) * n);
  for (int i = 0; i < n; i++) {
      p[i].num = numbers[i];
      p[i].idx = i;
  }
  qsort(p, n, sizeof(Ptr), cmp); 
  Data *arr = (Data*)malloc(sizeof(Data) * n/2);
  int len = 0;
  for (int i = 0; i < n / 2; i++) {
    arr[len].sum = p[i].num + p[n-1-i].num; 
    arr[len].first = p[i].idx;
    arr[len].second = p[n-1-i].idx;
#if defined(INC)
    if (arr[len].first > arr[len].second)
       swap(arr[len].first, arr[len].second);
#elif defined(DEC)
    if (arr[len].first < arr[len].second)
       swap(arr[len].first, arr[len].second);
#endif
    len++;
  }
  qsort(arr, len, sizeof(Data), cmp_sum);
  for (int i = 0; i < len; i++) {
      printf("%d = numbers[%d] + numbers[%d]\n", 
             arr[i].sum, arr[i].first, arr[i].second);  
  }
  return;
}
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int *A = (int *) malloc(sizeof(int)*n);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        pairPrint(A, n);
        free(A);
    }
    return 0;
}
// gcc -DINC pairing.c
// gcc -DDEC pairing.c