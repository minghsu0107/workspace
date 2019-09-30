#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <cstring> 
#include <queue> 
#define MAXN 10000 
#define INF 0x3f3f3f3f 
using namespace std; 
typedef pair<int, int> P; 
int N, M, S, T, K; 
int dist[MAXN]; // saves h_score of every node(dist[v] = h_score from v to end)
int tdist[MAXN]; 
int cnt[MAXN]; 

bool f[MAXN];
bool vis[MAXN]; 
vector<P> Adj[MAXN]; 
vector<P> Rev[MAXN]; 
struct Edge { 
	int to, len; 
	Edge(){} 
	Edge(int t, int l):to(t), len(l){} 
}; 
priority_queue<Edge> q; 
// min heap, q.top = node with smallest f_score(g_score + h_score)
bool operator<(const Edge &a, const Edge &b) { 
	return (a.len + dist[a.to]) > (b.len + dist[b.to]); 
} 
void dijkstra() {
	memset(vis, false, sizeof(vis)); 
	memset(dist, 0, sizeof(dist)); 
	fill(tdist, tdist+MAXN, INF); 
	tdist[T] = 0; 
	while(!q.empty()) q.pop(); 
	q.push(Edge(T, 0)); 
	while (!q.empty()) { 
		int x = q.top().to; 
		int d = q.top().len; 
		q.pop(); 
		if (vis[x]) continue;
        vis[x] = true;

		if (tdist[x] < d) continue; 
		for (int i = 0; i < Rev[x].size(); i++) { 
			int y = Rev[x][i].first; int len = Rev[x][i].second; 
			if (d + len < tdist[y]) { 
				tdist[y] = d + len; 
				q.push(Edge(y, tdist[y])); 
			} 
		} 
	} 
	for (int i = 1; i <= N; i++){ 
		dist[i] = tdist[i]; 
	} 
} 
int aStar() { 
	if (dist[S] == INF) return -1; 
	while (!q.empty()) q.pop(); 
	q.push(Edge(S, 0)); 
	memset(cnt, 0, sizeof(cnt)); 
	while (!q.empty()) { 
		int x = q.top().to; 
		int d = q.top().len; //d = g_score of x(actual dis from start to x)
		q.pop(); 
		cnt[x]++; 
		if (cnt[T] == K) return d; 
		if (cnt[x] > K) continue; 
		for (int i = 0; i < Adj[x].size(); i++) { 
			int y = Adj[x][i].first; 
			int len = Adj[x][i].second; 
			// d+len is new g_score
			q.push(Edge(y, d+len)); 
		} 
	} 
	return -1; 
} 
int main() { 
	std::ios::sync_with_stdio(false); 
	int a, b, t; 
	cin >> N >> M; 
	for (int i = 0; i < M; i++) { 
		cin >> a >> b >> t; 
		Adj[a].push_back(make_pair(b, t)); 
		Rev[b].push_back(make_pair(a, t)); 
	} 
	cin >> S >> T >> K; 
	//本题需要特别注意的地方，S==T时，也得走出去转一圈
	if (S == T) K++; 
	dijkstra(); 
	cout << aStar() << endl; 
	return 0; 
}