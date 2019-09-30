/*
所謂的Topological Sort(拓撲排序)要求，
若directed acyclic graph(DAG)中存在一條edge(X,Y)，
那麼序列中，vertex(X)一定要在vertex(Y)之前出現

只有directed acyclic graph(DAG)的Topological Sort(拓撲排序)才有意義。
在DAG上執行一次DFS()，若存在一條path從vertex(X)到vertex(Y)
那麼finish[X]一定比finish[Y]還大
因此只要進行一次DFS()，並且依照finish[]由大到小印出vertex，就是Topological Sort(拓撲排序)了
*/
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>
#include <stack>
#include <algorithm>
#include <iomanip>      // for setw()

class Graph{
private:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    int *color,             // 0:white, 1:gray, 2:black
        *distance,
        *predecessor,
        *discover,
        *finish;
    std::stack<int> s;
    // sort from larger finish time to smaller finish time 
    struct cmp {
    	bool operator() (std::pair<int, int> a, std::pair<int, int> b) { 
    		return a.first > b.first; 
    	}
    };

public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };

    void AddEdgeList(int from, int to);

    void DFS(int Start);
    void DFSVisit(int vertex, int &time);

    void TopologicalSort(int Start = 0);
    void TopologicalSort2(int Start = 0);
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
    s.push(vertex);
}
void Graph::TopologicalSort(int Start){

    DFS(Start);         // 進行一次DFS用來取得 finish[]

    std::vector<std::pair<int, int> > v;
    for (int i = 0; i < num_vertex; i++) {
        v.emplace_back(finish[i], i);
    }
    
    sort(v.begin(), v.end(), cmp());

    std::cout << "Topological Sort:\n";
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(3) << v[i].second;
    std::cout << std::endl;
}
void Graph::TopologicalSort2(int Start){

    DFS(Start);         // 進行一次DFS用來取得 finish[]


    std::cout << "Topological Sort:\n";
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(3) << s.top();
        s.pop();
    }
    std::cout << std::endl;
}
int main(){
    Graph g5(15);            // 建立如圖二(a)的DAG
    g5.AddEdgeList(0, 2);
    g5.AddEdgeList(1, 2);
    g5.AddEdgeList(2, 6);g5.AddEdgeList(2, 7);
    g5.AddEdgeList(3, 4);
    g5.AddEdgeList(4, 5);
    g5.AddEdgeList(5, 6);g5.AddEdgeList(5, 14);
    g5.AddEdgeList(6, 8);g5.AddEdgeList(6, 9);g5.AddEdgeList(6, 11);g5.AddEdgeList(6, 12);
    g5.AddEdgeList(7, 8);
    g5.AddEdgeList(9, 10);
    g5.AddEdgeList(12, 13);

    g5.TopologicalSort();
    g5.TopologicalSort2();
    g5.TopologicalSort(4);
    g5.TopologicalSort2(4);

    return 0;
}
/* solution2: modify dfs()
1.
把剛剛塗黑的vertex放進stack中，那麼按照順序，最先被塗黑的vertex就最先被放入stack的vertex，也就最後被pop()出stack。
因此，對stack依序進行pop()便能夠維持finish由大到小的順序

2.
或者，把剛剛塗黑的vertex推進(push)一串Linked list，那麼，只要每次都是在Linked list的前端(front)加入vertex，當有下一個vertex被推入Linked list時，先前finish較小的vertex就被往後挪。
最後，對Linked list進行一次traversal，得到的vertex順序就會是finish由大到小
*/
