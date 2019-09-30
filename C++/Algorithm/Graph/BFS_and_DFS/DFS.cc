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
        *discover,
        *finish;
public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
    void printTable();
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
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
        if (color[*itr] = 1) {
            // a circle exists
        }
    }
    color[vertex] = 2;                         // 當vertex已經搜尋過所有與之相連的vertex後, 將其塗黑
    finish[vertex] = ++time;                   // 並更新finish時間
}
void Graph::printTable() {
    std::cout << "predecessor:" << std::endl;         // 印出 A(0) ~ H(7)的predecessor
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << predecessor[i];
    }
    std::cout << "\ndiscover time:" << std::endl;  // 印出 A(0) ~ H(7)的discover time
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << discover[i];
    }
    std::cout << "\nfinish time:" << std::endl;    // 印出 A(0) ~ H(7)的finish time
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++){
        std::cout << std::setw(4) << finish[i];
    }
}

int main(){
    // 定義一個具有八個vertex的Graph
    Graph g2(8);
    // 建立如圖三之Graph
    g2.AddEdgeList(0, 1);g2.AddEdgeList(0, 2); 
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);g2.AddEdgeList(3, 5);
    // AdjList[4] is empty
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS(0);    // 以vertex(0), 也就是vertex(A作為DFS()的起點
    g2.printTable();
    return 0;
}
/*
根據時間軸，可以直接由discover與finish觀察出各個vertex之間的「ancestor-descendant」關係
(也就包含了predecessor關係)

若兩個vertex的「搜尋生命週期」完全沒有重疊
1.有可能在同一棵Depth-First Tree，但是互相沒有「ancestor-descendant」的關係
2.也有可能在不同棵Depth-First Tree