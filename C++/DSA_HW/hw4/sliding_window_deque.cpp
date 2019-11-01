#include <cstdio>
#include <cstring>

const int M =1e6+6;
int n,k;
int a[M],qmax[M],qmin[M],pmax[M],pmin[M],mx[M],mi[M];

void get_max(){
    int tail=0,head=1;
    for(int i=1;i<k;i++){
        while(head<=tail&&qmax[tail]<=a[i])
            --tail;
        qmax[++tail]=a[i];
        pmax[tail]=i;
    }
    for(int i=k;i<=n;i++){
        while(head<=tail&&qmax[tail]<=a[i])
            --tail;
        qmax[++tail]=a[i];
        pmax[tail]=i;
        while(pmax[head]<i-k+1)
            ++head;
        mx[i-k+1]=qmax[head];
    }
    for(int i=1;i<=n-k+1;i++){
        i==1?printf("%d",mx[i]):printf(" %d",mx[i]);
    }
    printf("\n");
}

void get_min(){  
    int tail=0,head=1;
    for(int i=1;i<k;i++){  //先開始將前k-1個元素插入優先隊列
        while(head<=tail&&qmin[tail]>=a[i]) //求最小值，維護一個單調遞增的隊列，最小值在隊首
            --tail;   
        qmin[++tail]=a[i];  //將隊尾不符合條件的元素刪除後，將該元素插入隊尾
        pmin[tail]=i;  //隊尾元素的位置
    }
    for(int i=k;i<=n;i++){ //然後將從第k個元素及以後插入優先隊列，此時就要註意過期的隊首元素的刪除
        while(head<=tail&&qmin[tail]>=a[i])   //依然是插入時的維護
            --tail;
        qmin[++tail]=a[i];
        pmin[tail]=i;
        while(pmin[head]<i-k+1)   //如果隊首元素的下標過小，則將該過期的隊首元素刪除
            ++head;
        mi[i-k+1]=qmin[head];   //記錄下新隊首元素
    }
    for(int i=1;i<=n-k+1;i++){
        i==1?printf("%d",mi[i]):printf(" %d",mi[i]);
    }
    printf("\n");
}

int main(){
    while(scanf("%d %d",&n,&k)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        // print the min and max number in each sliding window
        get_min();
        get_max();
    }
    return 0;
}

