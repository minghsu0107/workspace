#include <stdio.h>
unsigned long long member[101];
int result[101];
int n, k;
int find = 0;
void com(int d, int len, unsigned long long common) {
    if (n - d < k - len) return;
	if (!find && len == k) {
		find = 1;
		return;
    }
	for (int i = d; i < n && !find; i++) {
        if (!find && (common & member[i]) == (unsigned long long)0) {
		    result[len] = i;
		    com(i+1, len+1, common | member[i]);
	    }
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		int m;
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
        	int num;
        	scanf("%d", &num);
        	unsigned long long tmp = 1;
        	member[i] |= (tmp << num);
        }
	}
	com(0, 0, 0);
	if (find) {
		for (int i = 0; i < k; i++) {
		    printf("%d\n", result[i]);
	    }
	}
	return 0;
}