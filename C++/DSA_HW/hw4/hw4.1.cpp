#include <bits/stdc++.h>
#include <bits/extc++.h>
#define MAXN 100000
#define prime_mod1 1073676287
#define prime_mod2 998244353
using namespace std;
using namespace __gnu_pbds;
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
 
typedef long long T;
char s[MAXN + 5];
int tail[MAXN + 5], m;
int candicate[MAXN + 5], cand_len;
const T r1 = chrono::steady_clock::now().time_since_epoch().count(), r2 = chrono::steady_clock::now().time_since_epoch().count();
 
gp_hash_table<T, int> hash_table1;
T h1[MAXN+5];
T h_base1[MAXN+5];
T h2[MAXN+5];
T h_base2[MAXN+5];
inline void hash_init1(int len, T prime=0xdefaced) {
    h_base1[0] = 1;
    for(int i = 1; i <= len; ++i) {
        h1[i] = (h1[i-1] * prime + s[i-1]) % prime_mod1;
        h_base1[i] = (h_base1[i-1] * prime) % prime_mod1;
    }
}
inline void hash_init2(int len, T prime=131) {
    h_base2[0] = 1;
    for(int i = 1; i <= len; ++i) {
        h2[i] = (h2[i-1] * prime + s[i-1]) % prime_mod2;
        h_base2[i] = (h_base2[i-1] * prime) % prime_mod2;
    }
}
inline T get_hash(int l, int r) {
    T a = (h1[r+1]-(h1[l]*h_base1[r-l+1])%prime_mod1+prime_mod1)%prime_mod1;
    T b = (h2[r+1]-(h2[l]*h_base2[r-l+1])%prime_mod2+prime_mod2)%prime_mod2;
    pair<T, T> x = {a + r1, b + r2};
    x.first += 0x9e3779b97f4a7c15;
    x.first = (x.first ^ (x.first >> 30)) * 0xbf58476d1ce4e5b9;
    x.first = (x.first ^ (x.first >> 27)) * 0x94d049bb133111eb;
    x.second += 0x9e3779b97f4a7c15;
    x.second = (x.second ^ (x.second >> 30)) * 0xbf58476d1ce4e5b9;
    x.second = (x.second ^ (x.second >> 27)) * 0x94d049bb133111eb;
    return (x.first ^ (x.first >> 31)) ^ (x.second ^ (x.second >> 31));
}
bool check1(int l, int len) {
    hash_table1.clear();
    int cnt = 0;
    for (int i = 0; i + l - 1 < len; ++i) {
        T hs = get_hash(i, i + l - 1);
        if (hash_table1.find(hs) == hash_table1.end())
            hash_table1[hs] = 0;
        hash_table1[hs]++;
 
        int tmp = hash_table1[hs];
        cnt = max(cnt, tmp);
        if (tmp >= m) tail[l] = i;
    }
    if (cnt >= m) return true;
    return false;
} 
void solve1(int len) {
    int x = 0, y = len;
    while (x < y) {
        int mid = (x + y + 1)>>1;
        if (check1(mid, len)) x = mid;
        else y = mid - 1;
    }
    if (x == 0) puts("none");
    else printf("%d %d\n", x, tail[x]);
}
void init_cand(int len) {
    cand_len = 0;
    for (int k = 0; k < len; ++k) {
        if (get_hash(0, k) == get_hash(len - 1 - k, len - 1))
            candicate[cand_len++] = k + 1;
    }
}
bool check2(int l, int len) {
    T hs = get_hash(0, l - 1);
 
    for (int i = 1; i + l - 1 < len - 1; ++i) {
        if (hs == get_hash(i, i + l - 1)) return true;
    }
    return false;
}
void solve2(int len) {
    init_cand(len);
    int x = -1, y = cand_len - 1; 
    while (x < y) {
        int mid = (x + y + 1)>>1;
        if (check2(candicate[mid], len)) x = mid;
        else y = mid - 1;
    }
    if (x == -1) puts("Just a legend");
    else printf("%s\n", s + len - candicate[x]);
}
int main() {
    scanf("%d", &m);
    while (m) {
        scanf("%s", s);
        int len = strlen(s);
        hash_init1(len);
        hash_init2(len);
 
        solve1(len);
        solve2(len);
        scanf("%d", &m);
    }
    return 0;
}