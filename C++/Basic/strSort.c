#include <stdio.h>
#include <string.h>
int main(){
    char str[12][40];
    int i, j;
    char temp[40];
    
    for(i = 0;i < 12; i++){
        scanf("%s", str[i]); // no "&"
    }
    for(i = 0; i < 12 - 1; i++){
        for(j = 0; j < 12 - 1 - i ; j++){
             if(strcmp(str[j], str[j+1]) > 0){
                 strcpy(temp, str[j]);
                 strcpy(str[j], str[j+1]);
                 strcpy(str[j+1], temp);
             }
        }
    }
    
    for(i = 0; i < 12; i++){
        printf("%s\n", str[i]);
    }
    return 0;
}