#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;
#pragma GCC optimize("03", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
typedef pair<int, int> pii;
char s[MAXN + 5];
int m;
int wa[MAXN + 5],wb[MAXN + 5],wv[MAXN + 5],wc[MAXN + 5];
int r[MAXN + 5],sa[MAXN + 5],rak[MAXN + 5], height[MAXN + 5];
pii dp[MAXN][20];
 
int cmp(int *r,int a,int b,int l) {
      return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int *r,int *sa,int n,int m) {
      int i,j,p,*x=wa,*y=wb,*t;
      for( i=0;i<m;i++) wc[i]=0;
      for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
      for( i=1;i<m;i++) wc[i] += wc[i-1];
      for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
      for( j= 1,p=1;p<n;j*=2,m=p){
            for(p=0,i=n-j;i<n;i++)y[p++] = i;
            for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
            for(i=0;i<n;i++)wv[i] = x[y[i]];
            for(i=0;i<m;i++) wc[i] = 0;
            for(i=0;i<n;i++) wc[wv[i]] ++;
            for(i=1;i<m;i++) wc[i] += wc[i-1];
            for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
 
      }
}
void calheight(int *r,int *sa,int n) {
      int i,j,k=0;
      for(i=1;i<=n;i++) rak[sa[i]] = i;
      for(i=0;i<n;height[rak[i++]] = k ) {
            for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
      }
}
void initRMQ(int n) {
      for(int i= 1; i <= n; i++) {
          dp[i][0] = make_pair(height[i], sa[i]);
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
        if (rak[i] > rak[0]) continue;
        if (askRMQ(rak[i]+1, rak[0]).first == len - i) {
            if (rak[0] - rak[i] >= 2) {
                idx = i;
                break;
            }
            else {
                if (height[rak[i]] == len - i
                    || ((rak[0] + 1 <= len) && height[rak[0]+1] >= len - i)) {
                    idx = i;
                    break;
                }
            }
        }
    }
    if (idx == -1)puts("Just a legend");
    else printf("%s\n", s + idx);
}
void init(int len) {
    int cnt = 0;
     for (int i = 0; i < len; ++i) {
            r[i]=s[i] - 'a' + 1;
            cnt = max(cnt, r[i]);
    }
    r[len] = 0;
    da(r, sa, len + 1, cnt + 1);
    calheight(r, sa, len);
    initRMQ(len);
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