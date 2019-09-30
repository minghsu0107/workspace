#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define N 200001

double arr[N];
inline void write(int x)
{
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

int main() {
	tree<pair<int,int>,null_type,less<pair<int,int> >,rb_tree_tag,tree_order_statistics_node_update> t;
	int n, m, k;
    ret(n, m, k);
    
    for (int i = 0; i < n; ++i) ret(arr[i]); 
    for (int i = 0; i < m; ++i) t.insert(make_pair(arr[i], i));

    for (int i = m; i < n; ++i) {
    	write(t.find_by_order(k-1)->first), puts("");
    	t.insert(make_pair(arr[i], i));
        t.erase(make_pair(arr[i - m], i - m));
    }
    write(t.find_by_order(k-1)->first), puts("");
    return 0; 

}