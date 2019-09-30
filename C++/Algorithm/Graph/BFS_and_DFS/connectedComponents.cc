#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>      // for std::setw()

class Graph{
private:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    int *color,             // 0:white, 1:gray, 2:black
        *predecessor,
        *distance,          // for BFS()
        *discover,          // for DFS()
        *finish;
public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void BFS(int Start);    
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
    
    void CCDFS(int vertex);                // 利用DFS 
    void CCBFS(int vertex = 0);            // 利用BFS, 兩者邏輯完全相同
    void SetCollapsing(int vertex);
    void PrintPredecessor();               // 印出predecessor, 供驗証用, 非必要
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::BFS(int Start){

    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {  // 初始化，如圖二(b)
        color[i] = 0;                       // 0:白色;
        predecessor[i] = -1;                // -1表示沒有predecessor
        distance[i] = num_vertex+1;         // num_vertex個vertex, 
    }                                       // 最長距離 distance = num_vertex -1條edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++) {  // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
        if (color[i] == 0) {                // 第一次i會是起點vertex, 如圖二(c)
            color[i] = 1;                   // 1:灰色
            distance[i] = 0;                // 每一個connected component的起點之距離設成0
            predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u 為新的搜尋起點
                for (std::list<int>::iterator itr = AdjList[u].begin();        // for loop 太長
                     itr != AdjList[u].end(); itr++) {                         // 分成兩段
                    if (color[*itr] == 0) {                // 若被「找到」的vertex是白色
                        color[*itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        distance[*itr] = distance[u] + 1;  // 距離是predecessor之距離加一
                        predecessor[*itr] = u;             // 更新被「找到」的vertex的predecessor
                        q.push(*itr);                      // 把vertex推進queue
                    }
                }
                q.pop();        // 把u移出queue
                color[u] = 2;   // 並且把u塗成黑色
            }
        }
        // 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
        // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
        i = j;
    }
}
void Graph::DFS(int Start){
    color = new int[num_vertex];           // 配置記憶體位置
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    int time = 0;                          // 初始化, 如圖三(b)
    for (int i = 0; i < num_vertex; i++) { 
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++) { // 檢查所有Graph中的vertex都要被搜尋到
        if (color[i] == 0) {               // 若vertex不是白色, 則進行以該vertex作為起點之搜尋
            DFSVisit(i, time);
        }
        i = j;                             // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    }
}

void Graph::DFSVisit(int vertex, int &time){   // 一旦有vertex被發現而且是白色, 便進入DFSVisit()
    color[vertex] = 1;                         // 把vertex塗成灰色
    discover[vertex] = ++time;                 // 更新vertex的discover時間
    for (std::list<int>::iterator itr = AdjList[vertex].begin();   // for loop參數太長
         itr != AdjList[vertex].end(); itr++) {                    // 分成兩段
        if (color[*itr] == 0) {                // 若搜尋到白色的vertex
            predecessor[*itr] = vertex;        // 更新其predecessor
            DFSVisit(*itr, time);              // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
        }
    }
    color[vertex] = 2;                         // 當vertex已經搜尋過所有與之相連的vertex後, 將其塗黑
    finish[vertex] = ++time;                   // 並更新finish時間
}

void Graph::SetCollapsing(int current) {
    int root;  // root
    for (root = current; predecessor[root] >= 0; root = predecessor[root]);

    while (current != root) {
        int parent = predecessor[current];
        predecessor[current] = root;
        current = parent;
    }
}

void Graph::CCDFS(int vertex = 0){

    DFS(vertex);
    PrintPredecessor();
    for (int i = 0; i< num_vertex; i++){
        SetCollapsing(i);
    }
    PrintPredecessor();

    int num_cc = 0;
    for (int i = 0; i < num_vertex; i++) {
        if (predecessor[i] < 0) {
            std::cout << "Component#" << ++num_cc << ": " << i << " ";
            for (int j = 0; j < num_vertex; j++) {
                if (predecessor[j] == i) {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void Graph::CCBFS(int vertex){

    BFS(vertex);
    PrintPredecessor();
    for (int i = 0; i< num_vertex; i++){
        SetCollapsing(i);
    }
    PrintPredecessor();

    int num_cc = 0;
    for (int i = 0; i < num_vertex; i++) {
        if (predecessor[i] < 0) {
            std::cout << "Component#" << ++num_cc << ": " << i << " ";
            for (int j = 0; j < num_vertex; j++) {
                if (predecessor[j] == i) {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}
void Graph::PrintPredecessor(){
    std::cout << "predecessor:" << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << predecessor[i];
    std::cout << std::endl;
}

int main(){
    Graph g3(9);
    g3.AddEdgeList(0, 1);
    g3.AddEdgeList(1, 0);g3.AddEdgeList(1, 4);g3.AddEdgeList(1, 5);
    // AdjList[2] empty
    g3.AddEdgeList(3, 6);
    g3.AddEdgeList(4, 1);g3.AddEdgeList(4, 5);
    g3.AddEdgeList(5, 1);g3.AddEdgeList(5, 4);g3.AddEdgeList(5, 7);
    g3.AddEdgeList(6, 3);g3.AddEdgeList(6, 8);
    g3.AddEdgeList(7, 5);
    g3.AddEdgeList(8, 6);

    g3.CCDFS();
    std::cout << std::endl;
    g3.CCBFS();
    std::cout << std::endl;

    return 0;
}
