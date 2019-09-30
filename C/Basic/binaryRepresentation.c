#include <stdio.h>
// 不需要把所有數字都存起來或是展開成 32 個 0 / 1
int main(){
    int N;
    char S[35];
 
    scanf("%s %d", S, &N);
 
    int val = 0, cnt = 0, n;
    while(N--){
        scanf("%d", &n);
        for(int i = 31; i >= 0; i--){
            cnt ++;
            val = (val << 1) | ((n >> i) & 1);
            if (cnt == 5){
                printf("%c", S[val]);
                val = cnt = 0;
            }
        }
    }
 
    printf("\n");
    return 0;
}