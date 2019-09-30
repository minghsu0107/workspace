#include<stdio.h>
int n,W;
int w[21],v[21];
int used[21];
int max=-1;
void knapsack0(int a,int wt,int money){
    if(money>max) max=money;
    for(int i=a;i<n;i++){
        if(!used[i]){
            used[i]=1;
            if(wt-w[i]>=0){
                knapsack0(i+1,wt-w[i],money+v[i]);
            }
            used[i]=0;
        }
    }
}
void knapsack(int d,int wt,int money){
    if(money>max) max=money;
    for(int i=d;i<n;i++){
        if(wt-w[i]>=0){
            knapsack(i+1,wt-w[i],money+v[i]);
        }
    }
}
//無序
void knapsack2(int a,int wt,int money){
    if(wt > W) return;
    if(money>max) max=money;
    if (a == n) return;
    knapsack2(a+1,wt,money);
    knapsack2(a+1,wt + w[a],money+v[a]);
}
int main()
{
    scanf("%d%d",&n,&W);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&w[i],&v[i]);
    }
    knapsack0(0,W,0);
    //knapsack0(0,W,0);
    //knapsack2(0,0,0);
    printf("%d\n",max);
}
