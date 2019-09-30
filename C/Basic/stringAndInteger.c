#include <stdio.h>
#include <string.h>
char str[100005];
unsigned long long arr[12505] = {};
int main(int argc, char const *argv[])
{
    int task;
    scanf("%d", &task);
    if (!task) {
        scanf("%s", str);
        int len = 0, slen = strlen(str), i = 0;
        while (i <= slen) {
            for (int x = 56; x >= 0 && i <= slen; x -= 8) {
                arr[len] |= (unsigned long long)str[i++] << x;
            } 
            len++; 
            // when i == slen, the program will still go through here (len++) first
            // and then stop the while loop
        }
        for (int i = 0 ; i < len; i++) {
            printf("%llu\n", arr[i]);
        }
    }
    else {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%llu", &arr[i]);
        }
        int end = 0;
        for (int i = 0; i < N && !end; i++) {
            int cnt = 0;
            while (cnt < 8) {
                  char ans = (char)(arr[i] >> (64 - 8));
                  if (ans == '\0') {
                    end = 1;
                    break;
                  }
                  printf("%c", ans);
                  arr[i] <<= 8;
                  cnt++;
            }
        }
    }
    return 0;
}