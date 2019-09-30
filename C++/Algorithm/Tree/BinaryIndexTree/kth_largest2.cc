// (logn)^2
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 200010;
int pre[maxn], c[maxn], a[maxn]; // a[x] = 組別x的大小
// BIT維護組別大小為i (1 <= i <= n) 的出現次數
int n, m;
int find(int x) {
    return x == pre[x]? x : pre[x] = find(pre[x]);
}
int lowbit(int x) {
    return x&(-x);
}
void update(int x,int v) {
    for (;x <= n; x += lowbit(x))
        c[x] += v;
}
int count(int x) {
    int ret = 0;

    while (x > 0) {
        ret += c[x];
        x -= lowbit(x);
    }

    return ret; // 組數前綴和(大小<=x的組別的次數總和)
}
int search(int x) {
    int l = 1, r = n;
    if(x <= count(1)) return 1;

    while(l < r) {
        int mid = (l + r)>>1;

        if(x <= count(mid)) r = mid;
        else  l = mid + 1;
    }
    return l;
}
int main() {
    int k, x, y, group_num;
    scanf("%d%d",&n, &m);
    for (int i = 1; i <= n; i++) {
        pre[i] = i;
        a[i] = 1;
    }
    group_num = n;
    update(1, n);  //初始組別大小爲1的數有n個   
    int p;
    for (int i = 0; i < m; i++) {
        scanf("%d", &p);
        if (p == 0) {
            scanf("%d%d", &x, &y);
            x = find(x);
            y = find(y);
            if(x == y) continue;

            update(a[x], -1); //組別大小爲a[x]的次數 -=1
            update(a[y], -1); //組別大小爲a[y]的次數 -=1
            update(a[x] + a[y], 1); //組別大小爲a[x]+a[y]的次數 -=1

            pre[y] = x;
            a[x] += a[y];
            group_num--;
        }
        else {
            scanf("%d", &k);
            k = group_num - k + 1;  //轉換爲求第k小
            printf("%d\n", search(k));
        }
    }
    return 0;
}