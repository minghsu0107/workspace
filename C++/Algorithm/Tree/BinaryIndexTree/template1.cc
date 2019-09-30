#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6;
int n,m;
ll sum[maxn];
int lowbit(int x){ return x&(-x); }
void add(int x, ll val) {
    while (x <= maxn){
        sum[x] += val;
        x += lowbit(x);
    }
}
ll getsum(int x) {
    ll res = 0;
    while(x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}
int main(){
    scanf("%d%d", &n, &m);
    ll c;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &c);
        add(i, c);
    }
    while(m--) {
        int id, x, y;
        scanf("%d%d%d", &id, &x, &y);
        if(id == 1) add(x, y); //a[x] += y
        else
            cout << getsum(y) - getsum(x-1) << endl;
    }
    return 0;
}