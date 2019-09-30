#include <iostream>
using namespace std;

int main(){
    int8_t aa;
    int16_t bb;
    int32_t cc;
    int64_t dd;
    const int maxNum = 10; // 將數值指定給變數之後，就不允許再將其它值指定給同一變數
    //maxNum = 20;  // error: assignment of read-only variable `maxNum'
    // int *ptr=&maxNum  // error: invalid conversion from `const int*' to `int*' 
    const int *vptr = &maxNum; //用const宣告的變數必須使用對應的const型態指標 不能再改變記憶體指向的值
    // const int* == int const*
    //*vptr = 20; // error, assignment of read-only location
    
    int v = 10;
    int* const vtr = &v; // 不能指定新的記憶體位址
    //vtr = &x;  // error,  assignment of read-only variable `vtr' 
    *vtr=3;// 可改變記憶體指向的值
    
    const int* const vtr2 = &maxNum; // constant for both pointer and value

    int x = 5;
    int y = 2;
    cout<<x / y<<endl;    // 得到 2
    
    cout<<(10>5)<<endl;//所有非零的數值在作為條件式時都被視為true
    
    double z = 5;
    cout<<z / y <<endl;   // 得到 2.5;合 int 及 double 的運算式, 則會試著先將 int 轉成 double 再做運算
    
    int m=3, n=2;
    double ans = (double)m/n; // ans -> 1.5
    cout<<ans<<endl;
    //變數的值取出後會轉換為 type, 再繼續其它計算, 但不影響變數原本的值
    //ans 計算完成之後, a 變數的值仍然維持 3 山非 3.0
    
    int nu = 0; 
    double number = 3.14; 
    nu = static_cast<int>(number);
    cout<<nu<<endl;
    int numb = 10;
    cout << static_cast<double>(numb) / 3;
    
    int num = 5;
    double realNum = num; // realNum -> 5.0
    cout<<realNum<<endl;
    
    double real = 6.79;
    int a = real; // a -> 6
    double b = (int)real; // b -> 6.0
    cout<<"a: "<<a<<" b: "<<b<<" real: "<<real<<endl;
    
    int a1=3, b1=2, c1=3;
    bool x1 = a1 > b1;  // x1 -> 1
    bool y1 = a1 < b1;  // y1 -> 0
    bool z1 = a1 >= c1; // z1 -> 1
    bool w1 = a1 <= b1; // w1 -> 0
    cout<<x1<<" "<<y1<<" "<<z1<<" "<<w1<<endl;
    //因為計算誤差的緣故不能依賴 == 或是 != 比較兩個浮點數
    
    int d=3, e=2;
    bool j = d > e++;  // j -> 1;先執行 d>e, 再執行e++ (程式由左而右執行)
    cout <<j<<" "<<e<<endl; // 印出 3
    int d1=3,e1=2;
    bool k = d1 > ++e1;       // k -> 0;先執行 ++e1, 再執行d1>e1
    cout <<k<<" "<<e1<<endl;  // 印出 3
    
    
    
}