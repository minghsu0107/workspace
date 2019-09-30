#include <bits/stdc++.h>
#define N 100005
#define M 100005
#define INF 1e15 // maximum path: 10^5 * 10^9
using namespace std;
typedef long long LL;
typedef pair<int, LL> ii;
int n, m, S, T, en, en2, adj[N], adj2[N];
bool vis[N];
// dis2[] aves h_score of every node(dis2[v] = h_score from v to end)
LL dis[N], dis2[N];
set<LL> dis_kth; 

struct Edge {
    int from, to, w, next;
};
Edge e[M], rev[M];
struct cmp {
    bool operator() (ii a, ii b) {
        return (a.second > b.second);

    }
};
struct Ed { 
    int to;
    LL len; 
    Ed(){} 
    Ed(int t, LL l):to(t), len(l){} 
}; 


bool operator<(const Ed &a, const Ed &b) { 
    return (a.len + dis2[a.to]) > (b.len + dis2[b.to]); 
} 
priority_queue <ii, vector<ii>, cmp> q;

// min heap, qq.top = node with smallest f_score(g_score + h_score)
priority_queue<Ed> qq;

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

void dijkstra(int s, int* adj, LL* dis, Edge* e) {
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
LL a_star(int K) {
    while(!qq.empty()) qq.pop();
    dis_kth.clear();
    qq.emplace(S, 0);
    while (!qq.empty()) { 
        int x = qq.top().to; 
        LL d = qq.top().len; //d = g_score of x(actual dis from start to x)
        qq.pop(); 
        if(x == T) dis_kth.insert(d);//如果到达终点就加到 set
        if(K == dis_kth.size() && x == T) return d;//大小相同并且是终点则直接返回这个值

        for(int i = adj[x]; i != -1; i = e[i].next) {
            int y = e[i].to; 
            LL len = e[i].w; 
            // d+len is new g_score
            qq.emplace(y, d + len); 
        }
    } 
     
}
void solve() {
    dijkstra(S, adj, dis, e);
    dijkstra(T, adj2, dis2, rev);
    printf("%lld\n", a_star(2) - dis[T]);
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
        solve();
    }
}