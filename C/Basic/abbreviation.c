#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(){
 char str[128];
 char result[128];
 char* invalid[4] = {"of","and","the","at"};
 int count = 0;
 while (scanf("%s",str)!=EOF){
    if(str[strlen(str)-1] == '.'){
             if((strncmp(str, invalid[0], 2) == 0 && strlen(str) == 3) ||
                (strncmp(str, invalid[1], 3) == 0 && strlen(str) == 4) ||
                (strncmp(str, invalid[2], 3) == 0 && strlen(str) == 4) ||
                (strncmp(str, invalid[3], 2) == 0 && strlen(str) == 3)){
                 result[count] = '\0';
                 printf("%s\n",result);
                 count = 0;
            }
            else{
                 result[count++] = toupper(str[0]); 
                 result[count] = '\0';
                 printf("%s\n",result);
                 count = 0;
            }
    }else if(strcmp(str, invalid[0]) != 0 
             && strcmp(str, invalid[1]) != 0 
             && strcmp(str, invalid[2]) != 0 
             && strcmp(str, invalid[3]) != 0){
        result[count++] = toupper(str[0]); 
 
    }
 }
 return 0; 
}
