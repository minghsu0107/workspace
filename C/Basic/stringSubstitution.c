#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    char S[1024]; // initial string
    char ins[1007]; // instruction
    char de[2]; // delimiter
 
    char A[501];
    char B[501];
 
    scanf("%s", S);
 
    while (scanf("%s", ins) != EOF) {
        if (strlen(ins) == 1 && ins[0] == 'p'){
            printf("%s\n", S); // print the string from start to '\0'
            continue;
        }       
        strncpy(de, &ins[1], 1); // when using strncpy, the destination must be char[len]
        de[1] = '\0'; // when using strncpy, remember to add '\0' t o the destination 
        char *ptr = strtok(&ins[1], de); 
        // devide the string starting from ins[1] to '\0' into tokens by de
        // every token ends with '\0'
        for(int i = 0; i < 2 && ptr != NULL; i++) {
            if (i) strcpy(B, ptr);  // copy the string starting from *ptr to '\0' to B and returning B位址
            else strcpy(A, ptr); 
            ptr = strtok(NULL, de); // ptr starts from the last ptr + 1
        }
        if (strcmp(A, B) == 0) continue;
        //相同就傳回0，str1大於str2則傳回大於0的值，
        //小於則傳回小於0的值，比較的標準是依字典順序比對
        ptr = strstr(S, A); // finding string A in String S, if found then return first 位址, else return NULL
        if (ptr != NULL) {
            if (strlen(A) == strlen(B)){
                strncpy(ptr, B, strlen(B));
            } else{
                strcpy(ptr+strlen(B), ptr+strlen(A)); // strcpy will add '\0' for you
                strncpy(ptr, B, strlen(B)); //strncpy won't add '\0' for you
            }
        }
    }
    return 0;
}