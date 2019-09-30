#include <bits/stdc++.h>
#define N 100010
using namespace std;
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
char st[N];
int m, pmin[N], qmax[N], rm[N];
namespace SA {
int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) fill_n(sa, n, -1); fill_n(cnt, m, 0);                  \
    for (int i = 0; i < n; ++i) cnt[s[i]]++;                                  \
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i-1];                           \
    for (int i = 0; i < m; ++i) cur[i] = cnt[i]-1;                            \
    for (int i = n1-1; ~i; --i) pushS(v[i]);                                  \
    for (int i = 1; i < m; ++i) cur[i] = cnt[i-1];                            \
    for (int i = 0; i < n; ++i) if (sa[i] > 0 &&  t[sa[i]-1]) pushL(sa[i]-1); \
    for (int i = 0; i < m; ++i) cur[i] = cnt[i]-1;                            \
    for (int i = n-1;  ~i; --i) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1)
void sais(int n, int m, int *s, int *t, int *p) {
    int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
    for (int i = n-2; ~i; --i) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
    for (int i = 1; i < n; ++i) rk[i] = t[i-1] && !t[i] ? (p[n1] = i, n1++) : -1;
    inducedSort(p);
    for (int i = 0, x, y; i < n; ++i) if (~(x = rk[sa[i]])) {
        if (ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
        else for (int j = p[x], k = p[y]; j <= p[x+1]; ++j, ++k)
            if ((s[j]<<1|t[j]) != (s[k]<<1|t[k])) {ch++; break;}
        s1[y = x] = ch;
    }
    if (ch+1 < n1) sais(n1, ch+1, s1, t+n, p+n1);
    else for (int i = 0; i < n1; ++i) sa[s1[i]] = i;
    for (int i = 0; i < n1; ++i) s1[i] = p[sa[i]];
    inducedSort(s1);
}
template<typename T>
int mapCharToInt(int n, const T *str) {
    int m = *max_element(str, str+n);
    fill_n(rk, m+1, 0);
    for (int i = 0; i < n; ++i) rk[str[i]] = 1;
    for (int i = 0; i < m; ++i) rk[i+1] += rk[i];
    for (int i = 0; i < n; ++i) s[i] = rk[str[i]] - 1;
    return rk[m];
}
// Ensure that str[n] is the unique lexicographically smallest character in str.
template<typename T>
void getSuf(int n, const T *str) {
    int m = mapCharToInt(++n, str);
    sais(n, m, s, t, p);
    for (int i = 0; i < n; ++i) rk[sa[i]] = i;
    for (int i = 0, h = ht[0] = 0; i < n-1; ++i) {
        int j = sa[rk[i]-1];
        while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
        if (ht[rk[i]] = h) h--;
    }
}
};
using namespace SA;
// use deque optimization to get 
// min height and max index in each sliding window
void solve1(int len) {
    if (m == 1) {
        printf("%d %d\n", len, 0);
        return;
    }
    int x = 0, idx = -1;
    int tail = 0, head = 1, r = 0, l = 1;
    for(int i = 1; i < m; i++){
        while(l <= r && sa[qmax[r]] <= sa[i])
            --r;
        qmax[++r] = i;
    }
    for(int i = 2; i < m; i++){ 
        while(head <= tail && ht[pmin[tail]] >= ht[i])
            --tail;   
        pmin[++tail] = i;
    }
    for(int i = m; i <= len; i++){
        while(head <= tail && ht[pmin[tail]] >= ht[i])
            --tail;
        pmin[++tail] = i;
        while(pmin[head] < i - m + 2)
            ++head;
 
        while(l <= r && sa[qmax[r]] <= sa[i])
            --r;
        qmax[++r] = i;
        while(qmax[l] < i - m + 1)
            ++l;
 
        if (ht[pmin[head]] > x) {
            x = ht[pmin[head]];  
            idx = sa[qmax[l]];        
        }
        else if (ht[pmin[head]] == x) {
            idx = max(idx, sa[qmax[l]]);
        }
    }
    if (x == 0) puts("none");
    else printf("%d %d\n", x, idx);
}
void solve2(int len) {
    int idx = -1;
    for (int i = 1; i < len; ++i) {
        if (rk[i] > rk[0]) continue;
        if (rm[rk[i]+1] == len - i) {
            if (rk[0] - rk[i] >= 2) {
                idx = i;
                break;
            }
            else {
                if (ht[rk[i]] == len - i
                    || ((rk[0] + 1 <= len) && ht[rk[0]+1] >= len - i)) {
                    idx = i;
                    break;
                }
            }
        }
    }
    if (idx == -1)puts("Just a legend");
    else printf("%s\n", st + idx);
}
void init(int len) {
    getSuf(len, st);
    // only need to do rmq of ht in [i, rk[0]], where 2 <= i <= rk[0]
    rm[rk[0]] = ht[rk[0]];  
    for (int i = rk[0]-1; i >= 2; --i)
        rm[i] = min(rm[i+1], ht[i]);
}
int main() {
    cin >> m;
    while (m) {
        cin >> st;
        int len = strlen(st);
        init(len);
 
        solve1(len);
        solve2(len);
        cin >> m;
    }
    return 0;
}