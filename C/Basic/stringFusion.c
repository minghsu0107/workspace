#include <stdio.h>
#include <string.h>
int main(){
  char str[128];
  char result[128];
  scanf("%s",result);
  while(scanf("%s",str)!=EOF){
      int i = 0;
      char* ptr = strchr(result,str[i]);
      if (ptr!=NULL){
            while(1){
                while(str[i]!='\0' && str[i] == *(ptr+i)){
                    i++;
                }
                if(*(ptr+i)=='\0'){
                    strcpy(ptr,str);
                    break;
                }
                else{
                    i = 0;
                    ptr = strchr(ptr+1,str[i]);
                    if(ptr==NULL){
                        strcat(result, str);
                        break;
                    }
                }
            }
      }
      else strcat(result, str);
  }
  printf("%s",result);
  return 0; 
}
