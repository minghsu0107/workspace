#include <stdio.h>
#include <string.h>
int s[20] = {}, cost[20], N, min = 2147483647;
void dfs(int d, int c, int appear) {
    if (c > min) return;
	int valid = 1;
    valid &= (__builtin_popcount(appear) == 26);
    if (valid && (c < min)) min = c;
	for (int i = d; i < N; i++) {
        int tmp = appear;
	    tmp |= s[i];
        dfs(i + 1, c + cost[i], tmp);
	}
	return;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char str[51];
        scanf("%s%d", str, &cost[i]);
        int len = strlen(str);
        for (int j = 0; j < len; j++) {
            s[i] |= 1 << (str[j] - 'a');
        }
    }
    int appear = 0;
    dfs(0, 0, appear);
    printf("%d", min);
    return 0;
}