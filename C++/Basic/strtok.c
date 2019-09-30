#include <stdio.h>
#include <string.h>
int main(){
    char delimeters[] = "/";
    char pathname[40];
    char file[40][40];
    int file_count = 0;
    char *start = pathname;

    int i;
    scanf("%s", pathname);
    start = strtok(start, delimeters);
    while (start != NULL){
        strcpy(file[file_count],start);
        file_count++;
        start = strtok(NULL, delimeters);
    }
    for(i = 0; i < file_count; i++){
        printf("%s\n", file[i]);
    }
    printf("After strok pathname becomes %s\n", pathname);
    // remain the first token and the string before it
    // every token ends with '\0'
    return 0;
}

//  /user/local/bin/vim