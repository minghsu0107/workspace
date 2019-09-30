#include <iostream>
#include <cstring> 
using namespace std;

void foo(int x) {           //overloaded function 
  x = 5;                    //對同名函式 據參數列的參數資料型態或參數的個數判斷呼叫
}
void change2(int &x) {
  x = 5;
}
inline void change3(int *p) {//參數為pointer, 所以要給函式的參數指定位址
  *p = 5;                    //行內函式建議可以直接定義於表頭檔案中
}

void foo2(char *p){
  char *pt = new char(10); //p只更改了複製的tString 對原來無影響
  pt="World";
  p=pt;
}

void foo(char** ppStr){// 宣告 ppStr 是一個指向 "字元指標" 的指標
    char *pStr = new char(10); // 配置 10 個字元的空間
    strcpy(pStr, "Hello"); // 設定字串
    *ppStr = pStr; // 將 ppStr 指的內容設為 pStr
}

int main() {
  int x = 1;
  cout << x<<endl; 
  foo(x);//pass by value 但只是改了複製的參數 對原來的無影響
  cout << x<<endl;
  change2(x);//改變了原來的參數 pass by reference
  cout << x<<endl;
  change3(&x);//pass by value(address)
  cout << x<<endl;//value of x was changed to 5
  
  char tString[]={'\0'};
  foo2(tString);
  printf("%s\n", tString);
  
  char *pString="abc"; // 宣告一個字元指標
  cout<<pString<<endl;
  foo(&pString); // 將字元指標的位址傳給函式
  printf("%s\n", pString); // 將傳回的字串 "Hello" 印出來
  
}