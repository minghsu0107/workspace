// State Space Search: Uniform-cost Search
// no negative weight
#include <bits/stdc++.h>
#define N 16
using namespace std;

struct edge { 
	int u , v , w; 
};
bool operator< (edge e1, edge e2) { return e1.w > e2.w; }
int w[N][N];
bool vis[N];
int dis[N], parent[N];

void AddEdge(int from, int to, int weight) {
	w[from][to] = weight;
}

void label_setting_with_priority_queue(int source, int n)
{
    for (int i = 0; i < n; i++) {
    	vis[i] = false;
        dis[i] = 1e9;
        parent[i] = -1;
    }

    priority_queue<edge> pq;
 
    int a = source;
    dis[a] = 0;
    parent[a] = -1;
    vis[a] = true;
 
    for (int i = 0; i< n - 1; i++) {
    	// 窮舉邊
        for (int b = 0; b < n; b++) {
            if (!vis[b] && w[a][b] != 0)
                pq.push( (edge){a, b, dis[a] + w[a][b]} );
        }
 
        // 找出下一個要加入到最短路徑樹的邊（與點）
        edge e = (edge){-1, -1, 0};
        while (!pq.empty()) {
            e = pq.top(); pq.pop();
            if (!vis[e.v]) break;
        }
 
        // 起點有連通的最短路徑都已找完
        if (e.u == -1 || e.v == -1) break;
 
        a = e.v;
        dis[a] = e.w;
        parent[a] = e.u;
        vis[a] = true;
    }
}
int main() {
	int n = 6, start = 0;
	AddEdge(0, 1, 8); AddEdge(0, 5, 1);
	AddEdge(1, 0, 3); AddEdge(1, 2, 1);
	AddEdge(3, 1, 4); AddEdge(3, 2, 6); AddEdge(3, 4, 7); AddEdge(3, 5, 3);
	AddEdge(5, 3, 2); AddEdge(5, 4, 8);
    label_setting_with_priority_queue(start, n);

    cout << "distance[]:\n";
    for (int i = 0; i < n; i++)
        cout << setw(4) << dis[i];
    cout << endl;

    cout << "predecessor[]:\n";
    for (int i = 0; i < n; i++)
        cout << std::setw(4) << parent[i];
    cout << endl;
}
// O(ElogE)