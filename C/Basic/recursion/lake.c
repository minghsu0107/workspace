#include <stdio.h>
#include <stdlib.h>
#define swap(x,y) {int t; t = x; x = y; y = t;} 
int compare(const void *data1, const void *data2) {
    int *ptr1 = (int *) data1;
    int *ptr2 = (int *) data2;
    if (*ptr1 < *ptr2) return 1;
    else if (*ptr1 > *ptr2) return -1;
    else return 0;
    // return *ptr2 - *ptr1
}
int grid[400][400], area[80001] = {};
int n, m, count, len = 0;
int isIn(int row, int column) { return (row >= 0 && row < n && column >= 0 && column < m); }
void find(int r, int c) {
    grid[r][c] = 0;
    count++;
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        int next_r = r + dr[i];
        int next_c = c + dc[i];
        if (isIn(next_r, next_c) && grid[next_r][next_c] == 1) {
            find(next_r, next_c);
        }
    }
    return;
}
int partition(int arr[], int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for(int j = front; j < end; j++) {
        if (arr[j] >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[end]);
    return i + 1;
}
void sort(int arr[], int front, int end) {
    if (front >= end) return;
    int index = partition(arr, front, end);
    sort(arr, front, index-1);
    sort(arr, index+1, end);
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
                count = 0;
                find(i, j);
                area[len++] = count;
            }
        }
    }
    //sort(area, 0, len - 1);
    qsort(area, len, sizeof(int), compare);
    for (int i = 0; i < len; i++) {
        printf("%d\n", area[i]);
    }
    return 0;
}
