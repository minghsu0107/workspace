#include <stdio.h>
int N, K, result[100];
unsigned long long club[100];
int find(int n, int collect, unsigned long long common)
{
    if(collect == K) return 1;
    for(int i = n; i < N && N - i >= K - collect; i++){
        if((club[i] & common) == (unsigned long long)0) {
            result[collect] = i;
            if(find(i + 1, collect + 1, common | club[i])) return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d", &N, &K);
    int i, j, n, mem;
    for(i = 0; i < N; i++){
        scanf("%d", &n);
        for(j = 0; j < n; j++){
            scanf("%d", &mem);
            club[i] |= (unsigned long long)1 << mem;
        }
    }
    if(find(0, 0, 0))
        for(i = 0; i < K; i++)
            printf("%d\n", result[i]);
    return 0;
}