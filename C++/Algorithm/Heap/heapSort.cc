#include <iostream>
#include <vector>

void swap(int &p1, int &p2){
    int temp = p1;
    p1 = p2;
    p2 = temp;
}

void MaxHeapify(std::vector<int> &array, int root, int length){

    int left = 2*root,      // 取得left child
    right = 2*root + 1,     // 取得right child
    largest;                // largest用來記錄包含root與child, 三者之中Key最大的node

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root) {                         // 如果目前root的Key不是三者中的最大
        swap(array[largest], array[root]);         // 就調換root與三者中Key最大的node之位置
        MaxHeapify(array, largest, length);        // 調整新的subtree成Max Heap
    }
}

void BuildMaxHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        MaxHeapify(array, i, (int)array.size() - 1);     // length要減一, 因為heap從1開始存放資料
    }
}

void HeapSort(std::vector<int> &array){

    array.insert(array.begin(), 0);                     // 將index(0)閒置

    BuildMaxHeap(array);                                // 將array調整成Max Heap

    int size = (int)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (int i = (int)array.size() -1; i >= 2; i--) {
        swap(array[1], array[i]);                       // 將最大值放到array的最後一個位置
        size--;
        MaxHeapify(array, 1, size);                     // 調整「忽略最後一個位置」的矩陣
    }

    array.erase(array.begin());                         // 將index(0)刪除
}

void PrintArray(std::vector<int> &array){
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {

    int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};
    std::vector<int> v(arr, arr+sizeof(arr)/sizeof(int));

    std::cout << "original:\n";
    PrintArray(v);

    HeapSort(v);

    std::cout << "sorted:\n";
    PrintArray(v);

    return 0;
}
