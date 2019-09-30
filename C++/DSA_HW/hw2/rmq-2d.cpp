#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int mp[255][255];
int dpmin[255][255][8][8];  ///2^8=256
int dpmax[255][255][8][8];
///dp[x][y][i][j]表示从（x,y）点到右下角为(x+2^i-1,y+2^i-1)矩形内的最值
void RMQ(int n,int m) {
    for(int i = 0; (1<<i) <= n; i++) {
        for(int j = 0; (1<<j) <= m; j++) {
            if(!i && !j) continue;
            for(int r = 1; r + (1<<i) - 1 <= n; r++) {
                for(int c = 1; c + (1<<j) - 1 <= m; c++) {
                    if(i != 0 && j == 0) {
                        dpmax[r][c][i][j] = max(dpmax[r][c][i-1][j], dpmax[r+(1<<(i-1))][c][i-1][j]);
                        dpmin[r][c][i][j] = min(dpmin[r][c][i-1][j], dpmin[r+(1<<(i-1))][c][i-1][j]);
                    }
                    else {
                        dpmax[r][c][i][j] = max(dpmax[r][c][i][j-1], dpmax[r][c+(1<<(j-1))][i][j-1]);
                        dpmin[r][c][i][j] = min(dpmin[r][c][i][j-1], dpmin[r][c+(1<<(j-1))][i][j-1]);
                    }
                }
            }
        }
    }
}
//以点(lx,ly)为左上角(rx,ry)为右下角矩形区域内最大值查询
int querymax(int lx, int ly, int rx, int ry) {
    int kx = 0, ky = 0;
    while(lx + (1<<(1+kx)) - 1 <= rx) kx++;
    while(ly + (1<<(1+ky)) - 1 <= ry) ky++;
    int m1 = dpmax[lx][ly][kx][ky];
    int m2 = dpmax[rx-(1<<kx)+1][ly][kx][ky];
    int m3 = dpmax[lx][ry-(1<<ky)+1][kx][ky];
    int m4 = dpmax[rx-(1<<kx)+1][ry-(1<<ky)+1][kx][ky];
    return max(max(m1, m2), max(m3, m4));
}
int querymin(int lx, int ly, int rx, int ry) {
    int kx = 0, ky = 0;
    while(lx + (1<<(1+kx)) - 1 <= rx) kx++;
    while(ly + (1<<(1+ky)) - 1 <= ry) ky++;
    int m1 = dpmin[lx][ly][kx][ky];
    int m2 = dpmin[rx-(1<<kx)+1][ly][kx][ky];
    int m3 = dpmin[lx][ry-(1<<ky)+1][kx][ky];
    int m4 = dpmin[rx-(1<<kx)+1][ry-(1<<ky)+1][kx][ky];
    return min(min(m1, m2),min(m3, m4));
}
int main() {
    int n, b, k, x, y;
    scanf("%d%d%d", &n, &b, &k);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &mp[i][j]);
            dpmax[i][j][0][0] = mp[i][j];
            dpmin[i][j][0][0] = mp[i][j];
        }
    }
    RMQ(n, n);
    while(k--) {
        scanf("%d%d",&x, &y);
        printf("%d\n", querymax(x,y,x+b-1,y+b-1) - querymin(x,y,x+b-1,y+b-1));
    }
    return 0;
}

/*
O（n*n*logn*logn）
query: O(1)
*/