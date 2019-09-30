#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define N 1000010
#define INF 2e9 + 10
typedef long long ll;

ll arr[N];
ll f[N];
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
	int n;
    ll cnt = 0;
	ret(n);
	for (int i = 0; i < n; ++i) ret(arr[i]);
	for (int i = 0; i < n; ++i) ret(f[i]);
    
	tree<ll,null_type,less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update> t;
    t.insert(arr[0]);
	for (int i = 1; i < n; ++i) {
       
		ll l = arr[i] - f[i];
        ll r = arr[i] + f[i] + 1;

        cnt += t.order_of_key(r) - t.order_of_key(l);

        t.insert(arr[i]);
    }
    printf("%lld\n", cnt);
    return 0;
}