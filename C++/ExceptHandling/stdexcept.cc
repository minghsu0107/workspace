#include <iostream> 
#include <stdexcept> 
using namespace std; 
 
int main() { 
    double *ptr; 
 
    do { 
        try { 
            ptr = new double[1000000]; 
        } 
        catch(bad_alloc err) { 
            cout << "配置失敗" 
                 << err.what() 
                 << endl; 
             return 1; 
        } 
        cout << "配置OK\n"; 
    } while(ptr); 
 
    return 0;
}
/*
當錯誤發生而丟出例外物件時，您可以使用what()方法來取得錯誤訊息

利用迴圈不斷配置記憶體
直到記憶體不足而發生bad_alloc例外為止這個錯誤訊息視您所採用的編譯器而有所不同
*/