#include <stdio.h>
//#define NULL ((void *)0)
void shuffle(int *deck[]);
void print(int *deck[]);
int main()
{
  int card[10000];
  int *deck[10000];
  int index = 0;
 
  while (scanf("%d", &(card[index])) != EOF) {
    deck[index] = &(card[index]);
    index++;
  }
  deck[index] = NULL;
  shuffle(deck);
  print(deck); 
  return 0;
}
void shuffle(int *deck[]){
    int count=0;
    for(int i=0;deck[i]!=NULL;i++){
        count++;
    }
    if(count==0){
       return;
    }
    int n = count%2==0? count/2 : (count/2)+1;
    int* atmp[n];
    int* btmp[count-n];
    int alen=0,blen=0;
    for(int i=0;i<n;i++){
        atmp[alen++]=deck[i];
    }
    for(int i=n;i<count;i++){
        btmp[blen++]=deck[i];
    }
    int index=0,p=0,q=0,flag=0;
    while(p<alen || q<blen){
      if(!flag){
        deck[index++]=atmp[p++];
        flag=1;
      }else{
        deck[index++]=btmp[q++];
        flag=0;
      }
    }
}
void print(int *deck[]){
    int f=0;
    for(int i=0;deck[i]!=NULL;i++){
        if(f) printf(" ");
        printf("%d",*deck[i]);
        f=1;
    }
    return;
}