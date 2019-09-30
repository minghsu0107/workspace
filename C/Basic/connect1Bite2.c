#include <stdio.h>
 
int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    int max = 0, len = 0;
    while (n != 0) {
      if (n & 1) ++len;
      else len = 0;
      if (len > max) max = len;
      n >>= 1;
    }
    printf("%d\n", max);
  }
}
