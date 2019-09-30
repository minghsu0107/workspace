#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int n, q;
// int a[maxn];
ll sum1[maxn], sum2[maxn];
int lowbit(int x) { return x&(-x); }
void update(ll a[],int x,ll val) {
    while (x <= maxn) {
        a[x] += val;
        x += lowbit(x);
    }
}
ll ask(ll a[],int x){
    ll res = 0;
    while(x) {
        res += a[x];
        x -= lowbit(x);
    }
    return res;
}
int main() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        ll val;
        cin >> val;
        //a[i] = val;
        update(sum1, i, val);
        update(sum2, i, i * val);
    }
    while(q--) {
        ll k, x, y;
        cin >> k >> x >> y;
        if(k == 1) {
            cout << (y + 1) * (ask(sum1, y)-ask(sum1, x-1)) - (ask(sum2, y)-ask(sum2, x-1)) << endl;
        }
        else {
            ll num = ask(sum1, x) - ask(sum1, x-1);
            update(sum1, x, y-num);
            // update(sum1, x, y - a[x]);
            // a[x] = y;
            ll num2 = ask(sum2, x) - ask(sum2, x-1);
            update(sum2, x, x*y-num2);
        }
    }
    return 0;
}