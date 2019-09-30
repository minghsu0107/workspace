#include <stdio.h>
#include <stdlib.h>
#define maxn 101
#define swap(x, y) {int t; t = x, x = y, y = t;}
typedef int Matrix[maxn][maxn];
void gauss_elimination(Matrix A, int n) {
	int r;
    for (int i = 0; i < n; i++) {
        r = i;
        for (int j = i + 1; j < n; j++)
        	if (abs(A[j][i]) > abs(A[r][i])) r = j;
        if (r != i) {
        	for (int j = 0; j <= n; j++)
        		swap(A[r][j], A[i][j]);
        }
        for (int k = i + 1; k < n; k++) {
        	int f = A[k][i] / A[i][i];
        	for (int j = i; j <= n; j++) 
        		A[k][j] -= f * A[i][j];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
    	for (int j = i + 1; j < n; j++) {
            A[i][n] -= A[j][n] * A[i][j];
    	}
    	A[i][n] /= A[i][i];
    }
}
int find(int answer[], Matrix A, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (answer[i]) {
			for (int j = 0; j < n; j++) {
				if (A[j][i]) {
					sum += A[j][n];
					break;
				}
			}
		}
	}
	return sum;
}
int main(int argc, char const *argv[])
{
	int n, answer[maxn];
	Matrix A;
	while (scanf("%d", &n) == 1) {
		  for (int i = 0; i < n; i++) {
              for (int j = 0; j <= n; j++) {
                  scanf("%d", &A[i][j]);
              }
		  }
		  for (int i = 0; i < n; i++) {
		  	  scanf("%d", &answer[i]);
		  }
		  gauss_elimination(A, n);
		  printf("%d\n", find(answer, A, n));
    }
	return 0;
}