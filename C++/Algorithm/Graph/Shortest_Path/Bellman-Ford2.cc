#include <bits/stdc++.h>
using namespace std;

struct edge { 
	int u , v , w; 
};
vector< edge > E;
bool BellmanFord(int start, int *dis, int *parent, int N) {
	for (int i = 0; i < N; i++) {
        dis[i] = 1e9;
        parent[i] = -1;
    }
    dis[start] = 0;
	for (int i = 1; i < N; ++i) {
		for ( edge ed : E ) {
            if (dis[ed.u] + ed.w < dis[ed.v]) {
               dis[ed.v] = dis[ed.u] + ed.w;
               parent[ed.v] = ed.u; 
            }
		}
	}
    // check whether there is a negative cycle
    for ( edge ed : E ) {
        // there is still edge that can be relaxed
        // meaning that there exists negative cycle
        if (dis[ed.u] + ed.w < dis[ed.v]) {
           return false; 
        }
    }
    return true;
}

void AddEdge(int u, int v, int w) {
	E.push_back( (edge){u, v, w} );
}

void FindPath(int x, int *parent) {
	if (x == -1) return;
    FindPath(parent[x], parent);
    cout << x << " ";
}

int main() {
	int N = 6;
	int *dis = new int[N];
	int *parent = new int[N];

	AddEdge(0, 1, 5);
    AddEdge(1, 4, -4); AddEdge(1, 2, 6);
    AddEdge(2, 4, -3); AddEdge(2, 5, -2);
    AddEdge(3, 2, 4);
    AddEdge(4, 3, 1); AddEdge(4, 5, 6);
    AddEdge(5, 0, 3); AddEdge(5, 1, 7);

    int suc = BellmanFord(0, dis, parent, N);
    
    if (suc) {
        std::cout << "distance[]:\n";
        for (int i = 0; i < N; i++)
            std::cout << std::setw(4) << dis[i];
        std::cout << std::endl;
        std::cout << "predecessor[]:\n";
        for (int i = 0; i < N; i++)
            std::cout << std::setw(4) << parent[i];
        std::cout << std::endl;
        FindPath(2, parent);
        std::cout << std::endl;
    }
    else
        std::cout << "negative cycle exists" << std::endl;
    return 0;
}