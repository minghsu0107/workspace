#include <stdio.h>
#include <string.h>
int len[20], cost[20], N, min = 2147483647;
char str[20][51];
void dfs(int d, int c, int appear) {
    if (c > min) return;
	int valid = 1;
    valid &= (__builtin_popcount(appear) == 26);
    if (valid && (c < min)) min = c;
	for (int i = d; i < N; i++) {
        int tmp = appear;
        for (int j = 0; j < len[i]; j++) {
            tmp |= 1 << (str[i][j] - 'a');
        }
        dfs(i + 1, c + cost[i], tmp);
	}
	return;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s%d", str[i], &cost[i]);
        len[i] = strlen(str[i]);
    }
    int appear = 0;
    dfs(0, 0, appear);
    printf("%d", min);
    return 0;
}