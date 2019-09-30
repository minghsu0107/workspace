#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#define N 100005
#define M 200005
#define INF 1e15 // maximum path: 10^5 * 10^9
using namespace std;
typedef long long LL;
int n, m, en, en2, adj[N], adj2[N], cnt[N][3], cnt2[N][3];
LL dis[N], dis2[N];
bool vis[N];
const int mod[3] = {1000000000 + 7, 1000000000 + 87, 1000000000 + 123};

struct Edge {
    int from, to, w, next;
};
Edge e[M], rev[M];

void initializeGraph() {
    en = en2 = 0;
    memset(adj, -1, sizeof(adj));
    memset(adj2, -1, sizeof(adj));
}

void addEdge(int from, int to, int w) {
    e[en] = (Edge){from, to, w, adj[from]}; adj[from] = en++;
}
void addRev(int from, int to, int w) {
    rev[en2] = (Edge){from, to, w, adj2[from]}; adj2[from] = en2++;
}


typedef pair<int, LL> ii;
struct cmp {
    bool operator() (ii a, ii b) {
        return (a.second > b.second);

    }
};
priority_queue <ii, vector<ii>, cmp> q;

void dijkstra(int s) {
    while(!q.empty()) q.pop();
    memset(vis, false, sizeof(vis));
    
    for (int i = 1; i <= n; ++i)
        dis[i] = INF;
    dis[s] = 0;
    q.emplace(s, dis[s]); 
    cnt[s][0] = cnt[s][1] = cnt[s][2] = 1;

    while(!q.empty()) {
        int p = q.top().first;
        LL d = q.top().second;
        q.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for(int i = adj[p]; i != -1; i = e[i].next) {
            if (dis[e[i].to] > d + e[i].w) {
                dis[e[i].to] = d + e[i].w;
                q.emplace(e[i].to, dis[e[i].to]);
                for (int j = 0; j < 3; ++j)
                    cnt[e[i].to][j] = cnt[p][j];
            }
            else if (dis[e[i].to] == d + e[i].w) {
                for (int j = 0; j < 3; ++j)
                    (cnt[e[i].to][j] += cnt[p][j]) %= mod[j];
            }
        }
    }
}
void dijkstra2(int s) {
    while(!q.empty()) q.pop();
    memset(vis, false, sizeof(vis));
    
    for (int i = 1; i <= n; ++i)
        dis2[i] = INF;
    dis2[s] = 0;
    q.emplace(s, dis2[s]); 
    cnt2[s][0] = cnt2[s][1] = cnt2[s][2] = 1;

    while(!q.empty()) {
        int p = q.top().first;
        LL d = q.top().second;
        q.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for(int i = adj2[p]; i != -1; i = rev[i].next) {
            if (dis2[rev[i].to] > d + rev[i].w) {
                dis2[rev[i].to] = d + rev[i].w;
                q.emplace(rev[i].to, dis2[rev[i].to]);
                for (int j = 0; j < 3; ++j)
                    cnt2[rev[i].to][j] = cnt2[p][j];
            }
            else if (dis2[rev[i].to] == d + rev[i].w) {
                for (int j = 0; j < 3; ++j)
                    (cnt2[rev[i].to][j] += cnt2[p][j]) %= mod[j];
            }
        }
    }
}
void solve1() {
    cout << dis[2] << '\n'; 
}
void solve2() {
    cout << cnt[2][0] << '\n';
}

void solve3() {
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (dis[e[i].from] + e[i].w + dis2[e[i].to] != dis[2])
            continue;
 
        bool uniq = true;
        for (int j = 0; j < 3; ++j)
            uniq &= cnt[e[i].from][j] * 1ll * cnt2[e[i].to][j] % mod[j] == cnt[2][j];
 
        ans += (int)uniq;
    }
    cout << ans << '\n';
}
int main() {
    initializeGraph();
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addRev(v, u, w);
    }
    dijkstra(1);
    dijkstra2(2);
    solve1(); 
    solve2();
    solve3();
}
