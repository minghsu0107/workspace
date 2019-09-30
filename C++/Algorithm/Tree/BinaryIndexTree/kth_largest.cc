#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 200010;
int pre[maxn], c[maxn], a[maxn]; // a[x] = 大小為x的組別的組數
int n, m;
int find(int x) {
    return x == pre[x]? x : pre[x] = find(pre[x]);
}
int lowbit(int x) {  //x二進制末尾 1 所表示的數
    return x&(-x);
}
void update(int x,int v) {//更新樹狀數組 往x的二進制數後加零
    for ( ;x <= n;x += lowbit(x))  //從第二次循環開始，每循環一次就在二進制數後加個零
        c[x] += v;
}
// if cnt == 2^n, then c[cnt] maintains the sum from 1 to cnt
int search(int k) {
    int cnt = 0, ans = 0;
    for (int i = 20; i >= 0; i--) { //利用二進制的思想，把答案用一個二進制數來表示
        cnt += (1<<i);
        if (cnt >= n || ans + c[cnt] >= k)
        //這裏大於等於k的原因是可能會有很多個數都滿足ans + c[cnt] >= k，所以找的是最大的滿足ans+c[cnt]<k的cnt
            cnt -= (1<<i);
        else
            ans += c[cnt];  //ans用來累加比當前cnt小的總組數
    }
    //求出的cnt是累加和（即小於等於cnt的數的個數）小於k的情況下cnt的最大值，所以cnt+1就是第k大的數
    return cnt + 1;
}
int main() {
    int k, x, y, group_num;
    scanf("%d%d",&n, &m);
    for (int i = 1;i <= n; i++) {
        pre[i] = i;
        a[i] = 1;
    }
    group_num = n;
    update(1, n);  //初始狀態值爲1的數有n個   
    int p;
    for (int i = 0; i < m; i++) {
        scanf("%d", &p);
        if (p == 0) {
            scanf("%d%d", &x, &y);
            x = find(x);
            y = find(y);
            if(x == y) continue;
            update(a[x], -1);
            update(a[y], -1);
            update(a[x] + a[y], 1);
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