#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll maxn = 1e6 + 10;
int n,q;
ll tree[maxn*4], a[maxn];
void pushup(int rt) {
    tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}
void build(int l, int r, int rt) {
    if(l == r){
        tree[rt] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
    pushup(rt);
}
void update(int pos, ll val, int l, int r, int rt) {
    if(l == r) {
        tree[rt] += val;
        return;
    }
    int mid = (l+r)>>1;
    if(pos <= mid) update(pos, val, l, mid, rt<<1);
    else update(pos, val, mid+1, r, rt<<1|1);
    pushup(rt);
}
ll ask(int L,int R,int l,int r,int rt) {
    ll res = 0;
    if(l >= L && r <= R) return tree[rt];
    pushup(rt);
    int mid = (l+r)>>1;
    if(L <= mid) res += ask(L,R,l,mid,rt<<1);
    if(R > mid) res += ask(L,R,mid+1,r,rt<<1|1);
    return res;
}
int main(){
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build(1, n, 1);
    while(q--) {
        int id, x, y;
        scanf("%d%d%d", &id, &x, &y);
        if(id == 1) update(x, y, 1, n, 1);
        else printf("%lld\n", ask(x, y, 1, n, 1));
    }
    return 0;
}