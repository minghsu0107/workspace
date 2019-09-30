#include <bits/stdc++.h>
#define N 100005
#define M 100005
#define INF 1e15 // maximum path: 10^5 * 10^9
using namespace std;
typedef long long LL;
int n, m, S, T, en, en2, adj[N], adj2[N];
LL dis[N], dis2[N];
bool vis[N];

struct Edge {
    int from, to, w, next;
};
Edge e[M], rev[M];

void initializeGraph() {
    en = en2 = 0;
    memset(adj, -1, sizeof(adj));
    memset(adj2, -1, sizeof(adj2));
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
    
    for (int i = 0; i < n; ++i)
        dis[i] = INF;
    dis[s] = 0;
    q.emplace(s, dis[s]); 

    while(!q.empty()) {
        int p = q.top().first;
        LL d = q.top().second;
        q.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for(int i = adj[p]; i != -1; i = e[i].next) {
            if (!vis[e[i].to] && dis[e[i].to] > d + e[i].w) {
                dis[e[i].to] = d + e[i].w;
                q.emplace(e[i].to, dis[e[i].to]);
            }
        }
    }
}
void dijkstra2(int s) {
    while(!q.empty()) q.pop();
    memset(vis, false, sizeof(vis));
    
    for (int i = 0; i < n; ++i)
        dis2[i] = INF;
    dis2[s] = 0;
    q.emplace(s, dis2[s]); 

    while(!q.empty()) {
        int p = q.top().first;
        LL d = q.top().second;
        q.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for(int i = adj2[p]; i != -1; i = rev[i].next) {
            if (!vis[rev[i].to] && dis2[rev[i].to] > d + rev[i].w) {
                dis2[rev[i].to] = d + rev[i].w;
                q.emplace(rev[i].to, dis2[rev[i].to]);
            }
        }
    }
}
void solve() {
    LL minn = dis[T], tmp, ans = INF;
    for (int i = 0; i < en; ++i) {
        int u = e[i].from, v = e[i].to;
        tmp = dis[u] + e[i].w + dis2[v];       
        if(tmp > minn && tmp < ans) ans = tmp;
    }
    printf("%lld\n", ans - minn);
}
int main() {
    int tt;
    scanf("%d", &tt);
    while(tt--) {
        initializeGraph();
        scanf("%d%d", &n, &m);
        scanf("%d%d", &S, &T);
        int u, v, w;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            addRev(v, u, w);
        }
        dijkstra(S);
        dijkstra2(T);
        solve();
    }
}
/*
枚舉每條邊，求出從起點到終點且經過此邊的最短路，次短路即為答案次小者
for an edge (a, b ,w) (from a to b with weight w) 
shortest path = dis[a] + w + dis2[b],
where dis[a] is the shortest distance from source to a
and dis2[b] is the shortest distance from b to destination

we can get dis2[] by dijkstra on the transpose graph:
set the source as the destination in the orginal graph, 
and we can get the shortest distances from every vertice to the destination
in the orignal graph
*/