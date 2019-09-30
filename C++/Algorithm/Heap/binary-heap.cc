#include <bits/stdc++.h>
using namespace std;

class Heap {
private:
	vector<int> A;
	int n, MAXHEAP;
	void pushup(int x);
	void pushdown(int x);
public:
	Heap(): n(0), MAXHEAP(100) {
		A.push_back(-1);
	}
	Heap(int max): n(0), MAXHEAP(max) {
		A.push_back(-1);
	}
	int removeMin();
	void add(int i);
	bool isFull();
	bool isEmpty();
};
void Heap::pushdown(int x) {
    int P = x, S = x<<1;
    while (S <= A.size() - 1) {
        if (S < A.size() - 1 && A[S+1] < A[S]) // choose the smaller child
			S++;
        if (A[P] <= A[S])
			break;
        swap(A[P], A[S]);
		P = S, S = P<<1;
    }
}
void Heap::pushup(int x) {
	int S = x, P = x>>1;
    while (S >= 2 && A[P] > A[S]) {
    	swap(A[P], A[S]);
        S = P, P = S>>1;
    }
}
int Heap::removeMin() {
     int mn = A[1];
     A[1] = A.back();
     A.resize(A.size() - 1);
     pushdown(1);
     return mn;
}
void Heap::add(int i) {
     A.push_back(i);
     pushup(A.size() - 1);
}
bool Heap::isFull() {
     return A.size() - 1 == MAXHEAP;
}
bool Heap::isEmpty() {
     return A.size() - 1 == 0;
}

int main() {
	vector<int> v = {2, 1, 3, 5, 4};
	Heap h;

	for (int& i: v) h.add(i);
	cout << h.isEmpty() << endl;

	for (int i = 0; i < v.size(); i++)
		cout << h.removeMin() << " ";
	cout << endl;

	cout << h.isEmpty() << endl;
}