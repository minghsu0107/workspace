#include<queue>
#include<cstdio>
#include<cstring>
#define N 5001
#define M 100001
#define INF 1e9
using namespace std;
int front[N], to[M<<1], nxt[M<<1], val[M<<1], from[M<<1], tot, n, m;
int dis1[N], dis2[N];
bool vis[N];
queue<int> q;
void add(int u,int v,int w) {
    to[++tot] = v; nxt[tot] = front[u]; 
    front[u] = tot; val[tot] = w; from[tot] = u;

    to[++tot] = u; nxt[tot] = front[v]; 
    front[v] = tot; val[tot] = w; from[tot] = v;
}
void spfa(int s, int *dis) {
    memset(vis,false,sizeof(vis));
    q.push(s);
    vis[s]=true;
    dis[s]=0;

    while(!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now]=false;
        for(int i = front[now]; i; i = nxt[i]) {
            if (dis[to[i]] > dis[now] + val[i]) {
                dis[to[i]] = dis[now] + val[i];
                if (!vis[to[i]]) {
                    vis[to[i]] = true;
                    q.push(to[i]);
                }
            }
        }
    }
}
void init() {
    for (int i = 1; i <= n; ++i) {
        dis1[i] = INF;
        dis2[i] = INF;
    }
}
void getSecShortest() {
    int minn=dis1[n], tmp, ans=0x7fffffff;
    for (int i = 1; i <= tot; ++i) {
        int u = from[i], v = to[i];
        tmp = dis1[u] + val[i] + dis2[v];
        if(tmp > minn && tmp < ans) ans = tmp;
    }
    printf("%d", ans);
}
int main() {
    scanf("%d%d",&n, &m);
    int u, v, w;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    init();
    spfa(1, dis1);
    spfa(n, dis2);
    getSecShortest();
}
/*
次短路一定是由最短路上出去经过其他的边在回到最短路上
所以先求出每个点到1的最短路dis1，每个点到n的最短路dis2
枚举每一条边
那么经过这条边u-->v的最短路为dis1[u]+w+dis2[v]
如果它大于最短路，更新答案
*/