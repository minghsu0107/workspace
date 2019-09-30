#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
 
typedef long long T;
char s[MAXN + 5];
int candicate[MAXN + 5], cand_len, m;
int wa[MAXN + 5],wb[MAXN + 5],wv[MAXN + 5],wc[MAXN + 5];
int r[MAXN + 5],sa[MAXN + 5],rak[MAXN + 5], height[MAXN + 5];
int dp[MAXN][20], dp2[MAXN][20];
 
int cmp(int *r,int a,int b,int l) {
      return r[a] == r[b] && r[a+l] == r[b+l];
}
 
void da(int *r,int *sa,int n,int m) {
      int i,j,p,*x=wa,*y=wb,*t;
      for( i=0;i<m;++i) wc[i]=0;
      for( i=0;i<n;++i) wc[x[i]=r[i]] ++;
      for( i=1;i<m;++i) wc[i] += wc[i-1];
      for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
      for( j= 1,p=1;p<n;j*=2,m=p){
            for(p=0,i=n-j;i<n;i++)y[p++] = i;
            for(i=0;i<n;++i)if(sa[i] >= j) y[p++] = sa[i] - j;
            for(i=0;i<n;++i)wv[i] = x[y[i]];
            for(i=0;i<m;++i) wc[i] = 0;
            for(i=0;i<n;++i) wc[wv[i]] ++;
            for(i=1;i<m;++i) wc[i] += wc[i-1];
            for(i=n-1;i>=0;--i) sa[--wc[wv[i]]] = y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;++i) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
 
      }
}
 
void calheight(int *r,int *sa,int n) {
 
      int i,j,k=0;
      for(i=1;i<=n;++i) rak[sa[i]] = i;
      for(i=0;i<n;height[rak[i++]] = k ) {
            for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
      }
 
}
void initRMQ(int n) {
      for(int i= 1;i<=n;++i) {
          dp[i][0] = height[i];
      }
      for(int j= 1; (1<<j) <= n; ++j ){
            for(int i = 1; i + (1<<j) - 1 <= n ; ++i) {
                  dp[i][j] = min(dp[i][j-1] , dp[i + (1<<(j-1))][j-1]);
            }
      }
 
}
void initRMQ2(int n) {
      for(int i= 1;i<=n;++i) {
          dp2[i][0] = sa[i];
      }
      for(int j= 1; (1<<j) <= n; ++j ){
            for(int i = 1; i + (1<<j) - 1 <= n ; ++i) {
                  dp2[i][j] = max(dp2[i][j-1] , dp2[i + (1<<(j-1))][j-1]);
            }
      }
 
}
int askRMQ(int L, int R) {     
      int k=0;
      while((1<<(k+1)) <= R-L+1) k++;
      return min(dp[L][k], dp[R - (1<<k) + 1][k]);
}
int askRMQ2(int L, int R) {     
      int k=0;
      while((1<<(k+1)) <= R-L+1) k++;
      return max(dp2[L][k], dp2[R - (1<<k) + 1][k]);
}
const T r1 = chrono::steady_clock::now().time_since_epoch().count(), r2 = chrono::steady_clock::now().time_since_epoch().count();
T h1[MAXN+5];
T h_base1[MAXN+5];
inline void hash_init1(int len, T prime=0xdefaced) {
    h_base1[0] = 1;
    for(int i = 1; i <= len; ++i) {
        h1[i] = (h1[i-1] * prime + s[i-1]);
        h_base1[i] = (h_base1[i-1] * prime);
    }
}
inline T get_hash(int l, int r) {
    return (h1[r+1]-(h1[l]*h_base1[r-l+1]));
} 
void solve1(int len) {
    int x = 0, idx = -1;
    if (m == 1) {
        printf("%d %d\n", len, 0);
        return;
    }
    initRMQ(len);
    initRMQ2(len);
    for (int i = 1; i + m - 1 <= len; ++i) {
        int tmp = askRMQ(i + 1, i + m - 1);
        if (tmp > x) {
            x = tmp;
            idx = askRMQ2(i, i + m - 1);
        }
        else if (tmp == x) {
            idx = max(idx, askRMQ2(i, i + m - 1));
        }
    }
    if (x == 0) puts("none");
    else printf("%d %d\n", x, idx);
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
void init(int len) {
    int cnt = 0;
     for (int i = 0; i < len; ++i) {
            r[i]=s[i] - 'a' + 1;
            cnt = max(cnt, r[i]);
    }
    r[len] = 0;
    da(r, sa, len+1, cnt+1);
    calheight(r, sa, len);
    hash_init1(len);
}
int main() {
    cin >> m;
    while (m) {
        cin >> s;
        int len = strlen(s);
        init(len);
 
        solve1(len);
        solve2(len);
        cin >> m;
    }
    return 0;
}