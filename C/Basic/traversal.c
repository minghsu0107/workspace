#include <stdio.h>
#include <assert.h>
 
#define MAXNM 262144
int ret[MAXNM][2];
void push(int ret[][2], int *cnt, int x, int y) {
    ret[*cnt][0] = x, ret[*cnt][1] = y;
    (*cnt)++;
}
int main() {
    int n, m, sx, sy;
    while (scanf("%d %d %d %d", &n, &m, &sx, &sy) == 4) {
        assert(m%2 == 0);
 
        int cnt = 0;
        push(ret, &cnt, 0, 0);
        for (int i = 0; i < m; i++) {
            if (i%2 == 0) {
                for (int j = 1; j < n; j++)
                    push(ret, &cnt, j, i);
            } else {
                for (int j = n-1; j >= 1; j--)
                    push(ret, &cnt, j, i);
            }
        }
        for (int i = m-1; i > 0; i--)
            push(ret, &cnt, 0, i);
 
        int stIdx = 0;
        for (int i = 0; i < cnt; i++) {
            if (ret[i][0] == sx && ret[i][1] == sy)
                stIdx = i, i = cnt;
        }
 
        for (int i = 0; i <= cnt; i++) {
            printf("%d %d\n", ret[stIdx][0], ret[stIdx][1]);
            if (++stIdx >= cnt) stIdx = 0;
        }
    }
    return 0;
}