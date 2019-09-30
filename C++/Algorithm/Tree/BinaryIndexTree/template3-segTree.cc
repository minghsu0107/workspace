#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
typedef long long ll;
const ll maxn=1e6+10;
int n,q;
ll a[maxn],tree[maxn*4],lazy[maxn*4];
void pushup(int rt){tree[rt]=tree[rt<<1]+tree[rt<<1|1];}
void pushdown(int l,int r,int rt){
    if(lazy[rt]){
        tree[rt<<1]+=l*lazy[rt];
        tree[rt<<1|1]+=r*lazy[rt];
        lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        lazy[rt]=0;
    }
}
void build(int l,int r,int rt){
    lazy[rt]=0;
    if(l==r){
        tree[rt]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int L,int R,ll val,int l,int r,int rt){
    if(l>=L&&r<=R){
        tree[rt]+=val*(r-l+1);
        lazy[rt]+=val;
        return;
    }
    int mid=l+r>>1;
    pushdown(mid-l+1,r-mid,rt);
    if(mid>=L) update(L,R,val,lson);
    if(mid<R) update(L,R,val,rson);
    pushup(rt);
}
ll ask(int L,int R,int l,int r,int rt){
    ll res=0;
    if(l>=L&&r<=R) return tree[rt];
    int mid=l+r>>1;
    pushdown(mid-l+1,r-mid,rt);
    if(mid>=L) res+=ask(L,R,lson);
    if(mid<R) res+=ask(L,R,rson);
    return res;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,n,1);
    while(q--){
        int id,x,y,z;
        scanf("%d",&id);
        if(id==1){
            scanf("%d%d%d",&x,&y,&z);
            update(x,y,z,1,n,1);
        }
        else{
            scanf("%d%d",&x,&y);
            printf("%lld\n",ask(x,y,1,n,1));
        }
    }
    return 0;
}