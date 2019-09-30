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

    int GetColor(int i){return color[i];};              // 取得private data: color
    int GetFinish(int i){return finish[i];};            // 取得private data: finish
    int GetPredecessor(int i){return predecessor[i];};  // 取得private data: predecessor

    void AddEdgeList(int from, int to);

    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
    void VariableInitializeDFS();     // 對DFS()需要的資料：color, discover, finish, predecessor
                                      // 進行「配置記憶體」與「初始化」

    void SetCollapsing(int vertex);
    void PrintDataArray(int *array);  // 列印出array[]
    void PrintFinish();               // 列印出 finish[]
    void PrintPredecessor();          // 列印出 predecessor[]

    Graph GraphTranspose();           // 產生Transpose of Graph
    void PrintSCCs(int Start = 0);    // 吃一個int, 表示起點vertex, 若沒給就從0開始

    // 利用QuickSort()得到 finish[] 由大致小的vertex順序
    friend void QuickSort(int *vec, int front, int end, int *vec2);
    friend int Partition(int *vec, int front, int end, int *vec2);
    friend void swap(int *x, int *y);
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

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int Partition(int *vec, int front, int end, int *vec2){
    int pivot = vec[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (vec[j] > pivot) {
            i++;
            swap(&vec[i], &vec[j]);
            swap(&vec2[i], &vec2[j]);
        }
    }
    swap(&vec[i + 1], &vec[end]);
    swap(&vec2[i + 1], &vec2[end]);

    return i + 1;   // 把 i + 1 當成下一個 recurrsive call 的 中間斷點
}
void QuickSort(int *vec, int front, int end, int *vec2){
    if (front < end) {
        int pivot = Partition(vec, front, end, vec2);
        QuickSort(vec, front, pivot - 1, vec2);
        QuickSort(vec, pivot + 1, end, vec2);
    }
}

void Graph::PrintSCCs(int Start){
    // 第一次DFS(), 目的是取得finish[]
    DFS(Start);

    // 顯示 第一次DFS()後的finish[]
    std::cout << "First DFS() on G, finish time:" << std::endl;
    PrintFinish();

    // gT代表Transpose of Graph
    Graph gT(num_vertex);
    gT = GraphTranspose();

    // 矩陣 finishLargetoSmall[] 用來儲存 finish[] 由大至小的vertex順序
    int finishLargetoSmall[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        finishLargetoSmall[i] = i;
    }
    // QuickSort()會更新 finishLargetoSmall[] 成 finish[] 由大至小的vertex順序
    QuickSort(finish, 0, num_vertex-1, finishLargetoSmall);

    // 列印出 finish[] 由大至小的vertex順序
    std::cout << "finish time Large to Small:" << std::endl;
    PrintDataArray(finishLargetoSmall);

    // 第二次DFS(), 執行在gT上, 先對四個資料「配置記憶體」且「初始化」
    gT.VariableInitializeDFS();
    int time = 0;
    for (int i = 0; i < num_vertex; i++){
        if (gT.GetColor(finishLargetoSmall[i]) == 0) {
            gT.DFSVisit(finishLargetoSmall[i], time);
        }
    }

    // 顯示 第二次DFS()後的finish[]
    std::cout << "Second DFS() on gT, finish time:\n";
    gT.PrintFinish();
    // 顯示 第二次DFS()後的predecessor[]
    std::cout << "predecessor[] before SetCollapsing:\n";
    gT.PrintPredecessor();

    for (int i = 0; i< num_vertex; i++)
        gT.SetCollapsing(i);

    // 顯示 SetCollapsing後的predecessor[]
    std::cout << "predecessor after SetCollapsing:\n";
    gT.PrintPredecessor();

    // 如同在undirected graph中尋找connected component
    int num_cc = 0;
    for (int i = 0; i < num_vertex; i++) {
        if (gT.GetPredecessor(i) < 0) {
            std::cout << "SCC#" << ++num_cc << ": " << i << " ";
            for (int j = 0; j < num_vertex; j++) {
                if (gT.GetPredecessor(j) == i) {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
void Graph::VariableInitializeDFS(){
    color = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
}
Graph Graph::GraphTranspose(){
    Graph gT(num_vertex);
    for (int i = 0; i < num_vertex; i++) {
        for (std::list<int>::iterator itr = AdjList[i].begin();itr != AdjList[i].end(); itr++) {
            gT.AddEdgeList(*itr, i);
        }
    }
    return gT;
}
void Graph::PrintDataArray(int *array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl;
}
void Graph::PrintFinish(){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << finish[i];
    std::cout << std::endl;
}
void Graph::PrintPredecessor(){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << predecessor[i];
    std::cout << std::endl;
}

int main(){
    Graph g4(9);
    g4.AddEdgeList(0, 1);
    g4.AddEdgeList(1, 2);g4.AddEdgeList(1, 4);
    g4.AddEdgeList(2, 0);g4.AddEdgeList(2, 3);g4.AddEdgeList(2, 5);
    g4.AddEdgeList(3, 2);
    g4.AddEdgeList(4, 5);g4.AddEdgeList(4, 6);
    g4.AddEdgeList(5, 4);g4.AddEdgeList(5, 6);g4.AddEdgeList(5, 7);
    g4.AddEdgeList(6, 7);
    g4.AddEdgeList(7, 8);
    g4.AddEdgeList(8, 6);

    std::cout << "Vertex(0) as starting point for the First DFS():\n\n";
    g4.PrintSCCs();
    std::cout << "Vertex(3) as starting point for the First DFS():\n\n";
    g4.PrintSCCs(3);

    return 0;
}
/*
每一個directed graph，只要「以SCC作為基本元素(vertex)」，都會有其相對應的component graph
component graph一定是directed acyclic graph(DAG)

若DFS()在每次尋找「新的搜尋起點時」，能夠按照「一條path上，從尾端至開頭」的vertex順序，
那麼Predecessor Subgraph就能長成「能夠分辨出SCC」的Depth-First Forest。

在DAG上執行一次DFS()，若存在一條path從vertex(X)到vertex(Y)
那麼finish[X]一定比finish[Y]還大
therefore, for C1->C2->C3 (C == Component Graph),
不論以哪個vertex作為起點，「finish的大小順序一定是C1、C2、C3」。

以「第一次DFS()所得到的finish之由大到小順序」選取起點，在GT上進行第二次DFS()，
就可以先選到C1，由於無法從C1走回C2，因此DFS()在搜尋完C1內的所有vertex後，
便形成自己的Depth-First Tree。接著再依序挑選C2、C3為起點進行搜尋，
並且建立起各自SCC的Depth-First Tree。
*/