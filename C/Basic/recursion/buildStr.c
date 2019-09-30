#include <stdio.h>
#include <stdlib.h>
int K, L, N, n;
char test[1024];
int compare(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}
void set(char lc, int possible[]) {
    for (int i = 1; i <= K; i++) {
        possible[i - 1] = ((lc - 'a') + i) % 26;
    }
    qsort(possible, K, sizeof(int), compare);
}
void build(int d, char lc) {
    if (n <= 0) return;
    if (d == L && n > 0) {
        printf("%s\n", test);
        n--;
        return;
    }
    int possible[26];
    set(lc, possible);
    for (int i = 0; i < K && n > 0; i++) {
         test[d] = possible[i] + 'a';
         build(d + 1, test[d]);
    }
    return;
}
int main(int argc, char const *argv[])
{
    char lc;
    scanf("%c%d%d%d", &lc, &K, &L, &N);
    test[0] = lc;
    n = N;
    build(1, lc);
    return 0;
}