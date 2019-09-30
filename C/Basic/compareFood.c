#include <stdio.h>
#include <string.h>
char food[100][65];
int len[100];
char ingredient[100][10][65];
int n, m;
int find(char str[]){
  for (int i = 0; i < n; i++){
      if(strcmp(str, food[i]) == 0){
          return i;
      }
  }
}
void prSort(char* result[], int count){
   int i, j;
   char *ptr[10];
   char *temp;
   for(i = 0;i < count; i++){
        ptr[i] = result[i];
    }
   for(i = 0; i < count - 1; i++){
        for(j = 0; j < count - 1 - i ; j++){
             if(strcmp(ptr[j], ptr[j+1]) > 0){
                 temp = ptr[j];
                 ptr[j] = ptr[j+1];
                 ptr[j+1] = temp;
             }
        }
    }
    int f = 0;
    for(int i = 0;i < count; i++){
	   if (f) printf(" ");
       printf("%s",ptr[i]);
	   f = 1;
    }
}
void cmp(char str1[], char str2[]){
    int idx1 = find(str1);
    int idx2 = find(str2);
    char* result[10];
    int count = 0;
    for (int i = 0; i < len[idx1]; i++){
      for (int j = 0; j < len[idx2]; j++){
          if(strcmp(ingredient[idx1][i], ingredient[idx2][j]) == 0){
             result[count++] = ingredient[idx1][i];
          }
      }
    }
	if(count == 0) printf("nothing");
	else prSort(result, count);
}
int main(){
  scanf("%d",&n);
  for(int k = 0; k < n; k++){
      scanf("%s",food[k]);
      scanf("%d",&len[k]);
      for(int j = 0;j < len[k]; j++){
         scanf("%s",ingredient[k][j]);
      }
  }
  scanf("%d",&m);
  while(m--){
	   char str1[65], str2[65];
     scanf("%s%s",str1,str2);
     cmp(str1,str2);
	   puts("");
  }
  return 0; 
}
