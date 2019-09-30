#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll maxn=1e6+10;
int n,q;
ll a[maxn],tree[maxn*4],lazy[maxn*4];
void pushup(int rt){tree[rt]=tree[rt<<1]+tree[rt<<1|1];}
void pushdown(int l,int r,int rt){
    if(lazy[rt]){
        tree[rt<<1]+=lazy[rt]*l;
        tree[rt<<1|1]+=lazy[rt]*r;
        lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        lazy[rt]=0;
    }
}
void build(int l,int r,int rt){
    if(l==r){
        tree[rt]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    pushup(rt);
}
void update(int L,int R,int val,int l,int r,int rt){
    if(l>=L&&r<=R){
        tree[rt]+=val*(r-l+1);
        lazy[rt]+=val;
        return ;
    }
    int mid=l+r>>1;
    pushdown(mid-l+1,r-mid,rt);
    if(mid>=L) update(L,R,val,l,mid,rt<<1);
    if(mid<R) update(L,R,val,mid+1,r,rt<<1|1);
    pushup(rt);
}
ll ask(int pos,int l,int r,int rt){
    if(l==pos&&l==r)
        return tree[rt];
    int mid=l+r>>1;
    pushdown(mid-l+1,r-mid,rt);
    ll ans;
    if(pos<=mid) return ask(pos,l,mid,rt<<1);
    else return ask(pos,mid+1,r,rt<<1|1);
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
            scanf("%d",&x);
            printf("%lld\n",ask(x,1,n,1));
        }
    }
    return 0;
}