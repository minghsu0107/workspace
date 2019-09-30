#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_N 32
#define MAX_FILENAME_LEN 16
#define MAX_INT 2147483647
 
int main(){
    int N, i;
    char fileNames[MAX_N][MAX_FILENAME_LEN];
    FILE *filePtr[MAX_N];
    int buffer[MAX_N];
    int flag[MAX_N] = {};
 
    scanf("%d", &N);
    for( i = 0 ; i < N ; ++i ){
        scanf("%s", fileNames[i]);
        filePtr[i] = fopen(fileNames[i], "rb");
        assert(filePtr[i] != NULL);
        fread(&buffer[i], sizeof(int), 1, filePtr[i]);
    }
 
    int minIndex;
    while (1) {
        minIndex = -1;
        int min = MAX_INT;
        for( i = 0 ; i < N ; ++i ){
            if( flag[i] == 0 ){
                if( buffer[i] <= min ){
                    min = buffer[i];
                    minIndex = i;
                }
            }
        }
        if( minIndex == -1 )
            break;
        printf("%d\n", min);
        int result = fread(&buffer[minIndex], sizeof(int), 1, filePtr[minIndex]);
        if( result == 0 )
            flag[minIndex] = 1;
    }
 
    for( i = 0 ; i < N ; ++i )
        fclose(filePtr[i]);
    return 0;
}