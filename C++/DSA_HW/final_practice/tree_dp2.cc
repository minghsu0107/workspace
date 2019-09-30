#pragma GCC optimize("O2" , "O3" , "Ofast", "no-stack-protector", "unroll-loops")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define int long long
#define double long double

using namespace std;

const int N = (int)2e5 + 5;

int a[N], n, sum[N], dp[N][3], vis[N][3];
vector<int> G[N];

int dfs(int u, int pa) {
  sum[u] = a[u];
  for (auto v : G[u]) if(v != pa) {
      sum[u] += dfs(v, u);
  }
  return sum[u];
}
int DP(int u, int b, int pa) {
  if (vis[u][b]) return dp[u][b];
  int &ans = dp[u][b]; ans = (int)-1e16; vis[u][b] = 1;
  assert(b == 1 || b == 2);
  if (b == 1) {
      ans = sum[u];
      for (auto v : G[u]) if(v != pa) {
          ans = max(ans, DP(v, 1, u));
      }
  }
  else {
    int mx = (int)-1e16, mx2 = (int)-1e16;
    for (auto v : G[u]) if(v != pa) {
          ans = max(ans, DP(v, 2, u));
          int vv = DP(v, 1, u);
          // get 1st and 2nd largest
          if(vv > mx) { mx2 = mx; mx = vv; }
          else if(vv == mx) { mx2 = mx; }
          else if(vv > mx2) { mx2 = vv; }
    }
    if(mx2 != (int)-1e16) ans = max(ans, mx + mx2);
  }
  return ans;
}

void init() {
  cin >> n;
  for (int i = 1 ; i <= n ; ++i) cin >> a[i];
  for (int i = 1 ; i < n ; ++i) {
      int u, v; cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
  }
}
void solve() {
  dfs(1, 0);
  memset(dp, -1, sizeof(dp));
  if (DP(1, 2, 0) == (int)-1e16) cout << "Impossible\n";
  else cout << DP(1, 2, 0) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t = 1; 
//  cin >> t;
  while (t--) {
      init();
      solve();
  }
}
/*
sum[u]: 以u為根的子樹的權和 (including u)
dp[u][1]: 以u為根 並選1個子樹的最大權和 (including u)
dp[u][2]: 以u為根 並選2個互斥子樹的最大權和 (excluding u)

There are 2 cases of final solution:
1. two subtrees have a same parent other than 1(root),
   i.e. they are both under another subtree
2. two subtrees are totally mutually exclusive,
   i.e. 1(root) is their only common ancestor

The answer should be the case with larger answer,
i.e. ans = dp[root][2] = max(case1, case2)

dp[u][2] 
= max( max(dp[i][2], for i in G[u]), dp[x][1] + dp[y][1] )
where dp[x][1], dp[y][1] are two subtree with largest answers 

dp[u][1]
= max(sum[u], max(dp[i][1], for i in G[u]))
*/