#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int a, b, c;
	//Edge() { a = b = c = 0; }
	//Edge(int a, int b, int c): a(a), b(b), c(c) {}
	Edge(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
};
bool operator< (Edge x, Edge y) { return x.a < y.a; }
ostream& operator<< (ostream& os, Edge& e) { 
	cout << e.a << " " << e.b << " " << e.c << endl;
	return os; 
}
int main() {
    Edge p, q(1, 2, 3);
    Edge e = (Edge){3, 2, 1};
    cout << p << q << e;
    cout << (p < q) << endl;
}