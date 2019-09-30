#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000010
#define ll long long
const int prime_mod = 1e9 + 7;
const int c = 26;

int n, k;
char s[MAXN];

ll h[MAXN];
ll h_base[MAXN];

inline void hash_init(int len, ll prime=0xdefaced) {
    h_base[0] = 1;
    for(int i = 1; i <= len; ++i){
        h[i] = (h[i-1] * prime + s[i-1]) % prime_mod;
        h_base[i] = (h_base[i-1] * prime) % prime_mod;
    }
}
inline ll get_hash(int l, int r) {
    return (h[r+1]-(h[l]*h_base[r-l+1])%prime_mod+prime_mod)%prime_mod;
}

ll pw(ll a, int n) {
    ll res = 1;
    while(n) {
        if (n&1) res = res * a % prime_mod;
        a = a * a % prime_mod, n >>= 1;
    }
    return res;
}

ll INV(ll a) { return pw(a, prime_mod - 2); }

int main() {
    scanf("%d%d",&n, &k);
    scanf("%s", s);
    hash_init(strlen(s));
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        ll pre = get_hash(0, i);
        ll suf = get_hash(n - i - 1, n - 1);
        if(pre == suf && 2 * n - (i + 1) <= k) ans++;
    }
    if (k >= 2 * n) {
       
       int m = k - 2 * n;
       ll tmp = pw(c, m + 1);
       tmp = (tmp - 1 + prime_mod) % prime_mod;
       tmp = tmp * INV(c-1) % prime_mod;
       ans = (ans + tmp) % prime_mod;
       
        /*
        int m = k - 2 * n;
        ll cur = 1;
        for (int i = 0; i <= m; i++) {
            ans = (ans + cur) % prime_mod;
            cur = cur * c % prime_mod;
        }
        */
    }
    printf("%lld\n",ans);
    return 0;
}