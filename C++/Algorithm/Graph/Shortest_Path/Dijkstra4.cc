// solving the problem that priority_queue does not have decrease_key
#include <bits/stdc++.h>
#define N 16
#define INF 0x3f3f3f3f 
using namespace std;

typedef pair<int, int> ii;
vector<ii> v[N];
bool vis[N];
int dis[N];

struct cmp {
    bool operator() (ii a, ii b) {
        return (a.second < b.second);

    }
};

void AddEdge(int from, int to, int w) {
	v[from].push_back(make_pair(to, w));
}

int main() {
	int n = 6, start = 0;
	AddEdge(0, 1, 8); AddEdge(0, 5, 1);
	AddEdge(1, 0, 3); AddEdge(1, 2, 1);
	AddEdge(3, 1, 4); AddEdge(3, 2, 6); AddEdge(3, 4, 7); AddEdge(3, 5, 3);
	AddEdge(5, 3, 2); AddEdge(5, 4, 8);

    memset(vis, false, sizeof vis);
    for (int i = 0; i < n; i++)
    	dis[i] = INF;
    dis[start] = 0;
    set <ii, cmp> pq;
    pq.insert((ii){start, dis[start]}); 
    
    while (!pq.empty()) {
    	int p = pq.begin()->first;
        pq.erase(pq.begin());
        vis[p] = true;
    	for (ii x: v[p]) {
            int q = x.first, w = x.second;
    		if (!vis[q] && dis[q] > dis[p] + w) {
                if (dis[q] != INF) 
                    pq.erase(pq.find(make_pair(q, dis[q]))); 
                dis[q] = dis[p] + w;
                pq.emplace(q, dis[q]);
    		}
    	}
    }

    cout << "distance[]:\n";
    for (int i = 0; i < n; i++)
        cout << std::setw(4) << dis[i];
    cout << endl;
}
// complexity = O((E + V)logV), E >> v -> O(ElogV)