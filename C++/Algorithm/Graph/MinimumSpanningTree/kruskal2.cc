#include <bits/stdc++.h>
using namespace std;

const int MAX = 16;
int n, p[MAX];
struct edge {
	int u, v, w;
};
struct cmp {
	bool operator() (edge& i, edge& j) {
		return i.w < j.w;
	}
};
vector <edge> E, MST;
void AddEdge(int from, int to, int weight) {
    E.push_back( (edge){from, to, weight} ); 
}
int find(int x) { return p[x] == x ? x: p[x] = find(p[x]); }
void kruskal() {
	int ans = 0;
	for (int i = 0; i < n; i++) p[i] = i;
	sort(E.begin(), E.end(), cmp());
    for (auto& e: E) {
    	int x = find(e.u); int y = find(e.v);
    	if (x != y) {
           MST.push_back(e);
    	   p[x] = y;
    	}
    }
}
void printMST() {
	for (auto& e: MST)
		cout << e.u << " " << e.v << " " << e.w << endl;
}
int main() {
	n = 7;
    AddEdge(0, 1, 5); AddEdge(0, 5, 3);
    AddEdge(1, 0, 5); AddEdge(1, 2, 10); AddEdge(1, 4, 1); AddEdge(1, 6, 4);
    AddEdge(2, 1, 10); AddEdge(2, 3, 5); AddEdge(2, 6, 8);
    AddEdge(3, 2, 5); AddEdge(3, 4, 7); AddEdge(3, 6, 9);
    AddEdge(4, 1, 1); AddEdge(4, 3, 7); AddEdge(4, 5, 6); AddEdge(4, 6, 2);
    AddEdge(5, 0, 3); AddEdge(5, 4, 6);
    AddEdge(6, 1, 4); AddEdge(6, 2, 8); AddEdge(6, 3, 9); AddEdge(6, 4, 2);
    kruskal();
    printMST();
}