#include<stdio.h>
#include<stdlib.h> // for qsort
#include<string.h>
#define MAXLENGTH 16
#define MAXCOMPONENT 64
typedef struct{
    char name[MAXLENGTH];
    int numComponent;
    int componentPartList[MAXCOMPONENT];
    int price;
}ComponentPart;
int calculate(ComponentPart list[],int index){
    if(list[index].price==0)
        for(int i=0;i<list[index].numComponent;i++)
            list[index].price+=calculate(list,list[index].componentPartList[i]);
    return list[index].price;
}
int cmp(const void *a,const void *b){
    return strcmp((*(ComponentPart**)a)->name,(*(ComponentPart**)b)->name);
}
void findPrice(int N,ComponentPart list[]){
    ComponentPart*toSort[N]; // avoid moving structures
    for(int i=0;i<N;i++){
        if(list[i].price==0)
            calculate(list,i);
        toSort[i]=&list[i];
    }
    qsort(toSort,N,sizeof(ComponentPart*),cmp);
    for(int i=0;i<N;i++)
        printf("%s %d\n",toSort[i]->name,toSort[i]->price);
}
int main(){
    int N;
    scanf("%d",&N);
    ComponentPart list[N];
    for(int i=0;i<N;i++){
        scanf("%s%d",list[i].name,&list[i].numComponent);
        if(list[i].numComponent){
            for(int j=0;j<list[i].numComponent;j++)
                scanf("%d",&list[i].componentPartList[j]);
            list[i].price=0;
        }
        else
            scanf("%d",&list[i].price);
    }
    findPrice(N,list);
    return 0;
}