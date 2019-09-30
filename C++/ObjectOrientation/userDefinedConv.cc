#include <iostream>
using namespace std;

//Integer類別將int基本型態包裝為物件 以提供更多物件導向上的操作行為
//為了支援與int基本型態的直接算術行為　使用operator int()定義了如何轉換
//當編譯器需要作int型態轉換時 就會使用自定義的行為

class Integer {
public:
    Integer(int value) : _value(value) {
    }
 
    int value() {
        return _value;
    }
 
    // 自訂型態轉換
    // 當需要將Integer轉換為int時如何執行 
    operator int() {
        return _value;
    }
    //編譯器會根據自訂型態做轉換 自動將自訂型態轉換為基本型態或指定的型態
    //operator後緊跟著的即是轉換的目標型態 也可以指定轉換為自訂義型態
    //ex: operator Other(){...}
    
    int compareTo(Integer);
 
private:
    int _value;
};
int Integer::compareTo(Integer integer) {
    if(_value > integer._value) {
        return 1;
    }
    else if(_value < integer._value) {
        return -1;
    }
 
    return 0;
}
int main() {
    Integer i1(10);
    Integer i2(20);
 
    cout << i1.compareTo(i2) << endl;
 
    cout << i1 + 10 << endl;
 
    return 0;
}