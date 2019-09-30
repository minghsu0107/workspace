#include <bits/stdc++.h>
#include <bits/extc++.h>
#define MAXN 100000
#define prime_mod1 1073676287 // prime_mod 必須要是質數
#define prime_mod2 1000000123
// 1e9 + 7, 1e9 + 9, 1e9 + 87, 1e9 + 123 are all prime
// str length <= 10^5, 所以hash大約要10^10級別 (n^2 substrings in total)
// so we sould do hash twice
using namespace std;
using namespace __gnu_pbds;
typedef long long T;
typedef pair<T, T> pii;
char s[MAXN + 5];
int tail[MAXN + 5], m;
int candicate[MAXN + 5], cand_len;

struct chash {
	static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    int operator()(pii x) const {
    	uint64_t a = splitmix64(x.first + FIXED_RANDOM);
    	uint64_t b = splitmix64(x.second + FIXED_RANDOM);
    	return a * 31 + b; 
    }
};
gp_hash_table<pii,int,chash> hash_table1;
T h1[MAXN+5]; // hash陣列
T h_base1[MAXN+5]; // h_base[n]=(prime^n)%prime_mod
T h2[MAXN+5];
T h_base2[MAXN+5];
inline void hash_init1(int len, T prime=0xdefaced) {
	h_base1[0] = 1;
	for(int i = 1;i <= len; ++i){
		h1[i] = (h1[i-1] * prime + s[i-1]) % prime_mod1;
		h_base1[i] = (h_base1[i-1] * prime) % prime_mod1;
	}
}
inline T get_hash1(int l, int r) { // 閉區間寫法，設編號為0 ~ len-1
	return (h1[r+1]-(h1[l]*h_base1[r-l+1])%prime_mod1+prime_mod1)%prime_mod1;
}
inline void hash_init2(int len, T prime=131) {
	h_base2[0] = 1;
	for(int i = 1;i <= len; ++i){
		h2[i] = (h2[i-1] * prime + s[i-1]) % prime_mod2;
		h_base2[i] = (h_base2[i-1] * prime) % prime_mod2;
	}
}
inline T get_hash2(int l, int r) { // 閉區間寫法，設編號為0 ~ len-1
	return (h2[r+1]-(h2[l]*h_base2[r-l+1])%prime_mod2+prime_mod2)%prime_mod2;
}
bool check1(int l, int len) {
	hash_table1.clear();
	bool flag = false;
	for (int i = 0; i + l - 1 < len; ++i) {
		T hs1 = get_hash1(i, i + l - 1);
		T hs2 = get_hash2(i, i + l - 1);
		pair<T, T> p(hs1, hs2); 
		if (hash_table1.find(p) == hash_table1.end())
			hash_table1[p] = 0;
		hash_table1[p]++;

		if (hash_table1[p] >= m) {
            tail[l] = i;
            flag = true;
        }
	}
	if (flag) return true;
	return false;
} 
void solve1(int len) {
	int x = 0, y = len;
	while (x < y) { // 左閉右閉
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
		T hs1 = get_hash1(0, k);
		T hs2 = get_hash2(0, k);
		if (hs1 == get_hash1(len - 1 - k, len - 1)
			&& hs2 == get_hash2(len - 1 - k, len - 1))
			candicate[cand_len++] = k + 1;
	}
}
bool check2(int l, int len) {
	T hs1 = get_hash1(0, l - 1);
	T hs2 = get_hash2(0, l - 1);
	for (int i = 1; i + l - 1 < len - 1; ++i) {
		T tmp1 = get_hash1(i, i + l - 1);
		T tmp2 = get_hash2(i, i + l - 1);
		if (hs1 == tmp1 && hs2 == tmp2) return true;
	}
	return false;
}
void solve2(int len) {
	init_cand(len);
	int x = -1, y = cand_len - 1; 
	while (x < y) { // 左閉右閉
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
}
/*
Generally speaking,
for [x,y]
m = (x+y+1)/2 when y = m-1
m = (x+y)/2 when x = m+1
*/