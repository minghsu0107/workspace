#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 10;
const ll inf = 1e10;
int n, m;
ll p;

// maxl: max prefix sum of the current interval
// maxr: max suffix sum of the current interval
// maxs: max sum of the current interval
struct node {
    ll sum, maxs, maxl, maxr;
} a[maxn<<2];

void pushup(int rt) {
    a[rt].sum = a[rt<<1].sum + a[(rt<<1) + 1].sum;
    a[rt].maxl = max(a[rt<<1].maxl, a[rt<<1].sum + a[(rt<<1)+1].maxl);
    a[rt].maxr = max(a[(rt<<1)+1].maxr, a[(rt<<1)+1].sum + a[rt<<1].maxr);
    a[rt].maxs = max(max(a[rt<<1].maxs, a[(rt<<1)+1].maxs), a[rt<<1].maxr + a[(rt<<1)+1].maxl);
}

void build(int l, int r, int rt) {
    if (l == r) {
        scanf("%lld", &p);
        a[rt].sum = a[rt].maxs = a[rt].maxl = a[rt].maxr = p;
        return;
    }
    int mid = (l + r)>>1;
    build(l, mid, rt<<1);
    build(mid + 1, r, (rt<<1) + 1);
    pushup(rt);
}

node query(int x, int y, int l, int r, int rt) {
    if (x <= l && y >= r)
        return a[rt];
    int mid = (l + r)>>1;
    node L, R, S;
    L.sum = L.maxs = L.maxl = L.maxr = -inf;
    R.sum = R.maxs = R.maxl = R.maxr = -inf;
    S.sum = S.maxs = S.maxl = S.maxr = 0;
    if (x <= mid) {
        L = query(x, y, l, mid, rt<<1);
        S.sum += L.sum;
    }
    if (y > mid) {
        R = query(x, y, mid + 1, r, (rt<<1) + 1);
        S.sum += R.sum;
    }
    S.maxl = max(L.maxl, L.sum + R.maxl);
    S.maxr = max(R.maxr, R.sum + L.maxr);
    S.maxs = max(max(L.maxs, R.maxs), L.maxr + R.maxl);
    return S;
}

void update(int x,int y,int l,int r,int rt) {
    if (l == r) {
        a[rt].sum = a[rt].maxs = a[rt].maxl = a[rt].maxr = y;
        return;
    }
    int mid = (l + r)>>1;
    if(x <= mid) update(x, y, l, mid, rt<<1);
    else update(x, y, mid + 1, r, (rt<<1) + 1);
    pushup(rt);
}

int main() {
    scanf("%d%d",&n, &m);
    build(1, n, 1);
    int x;
    ll y, ans;
    ans = max(query(1, n, 1, n, 1).maxs, 0LL);
    printf("%lld\n", ans);
    while(m--) {
        scanf("%d%lld",&x, &y);
        update(x, y, 1, n, 1);
        ans = max(query(1, n, 1, n, 1).maxs, 0LL);
        printf("%lld\n", ans);
    }
    return 0;
}