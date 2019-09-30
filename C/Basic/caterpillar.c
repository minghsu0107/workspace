#include <stdio.h>
#include <stdlib.h>
//由於身體一開始平行於兩軸，可以得到最大值相當於 L≤min(N,M)≤1000
//我們只需要宣告 int row[1024], column[1024];
//通常習慣宣告 2^n 大小，因為抓值時，計算索引值能跑得更快
char g[1024][1024]; // check if collision; if body is in that grid, then mark it as 1
int bp[1024][2]; // saving rows and columns of each section of the caterpillar
int main() {
    int n, m;
    int sx, sy, ex, ey; // sx,sy-> head's; ex,ey-> tail's
    int q, cmd;
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
    int L = abs(sx-ex)+abs(sy-ey)+1; // body length
    int hidx = 0, tidx = L-1; // head index; tail index
    {
        int dx = sx < ex ? 1 : (sx > ex ? -1 : 0);
        int dy = sy < ey ? 1 : (sy > ey ? -1 : 0);
        for (int i = 0; i < L; i++) {
            g[sx][sy] = 1;
            bp[i][0] = sx, bp[i][1] = sy, sx += dx, sy += dy;
        }
    }
    scanf("%d", &q); // how many commands
 
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    while (q--) {
        scanf("%d", &cmd);
        int cx = bp[tidx][0], cy = bp[tidx][1];
        g[cx][cy] = 0;
        tidx--;
        if (tidx < 0)
            tidx = L-1; // save the coordinates in a circular way

        int tx = bp[hidx][0], ty = bp[hidx][1];
        tx += dx[cmd], ty += dy[cmd];  // head moves

        if (tx < 0 || ty < 0 || tx >= n || ty >= m || g[tx][ty]) { //the move is illegal
            g[cx][cy] = 1; // the tail gets back
            break;
        }
        hidx--;
        if (hidx < 0)
            hidx = L-1;
        bp[hidx][0] = tx, bp[hidx][1] = ty;
        g[tx][ty] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            //printf("%d", g[i][j]);   // change ASCII into int directly
            putchar(g[i][j]+'0'); 
            // g[i][j] saves ASCII, so we add '0' to print the real char number
        puts("");
    }
    return 0;
}