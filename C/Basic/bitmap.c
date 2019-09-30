#include <stdio.h>
int main() {
	int c, r, count = 0;
	unsigned int x;
	char a[2], b[2];
	scanf("%d%d",&c, &r);
	scanf("%s%s",a,b);
	while (scanf("%d", &x) == 1) {
        for (int i = 31; i >= 0; i--) {
			if ((x>>i)&1) printf("%c",a[0]);
		    else printf("%c",b[0]);
			count++;
			if (count == r*c) break;
			if (count%c == 0) puts("");
		}
	}
	return 0;
}
