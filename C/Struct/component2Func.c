#include "component2Func.h"
#include<stdio.h>
#include<stdlib.h> // for qsort
#include<string.h>
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