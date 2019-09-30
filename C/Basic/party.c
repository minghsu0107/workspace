#include<stdio.h>
#define MAX_STUDENT 32768
#define MAX_FRIEND 256
 
int graph[MAX_STUDENT][MAX_FRIEND]={ {0} };
int count[MAX_STUDENT]={0};
int invited[MAX_STUDENT]={0};
 
int main(){
    // input
    int N,E;
    scanf("%d%d",&N,&E);
    // record friendship and friend number of each student   
    while(E-->0){
        int vi,vj;
        scanf("%d%d",&vi,&vj);
        graph[vi][count[vi]++]=vj;
        graph[vj][count[vj]++]=vi;
    }
    // make all friends of each host invited
    int host;
    while(scanf("%d",&host)==1){
        invited[host]=1;
        for(int i=0;i<count[host];i++)
            invited[graph[host][i]]=1;
    }
    // output
    for(int i=0;i<N;i++)
        if(invited[i]==0)
            printf("%d\n",i);
}
