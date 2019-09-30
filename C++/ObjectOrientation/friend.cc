#include <iostream>
using namespace std;

//使用friend關鍵字來設定類別的好友函式 該函式可以直接存取該類別的私用成員
//使用friend函式通常是基於效率的考量，以直接存取私用成員而不透過函式呼叫

class Ball;

int compare(Ball&, Ball&);

class Ball { 
public: 
    Ball(double, char*); 
 
    double radius() {
        return _radius;
    }
 
    char* name() {
        return _name; 
    }
 
    void radius(double radius) {
        _radius = radius;
    } 
 
    void name(char *name) {
        _name = name;
    }
 
    // 宣告朋友函式 
    friend int compare(Ball&, Ball&);
 
private:
    double _radius; // 半徑 
    char *_name; // 名稱 
};

// compare不為Ball的成員　但為Ball的friend函式
int compare(Ball &b1, Ball &b2) {
    // 可直接存取私用成員
    if(b1._radius == b2._radius)
        return 0;
    else if(b1._radius > b2._radius)
        return 1;
    else
        return -1;
}

Ball::Ball(double radius, char *name) { 
    _radius = radius; 
    _name = name;
}

int main() {
    Ball b1(10, "RBall");
    Ball b2(20, "GBall");
 
    switch(compare(b1, b2)) {
        case 1:
            cout << b1.name() << " 較大" << endl;
            break;
        case 0:
            cout << b1.name() << " 等於 " << b2.name() << endl;
            break;
        case -1:
            cout << b2.name() << " 較大" << endl;
            break;
    }
 
    return 0;
}