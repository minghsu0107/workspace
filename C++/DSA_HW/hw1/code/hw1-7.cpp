#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define lowbit(x) (x&-x)
 
using namespace std;
 
void rit(int &n)
{
    char c;
    while(!isdigit(c=getchar()));
    n=c-'0';
    while(isdigit(c=getchar()))
        n=n*10+c-'0';
}
 
vector<int> bit;
 
void mod(int x,int v) {
    while(x < bit.size()) {
        bit[x] += v;
        x += lowbit(x);
    }
}
 
int sum(int x) {
    int ret = 0;
    while(x) {
        ret += bit[x];
        x -= lowbit(x);
    }
    return ret;
}
 
int query(int k) {
    int l = 1, r = bit.size() - 1, m;
    while(l < r) {
        int m = (l + r)>>1;
        if(k <= sum(m))
            r = m;
        else
            l = m + 1;
    }
    return l;
}
 
int main() {
    cin.tie(0),ios::sync_with_stdio(0);
    int n, m, k;
    rit(n), rit(m), rit(k);
    vector<int> arr(n), sorted(n);
    for(int i = 0; i < n; ++i)
        rit(arr[i]);
    sorted = arr;
    sort(sorted.begin(),sorted.end());
    sorted.resize(unique(sorted.begin(),sorted.end())-sorted.begin());
    for(int i = 0; i < n; ++i)
        arr[i]=lower_bound(sorted.begin(),sorted.end(),arr[i])-sorted.begin()+1;
    bit.resize(sorted.size() + 1, 0);
    for(int i = 0; i < m; i++)
        mod(arr[i], 1);
    cout << sorted[query(k) - 1] << '\n';
    for(int i = m; i < n; ++i) {
        mod(arr[i - m], -1);
        mod(arr[i], 1);
        cout << sorted[query(k) - 1] << '\n';
    }
    return 0;
}
// k starts from 1
// bit maintains the number of occurrence 
// of each descritizated element (from 1 to n)
// bit[x] == 大小<=x的數字的出現次數總和 (x已離散化)
// 也就是<=x的數字的總個數
// query(k) returns x, 
// where x is the lower bound such that bit[x] >= k
// since x is descritizated, x - 1 is the index of sorted