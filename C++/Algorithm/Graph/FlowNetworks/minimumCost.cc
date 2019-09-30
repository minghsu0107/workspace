#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;
static const int maxn = 1000;

struct Edge {
	int from, to, cap, flow, cost;
};

struct MCMF {
	int n, m;
	vector <Edge> edges;
	vector<int> G[maxn];
    int inq[maxn];
    int d[maxn];
	int a[maxn];   
	int p[maxn];   // p[i] saves the index of edge that goes into vertex i 
    

	void init(int n) {
        this->n = n;
		for (int i = 0; i < n; ++i) G[i].clear();
		edges.clear();
	}

	void addEdge(int from, int to, int cap, int cost) {
		edges.push_back((Edge){from, to, cap, 0, cost});
		edges.push_back((Edge){to, from, 0, 0, -cost});
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
    
    bool BellmanFord(int s, int t, int& flow, long long& cost) {
        for (int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for (int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += a[t];
        cost += (long long)d[t] * (long long)a[t];
        for (int u = t; u != s; u = edges[p[u]].from) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
        }
        return true;   
    }

	int minCostMaxFlow(int s, int t, long long& cost) {
        int flow = 0; cost = 0;
        while (BellmanFord(s, t, flow, cost));
        return flow;
    }
};

int main() {
	MCMF g;
	g.init(6);
    g.addEdge(0, 1, 16, 1);
    g.addEdge(0, 2, 13, 1); 
    g.addEdge(1, 2, 10, 1); 
    g.addEdge(1, 3, 12, 1); 
    g.addEdge(2, 1, 4, 1); 
    g.addEdge(2, 4, 14, 1); 
    g.addEdge(3, 2, 9, 1); 
    g.addEdge(3, 5, 20, 1); 
    g.addEdge(4, 3, 7, 1); 
    g.addEdge(4, 5, 4, 1);
    int s = 0, t = 5;

    long long cost = 0;
    cout << "Maximum flow " << g.minCostMaxFlow(s, t, cost) << endl;
    cout << cost << endl;
    return 0;
}