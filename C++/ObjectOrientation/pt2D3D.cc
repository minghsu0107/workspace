#include <iostream>
using namespace std;

//公開繼承某個類別時 該成員的所有public成員都可以在衍生類別中被呼叫使用
//而private成員則不可以直接在衍生類別中被呼叫使用
class Point2D { 
public: 
    // default
    Point2D() {
        _x = 0;
        _y = 0;
    }
    Point2D(int x, int y) : _x(x), _y(y) {
    }
    int x() {return _x;} 
    int y() {return _y;} 
    void x(int x) {
        _x = x;
    }
    void y(int y) {
        _y = y;
    }
    
    Point2D operator+(const Point2D&); // 重載+運算子 例如 p1+p2
    Point2D operator-(const Point2D&); // 重載-運算子 例如 p1-p2
    //Point2D& operator++(); // 重載++前置，例如 ++p 
    //Point2D operator++(int); // 重載++後置，例如 p++  (在後置中會傳入一個0 但實質上沒有作用 只是識別用)
    Point2D& operator--(); // 重載--前置，例如 --p 
    Point2D operator--(int); // 重載--後置，例如 p--
    
    //使用類別成員來超載二元運算子時，會有一個限制，就是運算子的左邊一定要是原物件
    //使用friend函式重載二元運算子時 要指定兩個參數型態 分別表式運算子左右邊的運算元型態
    
    friend Point2D operator+(const Point2D&, int); // 例如p+10 
    friend Point2D operator+(int, const Point2D&); // 例如10+p 
    friend Point2D operator++(Point2D&);  // 前置 ++p
    friend Point2D operator++(Point2D&, int); // 後置 p++
private:
    int _x;
    int _y;
};
Point2D Point2D::operator+(const Point2D &p) { 
    Point2D tmp(_x + p._x, _y + p._y); 
    return tmp; 
} 

Point2D Point2D::operator-(const Point2D &p) { 
    Point2D tmp(_x - p._x, _y - p._y); 
    return tmp; 
} 
Point2D& Point2D::operator--() { 
    _x--; 
    _y--; 

    return *this; 
} 

Point2D Point2D::operator--(int) { 
    Point2D tmp(_x, _y); 
    _x--; 
    _y--; 

    return tmp; 
} 

Point2D operator+(const Point2D &p, int i) { 
    Point2D tmp(p._x + i, p._y + i); 

    return tmp; 
} 

Point2D operator+(int i, const Point2D &p) { 
    Point2D tmp(i + p._x, i + p._y);

    return tmp; 
}
Point2D operator++(Point2D &p) { 
    p._x++; 
    p._y++; 
  
    return p; 
} 

Point2D operator++(Point2D &p, int) { 
    Point2D tmp(p._x, p._y); 

    p._x++; 
    p._y++; 

    return tmp; 
} 

class Point3D : public Point2D { 
public: 
    Point3D() { 
        _z = 0; 
    } 
    Point3D(int x, int y, int z) : Point2D(x, y), _z(z) { 
    } 
    int z() {return _z;}
    void z(int z) {_z = z;}
 
private:
    int _z;
}; 

int main() {
    Point2D t1(5, 5);
    Point2D t2; 
    t2 = 10 + t1;
    cout << "t2: (" 
         << t2.x() << ", " 
         << t2.y() << ")"
         << endl;
    t2++;
    cout << "t2: (" 
         << t2.x() << ", " 
         << t2.y() << ")"
         << endl;
    ++t2;
    cout << "t2: (" 
         << t2.x() << ", " 
         << t2.y() << ")"
         << endl;
    t2=t2-t1;
    cout << "t2: (" 
         << t2.x() << ", " 
         << t2.y() << ")"
         << endl;
    --t2;
     cout << "t2: (" 
         << t2.x() << ", " 
         << t2.y() << ")"
         << endl;
    cout<<endl;
    
    Point3D p1(1, 3, 4);
    Point3D p2; 

    cout << "p1: (" 
         << p1.x() << ", " 
         << p1.y() << ", " 
         << p1.z() << ")"
         << endl;
 
    p2.x(5);
    p2.y(7);
    p2.z(8);
 
    cout << "p2: (" 
         << p2.x() << ", " 
         << p2.y() << ", " 
         << p2.z() << ")"
         << endl;
 
}
