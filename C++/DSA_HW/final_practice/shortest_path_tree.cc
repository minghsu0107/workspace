#include<bits/stdc++.h>
#define maxn 300005
#define INF 1e15
using namespace std;

struct lpl {
    int to, dis, num;
} lin;
vector<lpl> point[maxn]; 

int n, m, s;
long long ans, dis[maxn];
bool vis[maxn];
queue<int> q;

struct ld {
    int num;
    long long dis;
} node[maxn];

inline void spfa() { 
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; ++i)
        dis[i] = INF;
    dis[s] = 0; 
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop(); 
        vis[now] = false;
        for(int i = point[now].size() - 1; i >= 0; --i) {
            int x = point[now][i].to;
            if(dis[x] > dis[now] + point[now][i].dis) {
                dis[x] = dis[now] + point[now][i].dis;
                if (!vis[x]) {
                    vis[x] = true; 
                    q.push(x);
                }
            }
        }       
    }
}

inline bool cmp(ld A, ld B) { return A.dis < B.dis; }

inline void solve() {
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        node[i].num = i; 
        node[i].dis = dis[i];
    }
    sort(node + 1, node + n + 1, cmp);

    int edge_id;
    for (int i = 1; i <= n; ++i) {
        int t = node[i].num; if (t == s) continue;
        int x = 2e9;
        for (int j = point[t].size() - 1; j >= 0; --j) {
            int now = point[t][j].to;
            if (dis[t] != dis[now] + point[t][j].dis) continue;
            if (point[t][j].dis < x) {
                x = point[t][j].dis; 
                edge_id = point[t][j].num; 

            }
        }
        ans += x; vis[edge_id] = true;
    }
}

inline void print() {
    cout << ans << endl;
    for (int i = 1; i <= m; ++i)
        if (vis[i]) printf("%d ", i);
    cout << endl;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int a, b, i = 1; i <= m; ++i) {
        scanf("%d%d%d", &a, &b, &lin.dis); lin.num = i;
        lin.to = b; point[a].push_back(lin);
        lin.to = a; point[b].push_back(lin);
    }
    scanf("%d", &s);

    spfa();
    solve();
    print();
    return 0;
}
/*
對於一個點的最短路，
只要有一條邊從一個近一點的點的最短路能夠轉移過來構成他的最短路就夠了
所以就貪心(choose vertice with shorter shortest distance first), 
for each vertex, 找一個最短的邊可以從一個近一點的點轉移過來
而近一點的點保證已在最短路徑樹內
(this is because we choose vertice that are nearer first)
*/