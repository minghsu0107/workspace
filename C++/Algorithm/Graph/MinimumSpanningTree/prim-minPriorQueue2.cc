// no negative edge
#include <bits/stdc++.h>
using namespace std;
static const int maxDistance = 100;

class Graph_MST{
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int> > > AdjList;
    std::vector<int> predecessor, distance;  // distance[i]: the cost of reaching i
    std::vector<bool> visited;
    void InitializeSingleSource(int Start);       // 以Start作為起點
    void PrintDataArray(std::vector<int> array);
    struct cmp {
        bool operator() (std::pair<int, int> a, std::pair<int, int> b) {
            return (a.second > b.second);

        }
    };
public:
    Graph_MST():num_vertex(0){};
    Graph_MST(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void Prim_MinQueue(int Start);

    friend class BinaryHeap;
};

void Graph_MST::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = maxDistance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;      // 起點vertex的distance設為0, ExtractMin就會從起點開始
}

void Graph_MST::Prim_MinQueue(int Start){

    InitializeSingleSource(Start);
    
    std::priority_queue <std::pair<int, int>, 
    std::vector<pair<int, int> >, cmp> minQueue;
    // minQueue is a set of unchosen vertice

    visited.resize(num_vertex, false);    // initializa visited[] as {0,0,0,...,0}
    
    minQueue.emplace(Start, distance[Start]);

    while (!minQueue.empty()) {
        int u = minQueue.top().first; // get the light edge
        minQueue.pop();
        visited[u] = true;
        for (std::list<std::pair<int, int> >::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {
            if (visited[(*itr).first] == false && (*itr).second < distance[(*itr).first]) {

                // for edge(X,Y)
                // u: X , (*itr).first: Y, (*itr).second: weight(X,Y)
                // (*itr).second < distance[(*itr).first]: weight(X,Y) < distance[Y]

                distance[(*itr).first] = (*itr).second;
                predecessor[(*itr).first] = u;
                minQueue.emplace((*itr).first, distance[(*itr).first]);
            }
        }
    }
    ///////   print result   /////////

    cout << "print predecessor[]:\n";
    PrintDataArray(predecessor);
    cout << "print distance[]:\n";
    PrintDataArray(distance);

    cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    int i = (Start+1)%num_vertex;   // 若從4開始, i依序為5,6,0,1,2,3
    while (i != Start) {
        cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
        << " : " << std::setw(3) << distance[i] <<"\n";
        i = (++i)%num_vertex;       // 到了6之後, 6+1 = 7, error:bad_access
    }
}
void Graph_MST::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++){
        cout << std::setw(4) << i;
    }
    std::cout << endl;
    for (int i = 0; i < num_vertex; i++){
        cout << std::setw(4) << array[i];
    }
    cout << endl << endl;
}
void Graph_MST::AddEdge(int from, int to, int weight){

    AdjList[from].emplace_back(to, weight);
}

int main(){

    Graph_MST g6(7);

    g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
    g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
    g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
    g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
    g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
    g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
    g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);

    cout << "MST found by Prim_MinQueue:\n";
    g6.Prim_MinQueue(2);

    return 0;
}
/* complexity = O((E + V)logV), E >> V -> O(ElogV)
   1.extract min (logV) for V times (since there are V vertice) -> O(VlogV)
   2.decrease key (logV) for every edge -> O(2ElogV) = O(ElogV) (since undirected)
*/
