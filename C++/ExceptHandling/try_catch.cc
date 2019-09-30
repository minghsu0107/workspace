#include <iostream> 
using namespace std;

int main() { 
    int a = 0;
    int b = 0;

    cout << "請輸入被除數: "; 
    cin >> a; 
    cout << "請輸入除數: "; 
    cin >> b;

    try { 
        if(b == 0) 
            throw "發生除零的錯誤"; 
        cout << "a / b = " 
             << static_cast<double>(a) / b 
             << endl; 
    } 
    /*
    catch(int err) { 
        cout << "除數為: " << err << endl; 
        cout << "結果無限大" << endl; 
    } 
    */
    catch(const char* str) { 
        cerr << "錯誤: " << str << endl; 
    } 
    catch(...) {
        cout << "處理所有的例外" << endl;
    }
    return 0;
}
/*
當檢查到錯誤發生時，使用throw丟出一個數值，這個數值可能是一個整數、浮點數、字串或是物件
發生錯誤時，執行哪一段catch區塊是由您所丟出的資料型態而定，丟出整數時就由設定catch整數的區塊捕捉
丟出浮點數時就用設定catch浮點數的區塊捕捉
您也可以直接丟出一個代表錯誤訊息的字串，以說明錯誤的原因

如果您丟出例外而catch中並沒有相對捕捉該例外的區塊
則程式會呼叫標準函式庫中的terminate()函式，而預設terminate()會呼叫 abort()函式來終止程式。

如果您想捕捉所有型態的例外，您可以使用catch(...)，通常這會放在所有catch之後
以捕捉所有尚未考慮到的例外狀況
*/
