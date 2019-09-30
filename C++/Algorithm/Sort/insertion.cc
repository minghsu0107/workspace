#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int *A, int n) {
	for (int i = 1; i < n; i++) {
		char cur = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > cur) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = cur;
	}
}

int main () {
	int A[6] = {6, 1, 2, 3, 5, 4};
	insertion_sort(A, 6);
	for (auto &x: A) cout << x << " "; 
}