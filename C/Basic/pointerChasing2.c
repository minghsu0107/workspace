#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
void chasing(int **A[], int a, int *B[], int b, int C[], int c){
    // set elements to NULL
    memset(A, 0, sizeof(A[0])*a);
    memset(B, 0, sizeof(B[0])*b);
    int bound[3] = {a, b, c};
 
    char line[64], *s[5];
    while (fgets(line, 64, stdin)!=NULL){
        // fgets() 從檔案一行一行的讀取資料
        // assert 4 strings
        s[0] = strtok( line, " ");
        for (int i=1; i<5; i++)
            s[i] = strtok( NULL, " ");
        if (s[0] == NULL || s[1] == NULL || s[2] == NULL || s[3] == NULL || s[4] != NULL){
            printf("0\n");
            continue;
        }
 
        // assert char type
        if (strlen(s[0]) != 1 || strlen(s[2]) != 1 ||
            s[0][0] - 'A' < 0 || s[0][0] - 'A' > 1 ||
            s[2][0] - 'A' < 1 || s[2][0] - 'A' > 2) {
            printf("0\n");
            continue;
        }
 
        // assert int type
        int valid = 1;
        int len = strlen(s[1]);
        for (int i=0; i<len; i++){
            if (!isdigit(s[1][i])){
                valid = 0;
                break;
            }
        }
        if (!valid){
            printf("0\n");
            continue;
        }
        len = strlen(s[3]);
        for (int i=0; i<len-1; i++){
            if (!isdigit(s[3][i])){
                valid = 0;
                break;
            }
        }
        if (!valid){
            printf("0\n");
            continue;
        }
 
        // asser logic
        char from = s[0][0]-'A', to = s[2][0]-'A';
        int fromI = atoi(s[1]), toI = atoi(s[3]);
        if (from != to - 1 ||
            fromI >= bound[from] || toI >= bound[to]){
            printf("0\n");
            continue;
        }
 
        // valid instruction
        printf("1\n");
 
        if (from == 0)
            A[fromI] = &B[toI];
        else
            B[fromI] = &C[toI];
    }
    return;
}
int main() {
        int a = 5, b = 4, c = 3;
        int **A[5] = {}, *B[4] = {}, C[3] = {2, 1, 4};
        chasing(A, a, B, b, C, c);
 
        int **ansA[5] = {} ,*ansB[4] = {};
        for (int i = 0; i < a; i++)
                ansA[i] = NULL;
        for (int i = 0; i < b; i++)
                ansB[i] = NULL;
        ansA[2] = &B[1], ansA[3] = &B[0], ansB[1] = &C[1], ansB[2] = &C[0];
        /*Check A*/
        for (int i = 0; i < a; i++)
                if (A[i] != ansA[i] )
                        printf("A[%d] wrong answer!\n", i);
 
        /*Check B*/
        for (int i = 0; i < b; i++)
                if (B[i] != ansB[i] )
                        printf("B[%d] wrong answer!\n", i);
        return 0;
}
