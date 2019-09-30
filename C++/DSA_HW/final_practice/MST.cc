#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 10;

int n, m, dis[MAXN], cnt;
bool vis[MAXN];
typedef pair<int, int> ii;
vector<ii> v[MAXN];
struct cmp {
    bool operator() (ii a, ii b) {
        return (a.second > b.second);
    }
};
priority_queue <ii, vector<ii>, cmp> pq;

void AddEdge(int from, int to, int w) {
    v[from].push_back(make_pair(to, w));
    v[to].push_back(make_pair(from, w));
}
void prim(int start) {
    memset(vis, false, sizeof vis);
    for (int i = 1; i <= n; ++i)
        dis[i] = 1e9;
    dis[start] = 0;
    pq.push((ii){start, dis[start]}); 
    
    while (!pq.empty()) {
        int p = pq.top().first;
        pq.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (ii x: v[p]) {
            int q = x.first, w = x.second;
            if (!vis[q] && w < dis[q]) {
                dis[q] = w;
                pq.emplace(q, dis[q]);
            }
        }
    }
}
void dfs(int s) {
    vis[s] = true;
    ++cnt;
    for (ii x: v[s]) {
        int p = x.first;
        if (!vis[p])
            dfs(p);
    }
}
void init() {
    cnt = 0;
    memset(vis, false, sizeof(vis));
    memset(v, 0, sizeof(v));
    while(pq.size()) pq.pop();
}
void getAns() {
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += dis[i];
    printf("%d\n", ans);
}
int main() {
    while (cin >> n >> m && m && n) {
        init();
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            AddEdge(a, b, c);
        }
        dfs(1);
        if (cnt != n) puts("-1");
        else {
            prim(1);
            getAns();
        }
    }
    return 0;
}