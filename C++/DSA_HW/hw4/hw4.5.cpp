#include <bits/stdc++.h>
#define N 100010
using namespace std;
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
typedef pair<int, int> pii;
char st[N];
int m;
pii dp[N][20];

namespace SA {
int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) fill_n(sa, n, -1); fill_n(cnt, m, 0);                  \
    for (int i = 0; i < n; i++) cnt[s[i]]++;                                  \
    for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];                           \
    for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
    for (int i = n1-1; ~i; i--) pushS(v[i]);                                  \
    for (int i = 1; i < m; i++) cur[i] = cnt[i-1];                            \
    for (int i = 0; i < n; i++) if (sa[i] > 0 &&  t[sa[i]-1]) pushL(sa[i]-1); \
    for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
    for (int i = n-1;  ~i; i--) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1)
void sais(int n, int m, int *s, int *t, int *p) {
    int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
    for (int i = n-2; ~i; i--) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
    for (int i = 1; i < n; i++) rk[i] = t[i-1] && !t[i] ? (p[n1] = i, n1++) : -1;
    inducedSort(p);
    for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
        if (ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
        else for (int j = p[x], k = p[y]; j <= p[x+1]; j++, k++)
            if ((s[j]<<1|t[j]) != (s[k]<<1|t[k])) {ch++; break;}
        s1[y = x] = ch;
    }
    if (ch+1 < n1) sais(n1, ch+1, s1, t+n, p+n1);
    else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
    for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
    inducedSort(s1);
}
template<typename T>
int mapCharToInt(int n, const T *str) {
    int m = *max_element(str, str+n);
    fill_n(rk, m+1, 0);
    for (int i = 0; i < n; i++) rk[str[i]] = 1;
    for (int i = 0; i < m; i++) rk[i+1] += rk[i];
    for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
    return rk[m];
}
// Ensure that str[n] is the unique lexicographically smallest character in str.
template<typename T>
void suffixArray(int n, const T *str) {
    int m = mapCharToInt(++n, str);
    sais(n, m, s, t, p);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0, h = ht[0] = 0; i < n-1; i++) {
        int j = sa[rk[i]-1];
        while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
        if (ht[rk[i]] = h) h--;
    }
}
};
using namespace SA;
void initRMQ(int n) {
      for(int i= 1; i <= n; i++) {
          dp[i][0] = make_pair(ht[i], sa[i]);
      }
      for(int j= 1; (1<<j) <= n; j++ ) {
            for(int i = 1; i + (1<<j) - 1 <= n ; i ++ ) {
                  dp[i][j].first = min(dp[i][j-1].first , dp[i + (1<<(j-1))][j-1].first);
                  dp[i][j].second = max(dp[i][j-1].second , dp[i + (1<<(j-1))][j-1].second);
            }
      } 
}
pii askRMQ(int L, int R) {     
      int k=0;
      while((1<<(k+1)) <= R-L+1) k++;
      return make_pair(min(dp[L][k].first, dp[R - (1<<k) + 1][k].first), 
                       max(dp[L][k].second, dp[R - (1<<k) + 1][k].second));
}

void solve1(int len) {
    int x = 0, idx = -1;
    if (m == 1) {
        printf("%d %d\n", len, 0);
        return;
    }
    for (int i = 1; i + m - 1 <= len; ++i) {
        pii tmp = askRMQ(i + 1, i + m - 1);
        if (tmp.first > x) {
            x = tmp.first;
            idx = askRMQ(i, i + m - 1).second;
        }
        else if (tmp.first == x) {
            idx = max(idx, askRMQ(i, i + m - 1).second);
        }
    }
    if (x == 0) puts("none");
    else printf("%d %d\n", x, idx);
}
void solve2(int len) {
    int idx = -1;
    for (int i = 1; i < len; ++i) {
        if (rk[i] > rk[0]) continue;
        if (askRMQ(rk[i]+1, rk[0]).first == len - i) {
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
    suffixArray(len, st);
    initRMQ(len);
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
