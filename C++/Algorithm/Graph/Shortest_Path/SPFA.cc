#include <bits/stdc++.h>
#define N 16
#define INF 0x3f3f3f3f 
using namespace std;

typedef pair<int, int> ii;
vector<ii> v[N];
bool isIn[N];
int dis[N], cnt[N];

void AddEdge(int from, int to, int w) {
	v[from].push_back(make_pair(to, w));
}

int main() {
    int n = 3, start = 0;
/*
	  AddEdge(0, 1, 8); AddEdge(0, 5, 1);
	  AddEdge(1, 0, 3); AddEdge(1, 2, 1);
	  AddEdge(3, 1, 4); AddEdge(3, 2, 6); AddEdge(3, 4, 7); AddEdge(3, 5, 3);
	  AddEdge(5, 3, 2); AddEdge(5, 4, 8);
*/
    AddEdge(0, 1, -1); AddEdge(1, 2, -1); AddEdge(2, 0, -1);
    memset(isIn, false, sizeof(isIn));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
        dis[i] = INF;
    dis[start] = 0;

    list <int> qq;
    qq.push_back(start);
    while (!qq.empty()) {
    	  int p = qq.front();
        qq.pop_front();
        isIn[p] = false;
      	for (ii x: v[p]) {
            int q = x.first, w = x.second;
        		if (dis[q] > dis[p] + w) {               
                dis[q] = dis[p] + w;
                if (!isIn[q]) {
                   if (++cnt[q] >= n) { // max update time = n - 1
                      cout << "negative cycle" << endl;
                      return 0;
                   }
                   isIn[q] = true;
                   // optimize: small label first(SLF)
                   if (dis[q] < dis[qq.front()]) qq.push_front(q);
                   else qq.push_back(q);
                }
        		}
      	}
    }

    cout << "distance[]:\n";
    for (int i = 0; i < n; i++)
        cout << std::setw(4) << dis[i];
    cout << endl;
    return 0;
}
// idea is just like BellmanFord, but SPFA only considers
// the vertice whose distances have been updated (save in queue)
// if a vertex goes into queue >= n times,
// then there is a negative cycle (we can use an array for counting)
// when the graph is sparse, use SPFA
// when the graph is dense, use dijkstra(with heap)
// 負環的比較：BellmanFord偵測到的負環為整個Graph的，SPFA偵測到的負環為從start出發會走的到的