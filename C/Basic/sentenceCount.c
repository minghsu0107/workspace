#include <stdio.h>
#include <ctype.h>
int main(){
  char c;
  int found=0, flag=0, count=0, cnt=0;
  while(scanf("%c",&c)!=EOF){
    if(cnt){
        if(c==' '){
           count++;
           flag=0;  
        }
        cnt=0;
    }
    if(flag&&c!=' '&&c!='\n') flag=0;
    if(!found&&c=='.') {
       found=1;
       continue;
    }
    if(found){
       if(c=='\n') {
          count++;
       }
       else if(c==' '){
           cnt=1;
           flag=1;
       }
       if(c!='.') found=0;
    }
  }
  if(found) count++;
  else if(flag) count++;
  printf("%d",count);
  return 0; 
}