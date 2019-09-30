#include <stdio.h>
#include <string.h>
 
int N, cost[20], len[20], min=2147483647;
char str[20][51];
void dfs(int d, int c, int appear[]) {
    if (c > min) return;
    if (d == N) {
        int valid = 1;
        for (int i='a'; i<='z' && valid; i++) {
            valid &= (appear[i]==1);
        }
        if (valid && (c < min)) min = c;
        return;
    }
    dfs(d + 1, c, appear);
    int tmp[128];
    for (int i='a'; i<='z'; i++)
        tmp[i] = appear[i];
    for (int i = 0; i < len[d]; i++) {
        tmp[str[d][i]] = 1;
    }
    dfs(d + 1, c + cost[d], tmp);
    return;
}
 
int main() {
    scanf("%d", &N);
    for (int i=0; i<N; i++) {
        scanf("%s%d", str[i], &cost[i]);
        len[i] = strlen(str[i]);
    }
    int appear[128] = {};
    dfs(0, 0, appear);
    printf("%d", min);
    return 0;
}