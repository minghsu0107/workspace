//區間修改 區間查詢
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll maxn = 1e6 + 10;
ll sum1[maxn], sum2[maxn], a[maxn];
int n,q;
int lowbit(int x){ return x&(-x); }
void add(int x,ll val) {
    for (int i = x; i <= n; i += lowbit(i)) {
        sum1[i] += val;
        sum2[i] += (x-1)*val;
    }
}
ll ask(int x) {
    ll res = 0;
    for(int i = x; i; i -= lowbit(i)) {
        res += x * sum1[i] - sum2[i];
    }
    return res;
}
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        add(i, a[i] - a[i-1]);
    }
    while(q--) {
        int id, l, r, x;
        scanf("%d", &id);
        if(id == 1) {
            scanf("%d%d%d", &l, &r, &x);
            add(l, x); add(r + 1, -x);
        }
        else{
            scanf("%d%d",&l, &r);
            printf("%lld\n",ask(r) - ask(l-1));
        }
    }
    return 0;
}
/*
我们继续用一个数组b【i】存第i个数与第i-1个数的差，即

b【i】=a【i】-a【i-1】，a【x】=b【1】+b【2】+……b【x】

我们建立树状数组sum1用来维护b的前缀和

我们也可以很容易得出：

a【1】+a【2】+……a【x】

=b【1】+（b【1】+b【2】）+……（b【1】+b【2】+……b【x】）

=x*b【1】+（x-1）*b【2】+……b【x】

=x*（b【1】+b【2】+……b【x】）-∑(i=1 to x)(i-1)*b[i]

,所以我们就多建立一个树状数组sum2用来维护（x-1）b【x】的前缀和就好了。
*/