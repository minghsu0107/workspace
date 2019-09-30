// Spanning Tree為連結所有Graph中的vertex的樹
// 具有最小weight總和的樹，稱為Minimum Spanning Tree(MST)
// 因為是樹，若Graph有V個vertex，Spanning Tree只有|V|−1條edge
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>      // for setw()

struct Edge{
    int from, to, weight;
    Edge(){};
    Edge(int u, int v, int w):from(u), to(v), weight(w){};
};

class GraphMST{
private:
    int num_vertex;
    std::vector<std::vector<int>> AdjMatrix;
    struct WeightComp {
        bool operator() (Edge e1, Edge e2) {
            return (e1.weight < e2.weight);
        }
    };
public:
    GraphMST():num_vertex(0){};
    GraphMST(int n):num_vertex(n){
        AdjMatrix.resize(num_vertex);
        for (int i = 0; i < num_vertex; i++) {
            AdjMatrix[i].resize(num_vertex);
        }
    }
    void AddEdge(int from, int to, int weight);

    void KruskalMST();
    void GetSortedEdge(std::vector<struct Edge> &vec);
    friend int FindSetCollapsing(int *subset, int i);
    friend int Find(int *subset, int i);
    friend void UnionSet(int *subset, int x, int y);
};
int FindSetCollapsing(int *subset, int i){      // 用遞迴做collapsing

    int root;  // root
    for (root = i; subset[root] >= 0; root = subset[root]);

    while (i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}
void UnionSet(int *subset, int x, int y){

    int xroot = FindSetCollapsing(subset, x),
        yroot = FindSetCollapsing(subset, y);

    // 用rank比較, 負越多表示set越多element, 所以是值比較小的element比較多
    // xroot, yroot的subset[]一定都是負值
    if (subset[xroot] <= subset[yroot]) {        // x比較多element或是一樣多的時候, 以x作為root
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }
    else {    //  if (subset[xroot] > subset[yroot]), 表示y比較多element
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}
void GraphMST::GetSortedEdge(std::vector<Edge> &edgearray){

    for (int i = 0; i < num_vertex-1; i++) {
        for (int j = i+1; j < num_vertex; j++) {
            if (AdjMatrix[i][j] != 0) {
                edgearray.emplace_back(Edge(i,j,AdjMatrix[i][j]));
            }
        }
    }
    // 用std::sort 排序, 自己定義一個comparison
    std::sort(edgearray.begin(), edgearray.end(), WeightComp());
}
void GraphMST::KruskalMST(){

    Edge *edgesetMST = new Edge[num_vertex-1];
    int edgesetcount = 0;
    
    // initial: 把Graph中的每一個vertex都視為各自獨立且互斥的集合(disjoint set) 
    int subset[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        subset[i] = -1;
    }

    std::vector<Edge> increaseWeight;
    GetSortedEdge(increaseWeight);              // 得到排好序的edge的vec

    for (int i = 0; i < increaseWeight.size(); i++) {
        if (FindSetCollapsing(subset, increaseWeight[i].from) != FindSetCollapsing(subset, increaseWeight[i].to)) {
            edgesetMST[edgesetcount++] = increaseWeight[i];
            UnionSet(subset, increaseWeight[i].from, increaseWeight[i].to);
        }
    }
    // 以下僅僅是印出vertex與vertex之predecessor
    std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    for (int i = 0; i < num_vertex-1; i++) {
        std::cout << std::setw(3) << edgesetMST[i].from << " - " << std::setw(3) << edgesetMST[i].to 
                  << " : " << std::setw(4) << edgesetMST[i].weight << "\n";
    }
}
void GraphMST::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}

int main(){

    GraphMST g6(7);
    g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
    g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
    g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
    g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
    g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
    g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
    g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);

    std::cout << "MST found by Kruskal:\n";
    g6.KruskalMST();

    return 0;
}
/*
No negative edge
根據Corollary2，給定：

Graph G=(V,E) 是一個connected、weighted、undirected graph；
Set A是MST之edge的subset，A⊆E(MST)；
subgraph C=(VC,EC) 為「Forest GA=(V,A)」中的connected component，C可以視為一棵Tree；
edge(X,Y)是所有在「Forest GA=(V,A)」中，連結各個connected component的light edge；

那麼，edge(X,Y)對Set A也會是安全的(safe)
(since 根據Theorem1，若Cut (C1,V−C1)「respect」Set A，
 那麼Cut上的「crossing light edge」，一定也是MST的edge)
 
Kruskal's Algorithm按照「weight由小到大」的順序挑選edge，並且避免產生cycle，即可找到MST

orting of edges takes O(ELogE) time. 
After sorting, we iterate through all edges and apply find-union algorithm. 
The find and union operations can take atmost O(LogV) time. 


complexity = O(ElogE+Elogv), since E < V^2 -> logE < 2logV
so complexity = O(ElogV)
*/