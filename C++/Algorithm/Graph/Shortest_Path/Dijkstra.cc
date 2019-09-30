// no negative weight, cycle is fine

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()
#include <map>
#include <cmath>
struct HeapNode {
    int key, element;
    HeapNode():key(0),element(0){};
    HeapNode(int key, int element):key(key),element(element){};
};
class BinaryHeap{
private:
    std::vector<HeapNode> heap;
    std::map<int, int> mp;
    void swap(struct HeapNode &p1, struct HeapNode &p2);
    int GetParentNode(int node){return std::floor(node/2);};
public:
    BinaryHeap(){heap.resize(1);};
    BinaryHeap(int n){
        heap.resize(n + 1);          // 主要存放vertex及其distance的vector
    }
    // Min-Priority Queue
    void MinHeapify(int node, int length);
    void BuildMinHeap(std::vector<int> array);
    void DecreaseKey(int node, int newKey);
    void MinHeapInsert(int node, int key);
    int ExtractMin();                               // 回傳heap[1]並調整Heap
    int Minimum(){return heap[1].element;};         // 回傳heap[1]

    bool IsHeapEmpty(){return (heap.size()<=1);};

};
void BinaryHeap::MinHeapInsert(int node, int key){

    heap.emplace_back(HeapNode(node,key));
    mp[node] = heap.size() - 1;
    DecreaseKey(node, key);
}
void BinaryHeap::DecreaseKey(int node, int newKey){

    int index_node = mp[node];      // 找到node所在的位置index

    if (newKey >= heap[index_node].key) {      // 如果不是把node的Key下修, 便終止此函式
        //std::cout << "new key is not smaller than current key\n";
        return;
    }
    heap[index_node].key = newKey;            // 更新node之Key後,   
                                              // 需要檢查是否新的subtree滿足Min Heap
    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key) {
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
        mp[node] = index_node;
    }
}
void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2){

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}
int BinaryHeap::ExtractMin(){

    if (IsHeapEmpty()) {
        std::cout << "error: heap is empty\n";
        exit(-1);
    }
    int min = heap[1].element;    // 此時heap的第一個node具有最小key值
    // 便以min記錄其element, 最後回傳min
    // delete the first element/vertex
    heap[1] = heap[heap.size()-1];            // 把最後一個element放到第一個位置,
    heap.erase(heap.begin()+heap.size()-1);   // 再刪除最後一個element
    MinHeapify(1, (int)heap.size());          // 目前, heap[1]具有最大Key, 需要進行調整

    return min;       // 回傳heap中具有最小key的element
}
void BinaryHeap::BuildMinHeap(std::vector<int> array){

    // 將array[]的資料放進 heap之矩陣中, 並預留 heap[0] 不做使用
    for (int i = 0; i < array.size(); i++) {
        heap[i + 1].element = i;                 // 把array[]的idx視為element
        heap[i + 1].key = array[i];              // 把array[]的數值視為key
        mp[i] = i + 1;
    }
    for (int i = (int)heap.size()/2; i >= 1 ; i--) {
        MinHeapify(i, (int)heap.size()-1);     // length要減一, 因為heap從從1開始存放資料
    }
}
void BinaryHeap::MinHeapify(int node, int length){

    int left = 2*node,          // 取得left child
        right = 2*node + 1,     // 取得right child
        smallest;               // smallest用來記錄包含root與child, 三者之中Key最小的node

    if (left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != node) {                 // 如果目前node的Key不是三者中的最小
        swap(heap[smallest], heap[node]);   // 就調換node與三者中Key最小的node之位置
        MinHeapify(smallest, length);       // 調整新的subtree成Min Heap
    }
}

const int Max_Distance = 100;
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int>>> AdjList;
    std::vector<int> predecessor, distance;
    std::vector<bool> visited;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);
    void PrintIntArray(int *array);

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // edge方向：from X to Y

    void Dijkstra(int Start = 0);        // 需要Min-Priority Queue
    friend class BinaryHeap;             // 以Binary Heap實現Min-Priority Queue
};
void Graph_SP::Dijkstra(int Start){

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);   // object of min queue
    minQueue.BuildMinHeap(distance);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        for (std::list<std::pair<int, int>>::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {

            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
        }
    }
    std::cout << "\nprint predecessor:\n";
    PrintDataArray(predecessor);
    std::cout << "\nprint distance:\n";
    PrintDataArray(distance);
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
void Graph_SP::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl;
}
int main(){

    Graph_SP g9(6);
    g9.AddEdge(0, 1, 8);g9.AddEdge(0, 5, 1);
    g9.AddEdge(1, 0, 3);g9.AddEdge(1, 2, 1);
    g9.AddEdge(2, 0, 5);g9.AddEdge(2, 3, 2);g9.AddEdge(2, 4, 2);
    g9.AddEdge(3, 1, 4);g9.AddEdge(3, 2, 6);g9.AddEdge(3, 4, 7);g9.AddEdge(3, 5, 3);
    g9.AddEdge(5, 3, 2);g9.AddEdge(5, 4, 8);

    g9.Dijkstra(0);

    return 0;
}
// Single-source