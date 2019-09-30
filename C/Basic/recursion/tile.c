#include <stdio.h>
int dx[5][3] = {{}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, 1}, {-1, -1, 1}};
int dy[5][3] = {{}, {1, -1, -1}, {-1, -1, 1}, {1, 1, -1}, {1, -1, 1}};
int T[5][3] = {{}, {4, 1, 2}, {1, 2, 3}, {4, 3, 2}, {4, 1, 3}};
void tile(int halfLen, int x, int y, int type) {
	while (halfLen > 1) {
	    halfLen /= 2;
        for (int i = 0; i < 3; i++){
            tile(halfLen, x + dx[type][i] * halfLen, y + dy[type][i] * halfLen, T[type][i]);
        }
    }
    printf("%d %d %d\n", type, x, y); // print the center at last
}
void tile2(int halfLen, int x, int y, int type) {
	printf("%d %d %d\n", type, x, y); // print the center
	while (halfLen >= 2) {
	    halfLen /= 2; // scale of sub-tiles (from largest(outmost) to smallest)
	    // go through sub-tiles in three directions
        for (int i = 0; i < 3; i++) {
            tile2(halfLen, x + dx[type][i] * halfLen, y + dy[type][i] * halfLen, T[type][i]);
        }
    }
}
void tile3(int halfLen, int x, int y, int type) {
	printf("%d %d %d\n", type, x, y);
	for (int i = 1; i <= halfLen / 2; i *= 2) {
        for (int j = 0; j < 3; j++) {
            tile3(i, x + dx[type][j] * i, y + dy[type][j] * i, T[type][i]);
        }
	}
}
int main() {
    int l, m;
    scanf("%d%d", &l, &m);
    int k = l / m;
    int cnt = 0;
    while (k > 1) {
        k >>= 1;
        cnt++;
    }
    int nx = 0;
    for(int i = 0; i < cnt; i++){
        l >>= 1;
        nx += l;
        tile3(l, nx, nx, 1); // initial center type is 1
    }
    return 0;
}