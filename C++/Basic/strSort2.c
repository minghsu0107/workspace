#include <stdio.h>
#include <string.h>
int main(){
    char str[12][40];
    int i, j;
    char *ptr[12];
    char *temp;
    for(i = 0;i < 12; i++){
        scanf("%s", str[i]); // no "&"
        ptr[i] = str[i];
    }
    for(i = 0; i < 12 - 1; i++){
        for(j = 0; j < 12 - 1 - i ; j++){
             if(strcmp(ptr[j], ptr[j+1]) > 0){
                 temp = ptr[j];
                 ptr[j] = ptr[j+1];
                 ptr[j+1] = temp;
             }
        }
    }
    
    for(i = 0; i < 12; i++){
        printf("%s\n", ptr[i]);
    }
    return 0;
}