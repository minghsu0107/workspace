#include <stdio.h>
long long int D, a, b, c, A, B, C;
int dir[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
int flag = 0;
int judge(long long int a, long long int b, long long int c, long long int d) {
    int k = 0;
    if (d < 0) return 0;
    if (!flag && d == 0) {
        flag = 1;
        return 1;   
    }
    for (int i = 0; i < 3 && !flag; i++) {
        if (a - dir[i][0] >= 0 && b - dir[i][1] >= 0 && c - dir[i][2] >= 0) {
              k += judge(a - dir[i][0], b - dir[i][1], c - dir[i][2], d - A*dir[i][0] - B*dir[i][1] - C*dir[i][2]);
        }
    }
    return k;
}
int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%lld%lld%lld%lld%lld%lld%lld", &D, &a, &b, &c, &A, &B, &C);
        if (judge(a,b,c,D)) printf("yes\n");
        else printf("no\n");
        flag = 0;
    }
    return 0;
}
