#include <stdio.h>
int arr[3][3];
int flag = 0;
void judge (int a, int b, int c) {
    if (!flag && a == 0 && b == 0 && c == 0) {
        printf ("yes\n");
        flag = 1;
        return;
    }
    for (int i = 0; i < 3 && !flag; i++) {
        if (a - arr[i][0] >= 0 && b - arr[i][1] >= 0 && c - arr[i][2] >= 0) {
           judge (a - arr[i][0], b - arr[i][1], c - arr[i][2]);
        }
    }
}
int main(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            scanf("%d",&arr[i][j]);
        }
    }
    int n, a, b, c;
    scanf ("%d", &n);
    for (int i = 0; i < n; i++){
        scanf ("%d%d%d", &a, &b, &c);
        judge (a, b, c);
        if (!flag) printf ("no\n");
        flag = 0;
    }
    return 0;
}
