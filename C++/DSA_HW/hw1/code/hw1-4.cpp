#include <bits/stdc++.h>
using namespace std;
#define MAX 200005
#define _for(i, a, b) for(int i=(a); i<(b); ++i)
int arr[MAX], n, m, k;
inline int read() {
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x) {
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
template <typename T>
inline bool ret(T& x) {
    char c = 0; bool flag = false;
    while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
    c == '-' ? (flag = true, x = 0) : (x = c - '0');
    while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
    if (flag) x = -x;
    return true;
}
template <typename T, typename ...Args>
inline bool ret(T& x, Args& ...args) { return ret(x) && ret(args...); }

int main(){
    int n, m, k;
    ret(n, m, k);
    multiset<int> ms;
    _for(i, 0, n) arr[i] = read();
    _for(i, 0, m) ms.insert(arr[i]);
    int cnt = 0;
    auto it = ms.begin();
    for(; cnt < k - 1; it++) cnt++;
    write(*it), puts("");

    _for(i, m, n) {
        ms.insert(arr[i]);
        if(arr[i] < *it) it--;
        if(arr[i - m] <= *it) it++;
        ms.erase(ms.lower_bound(arr[i - m]));
        write(*it), puts("");
    }
}