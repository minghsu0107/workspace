#include <stdio.h>
#include <string.h>
int main(){
    char pathname[40];
    char file[40][40];
    int file_count = 0;
    char* start = pathname;
    char* slash;
    int copy_length = 0;

    int i;
    scanf("%s", pathname);
    while (start != NULL){
        start = strchr(start, '/');
        slash = strchr(start+1, '/');
        if(slash != NULL){
            start++;
            copy_length = (int)(slash - start);
            strncpy(file[file_count],start, copy_length);
            file[file_count][copy_length] = '\0';
            file_count++;
            start = (char*) (slash);
        }
        else{
           start++;
           strcpy(file[file_count],start);
           file_count++; 
           start = NULL;
        }
    }
    for(i = 0; i < file_count; i++){
        printf("%s\n", file[i]);
    }
    return 0;
}

//  /user/local/bin/vim