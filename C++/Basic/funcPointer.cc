#include <iostream>
using namespace std;

//函式本身在記憶體中也佔有一個空間，而函式名稱本身也就是指向該空間位址的參考名稱
//當呼叫函式名稱時，程式就會執行該函式名稱所指向的記憶體空間中之指令。

int foo(); 
typedef bool (*CMP)(int, int);//使用 typedef定義比較容易閱讀的名稱
void swap(int&, int&);
bool larger(int a, int b);
bool smaller(int a, int b);
void sort(int*, int, CMP);//若不用typedef then: void sort(int*, int, bool (*compare)(int, int));

int main() { 
    int (*ptr)() = 0; //宣告函式指標 它與某個函式指向相同的空間: 傳回值型態 (*指標名稱)(傳遞參數);
    ptr = foo; //指標取得函式的位址
    foo(); 
    ptr();     //呼叫函式
    cout << "address of foo:" 
         << foo << endl; 
    cout << "address of foo:" 
         << ptr << endl;      //兩個的記憶體空間是相同的
    
    int number1[] = {3, 5, 1, 6, 9};
    sort(number1, 5, larger);
    cout << "大的在前 ";
    for(int i = 0; i < 5; i++) {
        cout << number1[i] << " ";
    }
    cout << endl;

    int number2[] = {3, 5, 1, 6, 9};
    sort(number2, 5, smaller);
    cout << "小的在前 ";
    for(int i = 0; i < 5; i++) {
        cout << number2[i] << " ";
    }
    cout << endl;
}
int foo() { 
    cout << "function point" << endl; 
    return 0; 
}

void swap(int &a, int &b) {
    int t = a; 
    a = b; 
    b = t;
}

bool larger(int a, int b) {
    return a > b;
}

bool smaller(int a, int b) {
    return a < b;
}

void sort(int* arr, int length, CMP compare ) { //若不用typedef then: void sort(int* arr, int length, bool (*compare)(int, int))
    int flag = 1; 
    for(int i = 0; i < length-1 && flag == 1; i++) { 
        flag = 0; 
        for(int j = 0; j < length-i-1; j++) { 
            if(compare(arr[j+1], arr[j])) { 
                swap(arr[j+1], arr[j]); 
                flag = 1; 
            } 
        } 
    } 
}
