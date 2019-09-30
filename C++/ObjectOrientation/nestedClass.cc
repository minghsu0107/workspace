#include <iostream>
using namespace std;

class PointDemo {
public:
    PointDemo(int);
    ~PointDemo();
 
    void show();
    
    //內部類別實作時不可存取外部類別的私用成員 如果要存取私用成員 必須宣告外部類別為friend
    friend class Point;
private:
    // Nested Class
    class Point {
    public:
        Point();
        Point(int, int);
        
        int x() { return _x; }
        int y() { return _y; }
        void x(int x) { _x = x; }
        void y(int y) { _y = y; }
        
        //外部類別實作時不能存取內部類別的私用成員 如果要存取 必須宣告外部類別為friend
        friend class PointDemo;
    private:
        int _x;
        int _y;
    };
 
    Point **_points;
    int _length;
};
// 實作內部類別
PointDemo::Point::Point() {
    _x = 0;
    _y = 0;
}

// 實作內部類別
PointDemo::Point::Point(int x, int y) {
    _x = x;
    _y = y;
}
PointDemo::PointDemo(int length) : _length(length) {
    _points = new Point*[_length];
    for(int i = 0; i < _length; i++) { 
        _points[i] = new Point(); //_points[i] is a pointer(Point*)
        _points[i]->x(i*5);
        (*_points[i]).y(i*5);
    } 
}

void PointDemo::show() {
    for(int i = 0; i < _length; i++) { 
    cout << "(x, y) = (" 
         << _points[i]->x() << ", "
         << _points[i]->y() << ")"
         << endl;
    } 
}

PointDemo::~PointDemo() {
    for(int i = 0; i < _length; i++) { 
        delete _points[i];
    } 
    delete [] _points;
}
int main() {
    PointDemo demo(10);
    demo.show(); 
    return 0;
}