#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	Point& operator= (const Point& p) {
		x = p.x; y = p.y;
		return *this;
	}
};
typedef Point Vector;
Vector operator+ (const Vector& A, const Vector& B)
{ return Vector(A.x + B.x, A.y + B.y); }
Vector operator- (const Vector& A, const Vector& B)
{ return Vector(A.x - B.x, A.y - B.y); }
Vector operator* (const Vector& A, int p)
{ return Vector(A.x * p, A.y * p); }
bool operator== (const Point& a, const Point& b)
{ return a.x == b.x && a.y == b.y; }
bool operator< (const Point& a, const Point& b)
{ return a.x < b.x || (a.x == b.x && a.y < b.y); }
istream& operator>> (istream& is, Point& p) { return is >> p.x >> p.y; }
ostream& operator<< (ostream& os, Point& p) { 
	cout << p.x << " " << p.y << endl;
	return os; 
}
int main() {
    Point a(1, 1), b, d;
    Point c = a + b;
    d = a + c;
    cout << a << b << c << d;
}