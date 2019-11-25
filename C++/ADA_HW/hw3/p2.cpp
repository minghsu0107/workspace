#include <bits/stdc++.h>
#define N 200005
#define M 500005
#define INF 1e15
using namespace std;
typedef long long ll;

int adj[N], n, m, S, T, en;
ll dis[N], cost[N], L;
bool vis[N];

struct Edge {
    int from;
    int to;
    ll d;
    ll c;
    int next;
};
Edge e[M<<1];

void initializeGraph() {
    en = 0;
    memset(adj, -1, sizeof(adj));
}

void addEdge(int from, int to, ll d, ll c) {
    e[en] = (Edge){from, to, d, c, adj[from]}; 
    adj[from] = en++;
}

struct Node {
    int p;
    ll val;
    Node() {}
    Node(int _p, ll _val): p(_p), val(_val) {}
};
bool operator< (const Node &a, const Node &b) {
    return (a.val > b.val);
}

bool operator> (const Node &a, const Node &b) {
    return (a.val < b.val);
}


void dijkstra(int s) {
    priority_queue <Node> q;
    while(!q.empty()) q.pop();
    
    for (int i = 0; i < n; ++i)
        cost[i] = INF;
    cost[s] = 0;
    q.emplace(s, cost[s]); 

    while (!q.empty()) {
        int p = q.top().p;
        ll c = cost[p];
        q.pop();
        for (int i = adj[p]; i != -1; i = e[i].next) {
            if (cost[e[i].to] > max(c, e[i].c)) {
                cost[e[i].to] = max(c, e[i].c);
                q.emplace(e[i].to, cost[e[i].to]);
            }
        }
    }
}

void dijkstra2(int s) {
    priority_queue <Node> q;
    while(!q.empty()) q.pop();
    memset(vis, false, sizeof(vis));
    
    for (int i = 0; i < n; ++i)
        dis[i] = INF;
    dis[s] = 0;
    q.emplace(s, dis[s]);

    while (!q.empty()) {
        int p = q.top().p;
        ll d = dis[p];
        q.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (int i = adj[p]; i != -1; i = e[i].next) {
            if (!vis[e[i].to] && e[i].c <= L && dis[e[i].to] > d + e[i].d) {
                dis[e[i].to] = d + e[i].d;
                q.emplace(e[i].to, dis[e[i].to]);
            }
        }
    }
}

int main() {
    initializeGraph();
    scanf("%d%d", &n, &m);
    scanf("%d%d", &S, &T);
    int u, v;
    ll d, c;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lld%lld", &u, &v, &d, &c);
        addEdge(u, v, d, c);
        addEdge(v, u, d, c);
    }
    dijkstra(S);
    L = cost[T];
    dijkstra2(S);
    printf("%lld %lld\n", dis[T], L);
    return 0;
}