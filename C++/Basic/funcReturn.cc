#include <iostream>
#include <string>
using namespace std;

int* createArray(int);
void deleteArray(int*);
string foo();   //pass by value
string& foo2(); //pass by reference
string& foo3(); //pass by reference
string* foo4(); //pass by value

int main(){
    //利用指標傳遞陣列給函式，以及傳回一個陣列
     int m = 4; 
     cout << "陣列大小: "<<m<<endl; 
    
     int *arr = createArray(m); //
    
     for(int i = 0; i < m; i++) {
     arr[i] = i; 
     }
     for(int i = 0; i < m; i++) {
     cout << "arr[" << i << "] = " 
     << arr[i] << endl; 
     }
     deleteArray(arr);
     
     string str; // 空字串
     str=foo();
     cout << "address: " << &str 
     << endl << str << endl<<endl; //傳回的字串在傳值時是複製一份新的傳回 所以兩個字串的記憶體位置不相同
     
     string &str2=foo2(); 
     cout << "address: " << &str2 
     << endl << str2 << endl<<endl; //foo2()執行時傳參考給str2 直接與字串共用記憶體位置
                              //但foo2()執行結束後自動回收s記憶體(無宣告new) 
                              //因此str2保留了s的位址 卻找不到s的內容
     string &str3 = foo3(); //&表參考
     cout << "address: " << &str3 //&表位址
     << endl << str3 << endl<<endl; 
     delete &str3; //回收string型態參考的記憶體
     // 因為delete &str3 所以foo4()中宣告的new string位址直接用delete後還回的
     
     string *str4=foo4(); //宣告字串指標以接收函式傳回的位址
     cout << "address: " << str4 
     << endl << *str4 << endl<<endl; 
     delete str4; //回收string型態指標的記憶體
     
}
// 傳回建立的陣列位址
int* createArray(int m) { 
     int *a = new int[m]; 
     for(int i = 0; i < m; i++) {
     a[i] = 0; 
     }
     return a; 
}
//若不是用new配置 則副函式中宣告的變數記憶體在函式執行結束後都會自動回收
//因此傳回指標值也就沒有意義 也會造成存取錯誤
void deleteArray(int* arr) {
     delete [] arr; 
}

string foo(){
     string s = "This is caterpillar speaking."; 
     cout << "address: " << &s 
     << endl << s << endl; 
     return s; 
}
string& foo2() { 
     string s = "This is caterpillar speaking."; 
     cout << "address: " << &s 
     << endl << s << endl; 
     return s; 
}
string& foo3() { //string& 表傳回string型態的參考
     string *s = new string("This is caterpillar speaking."); //宣告string指標 s
     cout << "address: " << s 
     << endl << *s << endl; 
     return *s; 
}
string* foo4(){  //string* 表傳回string型態的指標(即指標所存的位址)
     string *s = new string("This is caterpillar speaking."); //宣告string指標 s
     cout << "address: " <<s 
     << endl << *s << endl; 
     return s; 
}