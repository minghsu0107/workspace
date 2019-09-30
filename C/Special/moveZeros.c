#include <stdio.h>
#define MAXN 100005
#define swap(x, y) {int t; t = x, x = y, y = t;}
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
int A[MAXN];
void moveZeroes(int* nums, int numsSize) {  // in-place algorithm
     int i; int feiling = 0; 
     for (i = 0; i<numsSize; i++) {
         if (nums[i] == 0) {
            continue;
         } else {
            nums[feiling] = nums[i]; 
            feiling++; 
         }
     }
     for (i = feiling; i<numsSize; i++) {
         nums[i] = 0;
     } 
}
int main() {
    int n, i;
    while (scanf("%d", &n)==1) {
        for (i = 0; i < n; i++)
            scan(A[i]);
        moveZeroes(A, n);
        for (i = 0; i < n; i++)
            printf("%d%c", A[i], " \n"[i==n-1]);
    }
    return 0;
}
