#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000000
int visited[1000000];
void loops(int N, int *A, int *B[], int ans[4]) {
    int Mnum, mnum, Mlen, mlen, flag = 1;
    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;
        visited[i] = 1;
        int max, min, len = 1;
        int *tmp = &A[i];
        max = *tmp, min = *tmp;
        tmp = B[tmp-A];
        while (*tmp != A[i]) {
            visited[tmp-A] = 1;
            if (*tmp > max) max = *tmp;
            else if (*tmp < min) min = *tmp;
            tmp = B[tmp-A];
            len++;
        }
        if (flag) {
            Mlen = len, mlen = len;
            Mnum = max, mnum = min;
            flag = 0;
        } else {
            if (len > Mlen) {
                Mlen = len;
                Mnum = max;
            }
            if (len == Mlen) {
                if (max > Mnum) Mnum = max;
            }
            if (len < mlen) {
                mlen = len;
                mnum = min;
            }
            if (len == mlen) {
                if (min < mnum) mnum = min;
            }
        }
    }
    ans[0] = Mlen, ans[1] = mlen, ans[2] = Mnum, ans[3] = mnum;
}
int main(){
    int N;
    int *A = (int *)malloc(sizeof(int) * MAXN);
    int **B = (int **)malloc(sizeof(int *) * MAXN);
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", A + i);
    for(int i = 0, ptr; i < N; i++){
        scanf("%d", &ptr);
        B[i] = A + ptr;
    }
    int ans[4];
    loops(N, A, B, ans);
    for(int i = 0; i < 4; i++)
        printf("%d\n", ans[i]);
    return 0;
}
