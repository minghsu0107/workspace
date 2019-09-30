#include <bits/stdc++.h>
using namespace std;
// [x, y]
int bsearch(int* A, int x, int y, int v) {
	int m;
	while (x <= y) {
		m = x + (y - x) / 2;
		if (A[m] == v) return m;
		if (A[m] > v) y = m - 1;
		else x = m + 1;
	}
}
// return the position of the first element that >= v
// if all elements < v, return last position
int lower_bound(int *A, int x, int y, int v) {
	int m;
	while (x < y) {
		m = x + (y - x) / 2;
		if (A[m] >= v) y = m;
		else x = m + 1;
	}
	return x;
}
// return the position of the last element that <= v
// if all elements > v, return first position
int upper_bound(int *A, int x, int y, int v) {
	int m;
	while (x < y) {
		m = (x + y + 1) >> 1;
		if (A[m] <= v) x = m;
		else y = m - 1;
	}
	return x;
}

int main() {
	int A[] = {1, 5, 3, 2, 2, 2};
	sort(A, A + 6);
	// A = {1, 2, 2, 2, 3, 5}
	cout << bsearch(A, 0, 5, 2) << endl;
	cout << lower_bound(A, 0, 5, 14) << " " << upper_bound(A, 0, 5, 14) << endl;
	cout << lower_bound(A, 0, 5, 4) << " " << upper_bound(A, 0, 5, 4) << endl;
	cout << lower_bound(A, 0, 5, 0) << " " << upper_bound(A, 0, 5, 0) << endl;
	cout << lower_bound(A, 0, 5, 1) << " " << upper_bound(A, 0, 5, 1) << endl;
	cout << lower_bound(A, 0, 5, 2) << " " << upper_bound(A, 0, 5, 2) << endl;
	return 0;
}