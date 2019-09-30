#include <stdio.h>
#include <ctype.h>
int main(){
  char str[105];
  int i=0;
  int start=0, end=0,flag=1;
  while(scanf("%c",&str[i])!=EOF){
     if(!isspace(str[i])&&flag&&str[i]!='\n'){
         start=i,end=i;
         flag=0;
     }
     if(!isspace(str[i])&&!flag&&str[i]!='\n') end=i;
     i++;
     if(str[i]=='\n'){
         for(int j=start;j<=end;j++){
             printf("%c",str[j]);
         }
         puts("");
         start=0,end=0,i=0,flag=1;
     }
  }
  for(int j=start;j<=end;j++){
        printf("%c",str[j]);
  }
  return 0; 
}