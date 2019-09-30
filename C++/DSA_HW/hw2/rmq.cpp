#include<stdio.h>  // poj 3264
#include<math.h>
#define max(x,y)  ((x)>(y)?(x):(y))
#define min(x,y)  ((x)<(y)?(x):(y))
int r[50010][50],s[50010][50]; int a[50010];
int n, q, u, v, p, maxh, minh;

void initial()
{
    for (int i = 1; i <= n; i++)
        r[i][0] = s[i][0] = a[i];
    for (int j = 1; (1<<j) <= n; j++) {
        for(int i = 1; i + (1<<j) - 1 <= n; i++) {
            r[i][j] = min( r[i][j-1],r[i+(1<<(j-1))][j-1] );
            s[i][j] = max( s[i][j-1],s[i+(1<<(j-1))][j-1] );
        }
    }
}
void solve() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a+i);
    initial();
    for (int i = 1; i <= q; i++) {
        scanf("%d%d",&u, &v);
        int j = (v - u + 1);
        int k = int(log10((double)j) / log10(2.0));
        minh = min( r[u][k], r[v-(1<<k)+1][k] );
        maxh = max( s[u][k], s[v-(1<<k)+1][k] );
        printf("%d %d\n", maxh, minh);
    }
}  
int main() {
    solve();
    return 0;
}