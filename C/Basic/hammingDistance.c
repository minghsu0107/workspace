#include <stdio.h>
unsigned int arr[32];
int n, m, p;
int distance(unsigned int t1, unsigned int t2) {
	unsigned int tmp = t1 ^ t2;
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += (1 & (tmp >> i));
		if (count > 1) break;
	}
	if (count <= 1) return 1;
	return 0;
}
void judge(unsigned int text) {
    for (int i = 0; i < n; i++) {
    	if (distance(arr[i], text)) printf("%d\n", arr[i]);
    }
}
int main() {
   scanf("%d%d%d", &n, &m, &p);
   for (int i = 0; i < m; i++) {
   	  unsigned long long num;
   	  scanf("%llu", &num);
   	  for (int j = 8*i + 7; j >= 8*i; j--) {
          arr[j] = num % 256;
          num /= 256;
   	  }
   }
   for (int i = 0; i < p; i++) {
   	  unsigned int text;
   	  scanf("%u", &text);
      judge(text);
   }
   return 0;
}