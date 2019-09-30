#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 1010
#define MAXM 100000
using namespace std;
struct Edge
{
    int from, to, next;
};
Edge edge[MAXM];
int head[MAXN], edgenum;
int vs[MAXN<<1];//第dfs_clock次DFS访问节点的编号
int depth[MAXN<<1];//第dfs_clock次DFS访问节点的深度
int id[MAXN];//id[i] 记录在vs数组里面 i节点第一次出现的dfs_clock下标
int dfs_clock;//时间戳
int N, M, Q;//点数 边数 查询数
int dp[MAXN<<1][20];
//dp[i][j]存储depth数组 以下标i开始的，长度为2^j的区间里 
// 最小值所对应的dfs_clock下标
void init()
{
    edgenum = 0;
    memset(head, -1, sizeof(head));
    // head[i] saves the edgenum of the edge whose from == ith node
    // we save the previous head[from] to E.next
    // and update head[from], so that we can get
    // a list of edge that is connected to from
}
void addEdge(int u, int v)
{

    Edge E = {u, v, head[u]};
    edge[edgenum] = E;
    head[u] = edgenum++;
}
void getMap()
{
    int a, b;
    while(M--)
        scanf("%d%d", &a, &b),
        addEdge(a, b), addEdge(b, a);
}
void DFS(int u, int fa, int d)//当前遍历点以及它的父节点  遍历点深度
{
    id[u] = dfs_clock;
    vs[dfs_clock] = u;
    depth[dfs_clock++] = d;
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == fa) continue;
        DFS(v, u, d+1);
        vs[dfs_clock] = u;//类似 回溯
        depth[dfs_clock++] = d;
    }
}
void find_depth()
{
    dfs_clock = 1;
    memset(vs, 0, sizeof(vs));
    memset(id, 0, sizeof(id));
    memset(depth, 0, sizeof(depth));
    DFS(1, -1, 0);//遍历
}
void RMQ_init(int NN)//预处理 区间最小值
{
    for(int i = 1; i <= NN; i++)
        dp[i][0] = i;
    for(int j = 1; (1<<j) <= NN; j++)
    {
        for(int i = 1; i + (1<<j) - 1 <= NN; i++)
        {
            int a = dp[i][j-1];
            int b = dp[i + (1<<(j-1))][j-1];
            if(depth[a] <= depth[b])
                dp[i][j] = a;
            else
                dp[i][j] = b;
        }
    }
}
int query(int L, int R)
{
    //查询L <= i <= R 里面使得depth[i]最小的值 返回对应下标
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    int a = dp[L][k];
    int b = dp[R - (1<<k) + 1][k];
    if(depth[a] <= depth[b])
        return a;
    else
        return b;
}
int LCA(int u, int v)
{
    int x = id[u];//比较大小 小的当作左区间 大的当作右区间
    int y = id[v];
    if(x > y)
        return vs[query(y, x)];
    else
        return vs[query(x, y)];
}
void solve()
{
    int a, b;
    while(Q--)
    {
        scanf("%d%d", &a, &b);
        printf("LCA(%d %d) = %d\n", a, b, LCA(a, b));
    }
}
int main()
{
    while(scanf("%d%d%d", &N, &M, &Q) != EOF)
    {
        init();
        getMap();
        find_depth();//DFS遍历整个树 求出所需要的信息
        RMQ_init(dfs_clock - 1);
        solve();
    }
    return 0;
}
/*
在线的rmq算法，叫做ST(Sparse Table)算法，采用动态规划的思想。
们用dp[i][j]表示从i开始，长度为2^j的数组长度内最小值的数组元素的下标。
如果我们要这个区间内的最小值，我们可以将其转化为
寻找dp[i][j-1]与dp[i+2^(j-1)-1][j-1]的最小值，
因为这两个区间刚好是上述区间的一半
查询的想法是找到两块空间，使其可以完全得覆盖L到R并且找到它们之间的最小值。
我们找了k=[log2(j-i+1)],中括号是取整的意思。

LCA问题可以经过DFS+st变成rmq（min）的解法，而且求解的时间复杂度规模是一样的
After DFS, 我们会访问到2n-1（加入树的节点个数为n的话）个节点
2n-1 == dfs_clock - 1
example:

结点访问顺序是: 1 2 3 2 4 5 4 6 4 2 1 7 8 7 1 //共2n-1个值

结点对应深度是: 0 1 2 1 2 3 2 3 2 1 0 1 2 1 0

如果查询结点3与结点6的公共祖先,则考虑在访问顺序中
3第一次出现，到6第一次出现的子序列: 3 2 4 5 4 6.
这显然是由结点3到结点6的一条路径.
在这条路径中，深度最小的就是最近公共祖先(LCA). 即结点2是3和6的LCA

于是问题转化为, 给定一个数组D,及两个数字i,j,如何找出
数组D中从i位置到j位置的最小值..
如上例,就是D[]={0,1,2,1,2,3,2,3,2,1,0,1,2,1,0}.
i=2;j=7
then solve it by RMQ