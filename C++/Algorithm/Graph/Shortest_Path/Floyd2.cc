#include <bits/stdc++.h>
#define N 16
#define max_dis 1e9
using namespace std;


int dis[N][N], parent[N][N];
// // parent[i][j] = k: for sp from i to j, the parent of j is k
void AddEdge(int from, int to, int w) {
	dis[from][to] = w;
}

void find_path(int from, int to) {
    if (dis[from][to] == max_dis) {
        cout << "there is no path" << endl;
        return;
    }
    if (from == to) {
        cout << from << " ";
        return;
    }
    find_path(from, parent[from][to]);
    cout << to << " ";
}
int main() {
	int n = 6;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = max_dis;
            parent[i][j] = -1;
        }
    }

	AddEdge(0, 1, 5);
    AddEdge(1, 4, -4); AddEdge(1, 2, 6);
    AddEdge(2, 4, -3); AddEdge(2, 5, -2);
    AddEdge(3, 2, 4);
    AddEdge(4, 3, 1); AddEdge(4, 5, 6);
    AddEdge(5, 0, 3); AddEdge(5, 1, 7);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dis[i][j] != 0 && dis[i][j] != max_dis)
                parent[i][j] = i;
        }
    }
    /* dynamic programming
       when k >= 0
       dis[i][j] (considering v(0) ~ v(k) as middle points)
       = min(dis[i][j] (considering v(0) ~ v(k-1) as middle points), 
             dis[i][k] + dis[k][j] (considering v(0) ~ v(k-1) as middile points))
       initialize(if k-1 < 0)
       dis[i][j] = weight[i][j]
    */
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dis[i][k] != max_dis && dis[i][j] > dis[i][k] + dis[k][j]) {
                   dis[i][j] = dis[i][k] + dis[k][j];
                   parent[i][j] = parent[k][j];
                }
            }
        }
    }

    cout << "distance[]:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << std::setw(4) << dis[i][j];
        cout << endl;
    }
    cout << "parent[]:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << std::setw(4) << parent[i][j];
        cout << endl;
    }

    find_path(0, 2);
}