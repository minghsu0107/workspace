#include <stdio.h> 
int main()
{
    int N, M, P;
    scanf("%d%d%d", &N, &M, &P);
    unsigned long long int valid[8];
    for (int i = 0; i < M; i++) 
        scanf("%llu", &valid[i]);
    unsigned int text[300];
    for (int i = 0; i < P; i++)
        scanf("%u", &text[i]);
 
 
    for (int i = 0; i < P; i++) {
        int time = 0, k = 0, find = 0;
        while (time < N && k < M && !find) {
            for (int j = 56; j >= 0 && time < N && !find; j -= 8) {
                unsigned long long int tmp = (valid[k] << (56 - j));
                unsigned int com = 0;
                tmp >>= 56;
                com |= (text[i] ^ tmp);
                if (com == 0 || com == 1 || com == 2 || com == 4 || com == 8 ||
                    com == 16 || com == 32 || com == 64 || com == 128) {
                    printf("%lld\n", tmp);
                    find = 1;
                }
                time++;
            }
            k++;
        }
    }
    return 0;
}