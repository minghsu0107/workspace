#include <stdio.h>
#include <string.h>

FILE *ptr[32];
int term[32] = {};
char last[32][4];
char file_name[32][32];
int main(){
    int k, i;
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
        scanf("%s", file_name[i]);
        ptr[i] = fopen(file_name[i], "rb");
    }
    scanf("%s", file_name[k]);
    ptr[k] = fopen(file_name[k], "w");
 
    for (i = 0; i < k; i++) {
        fread(last[i], 1, 3, ptr[i]);
        last[i][3] = '\0';
    }
    int idx;
    while (1) {
          idx = -1;      
          char min[5] = "zzzz";     
          for (i = 0; i < k; i++) {
                if (term[i] == 0) {
                    if (strcmp(last[i], min) < 0) {
                        strcpy(min, last[i]);
                        idx = i;
                    }
                }
          }
          if (idx == -1) break;
          fwrite(min, 1, 3, ptr[k]);
          int n = fread(last[idx], 1, 3, ptr[idx]);
          if (n < 3) {
            term[idx] = 1;
            continue;
          }
          last[idx][3] = '\0';
    }
    for (int i = 0; i <= k; i++) 
        fclose(ptr[k]);
    return 0;
}