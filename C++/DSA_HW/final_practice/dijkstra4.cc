#include <string.h>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long LL;
const LL inf = 1e15;
const int maxn = 100005;
const int maxm = 100005;
 
struct node1 {
    int v, w, next;
} edge[maxm];

struct node {
    int v;
    LL w;
    node(int a, LL b): v(a), w(b){}
    bool operator<(const node k)const {
        return w > k.w;
    }
};
priority_queue<node> q;
int n, m, no, s, t;
int head[maxn];
LL dis[maxn][2];
// int vis[maxn][2];
inline void init() {
    no = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < n; ++i) {
        dis[i][0] = dis[i][1] = inf;
    }
    // memset(vis, 0, sizeof (vis));
    while(!q.empty()) q.pop();
}
inline void add(int u, int v, int w) {
    edge[no].v = v, edge[no].w = w;
    edge[no].next = head[u]; head[u] = no++;
}
void DJ()
{
    dis[s][0] = 0;
    q.push(node(s, 0));
    while(!q.empty()) {
        node top = q.top(); q.pop();
        //if(vis[top.v][top.key]) continue;
        //vis[top.v][top.key] = 1;
        for (int k = head[top.v]; k != -1; k = edge[k].next) {
            LL tmp = top.w + edge[k].w;
            if(dis[edge[k].v][0] > tmp) {
                swap(dis[edge[k].v][0], tmp);
                q.push(node(edge[k].v, dis[edge[k].v][0]));
            }
            if(dis[edge[k].v][1] > tmp && dis[edge[k].v][0] < tmp) {
                // strictly sec shortest
                dis[edge[k].v][1] = tmp;
                q.push(node(edge[k].v, dis[edge[k].v][1]));
            }
        }
    }
}
int main()
{
    int tt;
    scanf("%d", &tt);
    while(tt--) {
        int u, v, w;
        scanf("%d %d", &n, &m); 
        init();
        scanf("%d%d", &s, &t);
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
        }
        DJ();
        printf("%lld\n", dis[t][1] - dis[t][0]);  //打印次短路 
    }
    return 0;
}
/*
if tmp is smaller than dis0, we update dis0 with tmp, and we use the
orginal value of dis0 (before updated) to update dis1

if tmp is greater than dis0 but smaller than dis1, we update
dis1 with tmp because tmp can be a posible solution of dis1 
in the current condition 

if tmp is equal to dis0, than we skip. This is because we want the 
strictly second shortest path
(if we want a solution that is not strict, we update dis1 with tmp
 when tmp is equal to dis0)

*/