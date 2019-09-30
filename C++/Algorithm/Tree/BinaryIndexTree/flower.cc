/*
hdu 4325 树状数组+离散化
题目大意：给定n朵花，每朵花开放的时间段，然后m个询问：ti时间点有多少花正在盛开
解题思路：裸树状数组，不过要离散化花开放的时间
The first line contains a single integer t (1 <= t <= 10), the number of test cases.
For each case, the first line contains two integer N and M, where N (1 <= N <= 10^5) is the number of flowers, and M (1 <= M <= 10^5) is the query times. 
In the next N lines, each line contains two integer Si and Ti (1 <= Si <= Ti <= 10^9), means i-th flower will be blooming at time [Si, Ti].
In the next M lines, each line contains an integer Ti, means the time of i-th query.
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 300005;
 
int n, m, k;
int C[maxn] ,a[maxn];
 
struct note {
    int x, id;
    bool operator <(const note &other)const {
        return x < other.x;
    }
}p[maxn];
 
int lowbit(int i) {
    return i&(-i);
}
 
int sum(int x) {
    int cnt = 0;
    while(x) {
        cnt += C[x];
        x -= lowbit(x);
    }
    return cnt;
}
 
void update(int pos,int value) {
    while (pos <= k) {
        C[pos] += value;
        pos += lowbit(pos);
    }
}
int main() {
    int T, tt = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int nn = n * 2;
        int mm = nn + m;

        for (int i = 0; i < mm; i++) {
            scanf("%d", &p[i].x);
            p[i].id = i;
        }
        sort(p, p + mm);
        k = 1;
        a[p[0].id] = k;
        for (int i = 1;i < mm; i++) {
            if (p[i].x == p[i-1].x) {
                a[p[i].id] = k;
            }
            else
                a[p[i].id]=++k;
        }
        
        // now a[i] = discretizated time point(start from 1)
        // i = 0~1 is the interval of the first flower
        // i = 2~3 is the interval of the second flower
        //   ...
        // i = nn-2 ~ nn-1
        memset(C, 0, sizeof(C));
        for (int i = 0; i < nn - 1; i += 2) {
            update(a[i], 1);
            update(a[i+1] + 1, -1);
        }
        printf("Case #%d:\n", ++tt);
        for (int i = nn; i < mm; i++) {
            printf("%d\n", sum(a[i]));
        }
    }
    return 0;
}
/*
這題可以看成是樹狀陣列的區間更新，給出每一朵花開放的時間範圍，
就相當於做一次區間更新，這個範圍內的每個點加1，直接使用樹狀陣列區間更新的模板就好了。
可是這題有個問題，那就是花開放範圍的資料極大（1-10^9），
無法直接開陣列儲存每一個點。那怎麼辦呢，很明顯需要用到資料的離散化。
我們可以發現，雖然花開放範圍極大，但是總共只有n朵花，n最大是10^5，
每一個範圍由兩個數l，r組成，再加上最多10^5個查詢數，
也就意味著一組資料最多出現3*（10^5）個不同的資料，陣列完全能夠存下。
而且我們判斷花是否在某一時刻開放，只需要知道數與數之間的相對大小，
而不需要在意具體數值（某一時刻在 l , r之間，即花是開的），所以，這就滿足了離散化的條件。
我們對每一朵花開放的範圍進行離散化，也對查詢的時刻進行離散化，
這樣，就不會改變他們的相對大小。然後使用樹狀陣列區間更新+單點查詢即可。
離散化的方法：將所有出現的數存入陣列，去除重複出現的數，再進行排序，
排序後這個數在陣列中對應的下標，即為其離散化之後的數值。 
*/