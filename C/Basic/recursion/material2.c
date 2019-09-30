#include <stdio.h>
int arr[3][3];
int flag = 0;
void judge (int a, int b, int c) {
    if (!flag && a == 0 && b == 0 && c == 0 ) {
        printf ("yes\n");
        flag = 1;
        return;
    }
    if (!flag && a - arr[0][0] >= 0 && b - arr[0][1] >= 0 && c - arr[0][2] >= 0) {
       judge (a - arr[0][0], b - arr[0][1], c - arr[0][2]);
    }
    if (!flag && a - arr[1][0] >= 0 && b - arr[1][1] >= 0 && c - arr[1][2] >= 0) {
       judge (a - arr[1][0], b - arr[1][1], c - arr[1][2]);
    }
    if (!flag &&a - arr[2][0] >= 0 && b - arr[2][1] >= 0 && c - arr[2][2] >= 0) {
       judge (a - arr[2][0], b - arr[2][1], c - arr[2][2]);
    }
}
void readArr (int i, int j) {
    if (i == 3) return;
    scanf("%d", &arr[i][j]);
    if (j < 2) readArr(i, j+1);
    else readArr(i+1, 0);
}
void readData (int n) {
    if (n == 0) return;
    int a, b, c;
    scanf ("%d%d%d", &a, &b, &c);
    judge (a, b, c);
    if (!flag) printf ("no\n");
    flag = 0;
    readData(n-1);
}
int main(){
    readArr(0,0);
    int n;
    scanf ("%d", &n);
    readData(n);
    return 0;
}
