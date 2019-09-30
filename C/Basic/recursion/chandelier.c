#include <stdio.h>
long long arr[16384];
int check (long long w[], int left, int right){
   for(int i = left; i <= right; i++){
       long long sumleft = 0;
       for(int j = i - left; j > 0; j--){
           sumleft += w[i-j] * j;
       }
       long long sumright = 0;
       for(int k = 1; k <= right - i; k++){
           sumright += w[i+k] * k;
       }
       if(sumleft == sumright) return i;
   } 
   return -1;
}
void dfs(int left, int right) {
	if (right - left + 1 < 3) return;
	int idx = check(arr, left, right);
	if (idx == -1) return;
	dfs(left, idx - 1);
	printf("%d\n", idx);
	dfs(idx+1, right);
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
	}
	dfs(0, n - 1);
	return 0;
}