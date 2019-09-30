#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000010
#define ll long long
const int prime_mod = 1e9 + 7;
const int c = 26;

int n, k, nxt[MAXN];
char s[MAXN];

void getNext(char* p) {
    int i = 1, j = 0;
    nxt[0] = -1;
    int len = strlen(p);
    while(i < len) {
        if(j == -1 || p[i] == p[j]) {
            nxt[++i] = ++j;
        } else
            j = nxt[j];
    }
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
    getNext(s);
    ll ans = 0;
    int ptr = n;
    while (ptr) {
        if(2 * n - ptr > k) break;
        ans++;
        ptr = nxt[ptr];
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
    printf("%lld\n", ans);
    return 0;
}