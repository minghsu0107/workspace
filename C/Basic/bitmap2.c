#include <stdio.h>
int bit[32*1024];
int main() {
	int c, r, cnt = 0;
	unsigned int x;
	char a[2], b[2];
	scanf("%d%d",&c, &r);
	scanf("%s%s",a,b);
	while (scanf("%d", &x) == 1) {
        for (int j = 31; j >= 0; j--) {
			bit[32*cnt + j] = x&1;
			x >>= 1;
		}
		cnt++;
	}
	for (int i = 0; i < r; i++) {
	    for (int j = 0; j < c; j++) {
	        if (bit[c*i + j]) printf("%c", a[0]);
	        else printf("%c", b[0]);
	    }
	    puts("");
	}
	return 0;
}
