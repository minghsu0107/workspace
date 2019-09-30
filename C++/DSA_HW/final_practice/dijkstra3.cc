#include <cstdio> 
#include <iostream> 
#include <algorithm> 
#include <cstring> 
#include <vector> 
#include <queue> 
using namespace std; 
#define ms(x, n) memset(x, n, sizeof(x)); 
typedef long long LL; 
const int maxn = 1e5 + 5; 
const LL inf = 1e15; 
int N, M, S, T; 
struct node { 
    int v, w; //目标节点和权值 
    node(int vv, int ww) {
        v = vv, w = ww;
    } 
}; 
vector<node> G[maxn]; 
LL d1[maxn], d2[maxn]; //最短路和次短路 
typedef pair<LL, int> P; 
void dijkstra() { 
    fill(d1, d1+maxn, inf); 
    fill(d2, d2+maxn, inf); 
    priority_queue<P, vector<P>, greater<P> > q; //d1,d2共用队列 
    d1[S] = 0; //d2[1]不应初始化为0 
    q.push(P(d1[S], S)); 
    while (!q.empty()) { 
        P cur = q.top(); q.pop(); 
        LL d = cur.first;
        int u = cur.second; 
        if(d > d2[u]) continue; //直接跳过 
        for (int i = 0; i < G[u].size(); i++) { 
            node &e = G[u][i]; 
            LL td = d + e.w; //假设为第一种情况 
            if (d1[e.v] > td) { //恰好和第二种情况冲突 
                swap(td, d1[e.v]); 
                q.push(P(d1[e.v], e.v)); 
            } 
            if (td<d2[e.v] && td>d1[e.v]) { //更新d2 
                d2[e.v] = td; 
                q.push(P(d2[e.v], e.v)); 
            } 
        } 
    } 
} 
int main() { 
    int u, v, w, t; 
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &M);
        scanf("%d%d", &S, &T);
        ms(G, 0);
        for (int i = 0; i < M; ++i){ 
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(node(v, w));
            // G[v].push_back(node(u, w)); 
        } 
        dijkstra();
        printf("%lld\n", d2[T] - d1[T]);
    }
    return 0; 
} 
