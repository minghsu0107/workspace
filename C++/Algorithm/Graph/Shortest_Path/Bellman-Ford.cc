/*一共執行|V|−1次迴圈。
在每一次迴圈裡，對「所有的edge」進行Relax()。
經過|V|−1 次的「所有edge之Relax()」後，
必定能夠產生「按照最短路徑上之edge順序的Relax()順序」，也就能夠得到最短路徑。
(convergence propertity)
由於從起點走到任一vertex之最短路徑，最多只會有|V|−1條edge，因此，執行|V|−1
次迴圈必定能夠滿足「最壞情況」(worst case)。
若重複|V|-1 次後仍然有邊可鬆弛則代表圖上有負環
*/
// no negative cycle, negative weight and positive cycle is fine
#include <iostream>
#include <vector>
#include <list>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()

const int Max_Distance = 100;
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int>>> AdjList;
    std::vector<int> predecessor, distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);

    void FindPath(int x);
    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // 對edge(X,Y)進行Relax
    bool BellmanFord(int Start = 0);            // 以Start作為起點
                                                // if there is negative cycle, return false
};

bool Graph_SP::BellmanFord(int Start){

    InitializeSingleSource(Start);
    // 從起點走到任一vertex之最短路徑，最多只會有|V|−1條edge
    // 因此，執行|V|−1次迴圈必定能夠滿足「最壞情況」(worst case)
    for (int i = 0; i < num_vertex-1; i++) {                // |V-1|次的iteration
        // for each edge belonging to E(G)
        for (int j = 0 ; j < num_vertex; j++) {             // 把AdjList最外層的vector走一遍
            for (std::list<std::pair<int,int> >::iterator itr = AdjList[j].begin();
                 itr != AdjList[j].end(); itr++) {          // 各個vector中, 所有edge走一遍
                Relax(j, (*itr).first, (*itr).second);
            }
        }
    }

    // check if there is negative cycle
    // check every edge
    for (int i = 0; i < num_vertex; i++) {
        for (std::list<std::pair<int,int> >::iterator itr = AdjList[i].begin();
             itr != AdjList[i].end(); itr++) {
            if (distance[(*itr).first] > distance[i]+(*itr).second) {   // i是from, *itr是to
                return false;
            }
        }
    }

    // print predecessor[] & distance[]
    std::cout << "predecessor[]:\n";
    PrintDataArray(predecessor);
    std::cout << "distance[]:\n";
    PrintDataArray(distance);

    return true;
}
void Graph_SP::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl << std::endl;
}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){
    AdjList[from].push_back(std::make_pair(to,weight));
}
void Graph_SP::FindPath(int x) {
	if (x == -1) return;
    FindPath(predecessor[x]);
    std::cout << x << " ";
}
int main(){

    Graph_SP g7(6);
    g7.AddEdge(0, 1, 5);
    g7.AddEdge(1, 4, -4);g7.AddEdge(1, 2, 6);
    g7.AddEdge(2, 4, -3);g7.AddEdge(2, 5, -2);
    g7.AddEdge(3, 2, 4);
    g7.AddEdge(4, 3, 1);g7.AddEdge(4, 5, 6);
    g7.AddEdge(5, 0, 3);g7.AddEdge(5, 1, 7);

    if (g7.BellmanFord(0))
        std::cout << "There is no negative cycle.\n";
    else
        std::cout << "There is negative cycle.\n";
    
    g7.FindPath(2);
    return 0;
}
// Single-source
// O(V * E), for full graph E = V(V-1)/2, so O(E) = O(V^2)
