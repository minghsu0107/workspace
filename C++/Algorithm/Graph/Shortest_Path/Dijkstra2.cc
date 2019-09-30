#include <bits/stdc++.h>
#define N 16
using namespace std;

typedef pair<int, int> ii;
vector<ii> v[N];
bool vis[N];
int dis[N];

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
    	dis[i] = 1e9;
    dis[start] = 0;
    int p = start;
    
    while(true) {
    	vis[p] = true;
    	for (ii x: v[p]) {
    		if (!vis[x.first]) {
    			int q = x.first, w = x.second;
    			dis[q] = min(dis[q], dis[p] + w);
    		}
    	}
    	int next = -1;
    	for (int i = 0; i < n; i++) {
    		if (!vis[i]) {
    			if (next == -1 || dis[i] < dis[next]) next = i;
    		}
    	}
    	if (next == -1) break;
    	p = next;
    }

    std::cout << "distance[]:\n";
    for (int i = 0; i < n; i++)
        std::cout << std::setw(4) << dis[i];
    std::cout << std::endl;
}
// O(E + V^2)