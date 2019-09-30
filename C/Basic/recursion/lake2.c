#include <stdio.h>
#include <stdlib.h>
int compare(const void *data1, const void *data2) {
    int *ptr1 = (int *) data1;
    int *ptr2 = (int *) data2;
    if (*ptr1 < *ptr2) return 1;
    else if (*ptr1 > *ptr2) return -1;
    else return 0;
    // return *ptr2 - *ptr1
}
int grid[400][400], area[80001] = {};
int n, m, len = 0;
int isIn(int row, int column) { return (row >= 0 && row < n && column >= 0 && column < m); }
int find(int r, int c) {
    int k = 1;
    grid[r][c] = 0;
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        int next_r = r + dr[i];
        int next_c = c + dc[i];
        if (isIn(next_r, next_c) && grid[next_r][next_c] == 1) {
            k += find(next_r, next_c);
        }
    }
    return k;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d",&grid[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j]) {
                area[len++] = find(i, j);
            }
        }
    }
    qsort(area, len, sizeof(int), compare);
    for (int i = 0; i < len; i++) {
        printf("%d\n", area[i]);
    }
    return 0;
}

// 10 8
// 1 1 1 1 1 1 1 1
// 1 0 0 0 0 0 0 1
// 1 0 0 1 1 0 0 1
// 1 0 1 1 1 1 0 1
// 1 0 0 0 0 1 0 1
// 1 0 1 0 0 1 0 1
// 1 0 1 1 1 1 0 1
// 1 0 0 1 1 0 0 1
// 1 0 0 0 0 0 0 1
// 1 1 1 1 1 1 1 1
