#include <stdio.h>
#include <limits.h> 
//找最小值時，可用<limits.h>中的INT_MAX作為最小值的初值；反之找最大值時，可用INT_MIN作為最大值的初值。
//#define INT_MAX 16385
//#define INT_MIN -1
void place(int bucket[1024],int N,int ball[16384],int M,int method,int result[16384]){
    switch(method){
    case 0: // first fit
        for(int i=0;i<M;i++){
            int found=0;
            for(int j=0;j<N&&!found;j++){
                if(bucket[j]>=ball[i]){
                    result[i]=j;
                    bucket[j]-=ball[i];
                    found=1;
                }
            }
            if(!found) result[i]==-1;
        }
        break;
    case 1: // best fit
        for(int i=0;i<M;i++){
            int min=INT_MAX;
            int index=-1;
            for(int j=0;j<N;j++){
                if(bucket[j]>=ball[i]&&bucket[j]<min){ // when same remaining capacity, choose smaller index.
                    index=j;
                    min=bucket[j];
                }
            }
            if(index!=-1)
                bucket[index]-=ball[i];
            result[i]=index;
        }
        break;
    case 2: // worst fit
        for(int i=0;i<M;i++){
            int max=INT_MIN;
            int index=-1;
            for(int j=0;j<N;j++){
                if(bucket[j]>=ball[i]&&bucket[j]>=max){ // when same remaining capacity, choose larger index.
                    index=j;
                    max=bucket[j];
                }
            }
            if(index!=-1)
                bucket[index]-=ball[i];
            result[i]=index;
        }
        break;
    default: // never here!
        break;
    }
}
int main(){
    int N,M,method;
    scanf("%d%d%d",&N,&M,&method);
    int buckets[N];
    for(int i=0;i<N;i++)
        scanf("%d",&buckets[i]);
    int balls[M];
    for(int i=0;i<M;i++)
        scanf("%d",&balls[i]);
    int result[M];
    place(buckets,N,balls,M,method,result);
    for(int i=0;i<M;i++)
        printf("%d%s",result[i],i==M-1?"":" ");
    return 0;
}