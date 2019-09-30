#include <stdio.h>

#define MAX_SIZE_PTRARRAY 512
#define MAX_NUM_PTR 512
#define MAX_NUM_INTVAR 512
//#define NULL ((void *)0)

// count.h
#ifndef COUNT_H_INCLUDED
#define COUNT_H_INCLUDED
void count(int **p[]);
#endif
void swap(int* a,int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int main(){
  int **ptrArray[MAX_SIZE_PTRARRAY] = {};
  int  *intPtr[MAX_NUM_PTR];
  int   intVar[MAX_NUM_INTVAR];
 
  intVar[0] = 7;
  intVar[1] = 6;
  intVar[2] = 2;
  intVar[3] = 9;
  ptrArray[0] = &intPtr[0];
  ptrArray[1] = &intPtr[1];
  ptrArray[2] = &intPtr[2];
  ptrArray[3] = &intPtr[3];
  ptrArray[4] = NULL;
  intPtr[0] = &intVar[0];
  intPtr[1] = &intVar[1];
  intPtr[2] = &intVar[2];
  intPtr[3] = &intVar[3];
 
  count(ptrArray);
 
  return 0;
}
void count(int **p[]){
    int num[MAX_NUM_INTVAR];
    int cnt[MAX_NUM_INTVAR]={};
    int index[MAX_NUM_INTVAR];
    int* address[MAX_NUM_INTVAR];
    int len=0;
    for(int i=0;p[i]!=NULL;i++){
        int found=0;
        for(int j=0;j<len&&!found;j++){
           if(*p[i]==address[j]){
               cnt[j]++;
               found=1;
           }
        }
        if(!found){
           num[len]=**p[i];
           cnt[len]++;
           address[len]=*p[i]; 
           index[len]=len;
           len++;
        }
    }
    int min;
    for (int i = 0; i < len - 1; ++i)
    {
        min = i;
        for (int j = i + 1; j < len; ++j){
            if (cnt[index[j]] < cnt[index[min]] ||
                (cnt[index[j]]==cnt[index[min]] && num[index[j]]<num[index[min]])){
                min = j;
            }
        }
        if (min != i){
            //printf("%d %d %d\n",i,num[index[min]],num[index[i]]);
            swap(&index[min],&index[i]);
            //printf("%d %d %d\n",i,num[index[min]],num[index[i]]);
        }
    }
    for(int i=0;i<len;i++){
        printf("%d %d\n",num[index[i]],cnt[index[i]]);
    }
    return;
}