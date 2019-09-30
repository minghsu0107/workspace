#include <iostream> 
using namespace std; 

//arr2複製了*arr1的屬性 但arr1資源先被回收了
//而arr2的_array仍然參考至一個已被回收資源的位址 這時再存取該位址的資料就有危險
//SafeArray *arr1 = new SafeArray(10);
//SafeArray arr2 = *arr1;
//delete arr1;
//除了為物件始化撰寫複製建構函式之外 最好再重載=指定運算子 (=指定運算子預設也是將物件的屬性值一一複製過去)
//在遇到指標成員時，產生位址上的資源複本
class SafeArray { 
public: 
    // 複製建構函式 
    SafeArray(const SafeArray&);
    // 建構函式 
    SafeArray(int len);
    // 解構函式 
    ~SafeArray();
    //static int count=1; error: only const static成員可以在類別定義中初始化
    static int count;
    int size() const;
    int get(int); 
    void set(int, int);
    
    // 重載=運算子 
    SafeArray& operator=(const SafeArray&);

private:
    int _length; 
    int *_array; 

    bool isSafe(int i); 
};
// 複製建構函式 
SafeArray::SafeArray(const SafeArray &safeArray): _length(safeArray._length) {
    _array = new int[_length];
    
    for(int i = 0; i < _length; i++) {
        _array[i] = safeArray._array[i];
    }
}
// 重載=指定運算子 
SafeArray& SafeArray::operator=(const SafeArray &safeArray) {
    if(this != &safeArray) {
        _length = safeArray._length;

        // 先清除原有的資源 
        delete [] _array;
 
        _array = new int[_length];
        for(int i = 0; i < _length; i++) {
            _array[i] = safeArray._array[i];
        } 
    }
 
    return *this;
}
// 動態配置陣列
SafeArray::SafeArray(int len) : _length(len) {
    _array = new int[_length];
}

int SafeArray::count=1;

int SafeArray::size () const{
    return _length;
}
// 測試是否超出陣列長度
bool SafeArray::isSafe(int i) {
    if(i >= _length || i < 0) {
        return false;
    } 
    else {
        return true;
    }
}

// 取得陣列元素值
int SafeArray::get(int i) {
    if(isSafe(i)) {
        return _array[i];
    }
 
    return 0;
}

// 設定陣列元素值
void SafeArray::set(int i, int value) {
    if(isSafe(i)) {
        _array[i] = value;
    }
}

// 刪除動態配置的資源
SafeArray::~SafeArray() {
    delete [] _array;
    cout<<"end: "<<count<<endl;
    count++;
}
void modify(SafeArray &x){
    for (int i=0;i<x.size();i++){
        if(i%2==0){
            x.set(i,5);
        }
    }
}

//由於參數列上x使用const宣告 表示不可更動x實例的狀態 也就是不得（在呼叫函式時）更動x的資料成員
//為了讓編譯器得知這項訊息 要在所呼叫的函式上加上const

void fun(const SafeArray &x){
    x.size();
}

int main() {
    SafeArray safeArray(10);
    for(int i = 0; i < safeArray.size(); i++) {
        safeArray.set(i, (i + 1) * 10);
    }
    for(int i = 0; i < safeArray.size(); i++) {
        cout << safeArray.get(i) << " ";
    }
    cout << endl;
    
    SafeArray *ptr = new SafeArray(10);
    for(int i = 0; i < ptr->size(); i++) {
        ptr->set(i, (i + 1) * 10);
    }
    for(int i = 0; i < ptr->size(); i++) {
        cout << ptr->get(i) << " ";
    }
    cout << endl;
    delete ptr;
 
    SafeArray arrs[] = {SafeArray(5), SafeArray(10), SafeArray(15)};
    for(int i = 0; i < 3; i++) {
        SafeArray *safeArray = arrs + i;
        for(int j = 0; j < safeArray->size(); j++) {
            safeArray->set(j, (j + 1) * 10);
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < arrs[i].size(); j++) {
            cout << arrs[i].get(j) << " ";
        }
        cout << endl;
    }
    
    //int (SafeArray::*mfPtr1)(int) = 0;
    //void (SafeArray::*mfPtr2)(int, int) = 0;
    typedef void (SafeArray::*MFPTR1)(int, int); 
    typedef int (SafeArray::*MFPTR2)(int);
    MFPTR1 mfPtr1 = 0;
    MFPTR2 mfPtr2 = 0;
    mfPtr1 = &SafeArray::set;
    mfPtr2 = &SafeArray::get;
 
    SafeArray safe(10);
    for(int i = 0; i < safe.size(); i++) {
        (safe.*mfPtr1)(i, (i+1)*10);
    }
    for(int i = 0; i < safe.size(); i++) {
        cout << (safe.*mfPtr2)(i) << " ";
    }
    cout << endl;
    
 
    SafeArray *safePtr = &safe;
    (safePtr->*mfPtr1)(2, 1000);
    for(int i = 0; i < safePtr->size(); i++) {
        cout << (safePtr->*mfPtr2)(i) << " ";
    }
    cout << endl; 
    
    SafeArray mat1(5);
    for(int i=0;i<mat1.size();i++){
        mat1.set(i,2);
    }
    SafeArray mat2(mat1);
    modify(mat1);
    for(int i = 0; i < mat1.size(); i++) {
        cout << mat1.get(i) << " ";
    }
    cout<<endl;
    for(int i = 0; i < mat2.size(); i++) {
        cout << mat2.get(i) << " ";
    }
    cout<<endl;
    
    
}