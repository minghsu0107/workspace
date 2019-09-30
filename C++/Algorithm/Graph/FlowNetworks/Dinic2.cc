#include <bits/stdc++.h>
using namespace std;
const int V = 100, E = 1000;
 
int adj[V]; // adjacency lists，初始化為-1, save the previous edge index in array e
struct Element {int b, r, next, rev;} e[E*2];
int en = 0;
void initializeGraph() {
    memset(adj, -1, sizeof(adj));
}
void addEdge(int a, int b, int c) {
    e[en] = (Element){b, c, adj[a], en + 1}; adj[a] = en++;
    e[en] = (Element){a, 0, adj[b], en - 1}; adj[b] = en++;
}
 
int d[V];       // 最短距離
bool visit[V];  // DFS visit record
 
// 計算最短路徑，求出容許網路。
bool BFS(int s, int t) {
    for (int i = 0 ; i < V ; i++) 
        d[i] = -1; 
    d[s] = 0;
    queue <int> q;
    q.push(s);
    while (!q.empty()) {
        int a = q.front();
        q.pop();
        for (int i = adj[a]; i != -1; i = e[i].next) {
            int b = e[i].b;
            if (e[i].r > 0 && d[b] < 0) {
                d[b] = d[a] + 1;
                q.push(b);
            }
        }
    }
    return d[t] < 0 ? false: true;
}
 
// 求出一條最短擴充路徑，並擴充流量。
int DFS(int a, int df, int t) {
    if (a == t) return df;
 
    if (visit[a]) return 0;
    visit[a] = true;
 
    for (int i = adj[a]; i != -1; i = e[i].next) {
        int b = e[i].b;
        if (e[i].r > 0 && d[a] + 1 == d[b]) {
            int f = DFS(b, min(df, e[i].r), t);
            if (f) {
                e[i].r -= f;
                // e[e[i].rev].r += f;
                e[i^1].r += f;
                return f;
            }
        }
    }
    return 0;
}
 
int dinic(int s, int t) {
    int flow = 0;
    while (BFS(s, t) == true) { 
        while (true) {
            memset(visit, false, sizeof(visit));
            int f = DFS(s, 1e9, t);
            if (!f) break;
            flow += f;
        }
    }
    return flow;
}

int main(int argc, char const *argv[])
{   
    initializeGraph();
    addEdge(0, 1, 16 );
    addEdge(0, 2, 13 ); 
    addEdge(1, 2, 10 ); 
    addEdge(1, 3, 12 ); 
    addEdge(2, 1, 4 ); 
    addEdge(2, 4, 14); 
    addEdge(3, 2, 9 ); 
    addEdge(3, 5, 20 ); 
    addEdge(4, 3, 7 ); 
    addEdge(4, 5, 4); 
    cout << "Maximum flow " << dinic(0, 5); 
    return 0;
}