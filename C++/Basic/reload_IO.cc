#include <iostream> 
using namespace std; 

class Point { 
    int x, y; 
public: 
    Point() { 
        x = y = 0; 
    } 

    Point(int x, int y) { 
        this->x = x; 
        this->y = y; 
    } 

    friend istream &operator>>(istream &s, Point &p); 
    friend ostream &operator<<(ostream &s, Point p); 
}; 

istream &operator>>(istream &s, Point &p) { 
    cout << "輸入點座標: "; 
    s >> p.x >> p.y; 
    return s; 
} 

ostream &operator<<(ostream &s, Point p) { 
    s << "("<< p.x << ", " << p.y << ")"; 
    return s; 
} 

int main() { 
    Point p1; 

    cin >> p1; 
    cout << "p1: " << p1 << endl; 

    return 0; 
}
/*
通常重載 << 運算子時，會使用friend函式，這是因為重載 << 函式時，它不是一個成員函式
理由在於 << 左邊不是物件，而是一個輸出串流
由於 << 函式不是成員函式，若要能存取資料成員
則該資料成員必須設定為public，使用friend函式來進行重載的話，則不用受此限制。 

注意第二個參數必須是參考，這樣才可以將資訊指定給所要的物件
而不是一個複製物件；同樣的，重載 >> 運算子多是利用friend函式進行
*/