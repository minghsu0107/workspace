#include <bits/stdc++.h>
using namespace std;
#define N 200001
#define INF 2e9 + 10

int arr[N];
typedef pair<int, int> proot; 
struct node {
    int val, pri, son[2]; 
    int sz, num; 
    void init(int _val, int _pri, int _sz, int _num) {
        val = _val, pri = _pri, sz = _sz, num = _num; 
        son[0] = son[1] = 0; 
    } 
}tr[N]; 
int tot, root; 
inline void init() { 
    tot = 0, root = 0; 
    tr[0].init(0, 0, 0, 0); 
} 
inline void update(int x) { 
    tr[x].sz = tr[tr[x].son[0]].sz + tr[tr[x].son[1]].sz + tr[x].num; 
} 
inline void Rotate(int &x, int p) { //p=0左旋，p=1右旋  
    int y = tr[x].son[!p]; 
    tr[x].son[!p] = tr[y].son[p]; 
    tr[y].son[p] = x; 
    update(x); update(y); //必须先更新x后更新y 
    x = y; 
} 
inline void Insert(int &x, int val) { 
    if (x == 0) tr[x = ++tot].init(val, rand(), 1, 1); 
    else { 
        tr[x].sz++; 
        if (tr[x].val == val) { 
            tr[x].num++; 
            return; 
        } 
        int p = val > tr[x].val; 
        Insert(tr[x].son[p], val); 
        if(tr[x].pri < tr[tr[x].son[p]].pri) Rotate(x, !p); 
    } 
} 
inline void del(int &x, int val) { //删除之前可以先查看一下这个值是否存在 
    //if(x == 0) return; 
    if (tr[x].val == val) { 
        if (tr[x].num > 1) { 
            tr[x].sz--; 
            tr[x].num--; 
            return; 
        } 
        if (tr[x].son[0] && tr[x].son[1]) { 
            int p = tr[tr[x].son[0]].pri > tr[tr[x].son[1]].pri; 
            Rotate(x, p); tr[x].sz--;   //如果接下删除tr[x].son[p]，注意处理tr[x].sz，因为这个一直TLE 
            del(tr[x].son[p], val);  
        } else { 
            if (tr[x].son[0] != 0) x = tr[x].son[0]; 
            else x = tr[x].son[1]; 
        } 
    } else { 
        int p = val > tr[x].val; 
        tr[x].sz--; 
        del(tr[x].son[p], val); 
    } 
} 
inline int get_kth(int x, int k) { 
    //if(x == 0) return 0; 
    if (k > tr[tr[x].son[0]].sz + tr[x].num) 
        return get_kth(tr[x].son[1], k - tr[tr[x].son[0]].sz - tr[x].num); 
    else if (k <= tr[tr[x].son[0]].sz) 
        return get_kth(tr[x].son[0], k); 
    else return tr[x].val; 
} 
inline int get_rank(int x, int val) { 
    //if(x == 0) return 0; 
    if (val == tr[x].val) return tr[tr[x].son[0]].sz + 1; 
    else if (val > tr[x].val) 
        return get_rank(tr[x].son[1], val) + tr[tr[x].son[0]].sz + tr[x].num; 
    else return get_rank(tr[x].son[0], val); 
} 
//求前驱和后继用两种不同的方法，其实一种即可 
// the largest value that is smaller than val
inline int get_prec(int x, int val) { 
    int ans = -INF; 
    while(x) { 
        if (val <= tr[x].val) x = tr[x].son[0]; 
        else ans = max(ans, tr[x].val), x = tr[x].son[1]; 
    } 
    return ans; 
} 
// the smallest value that is larger than val
inline int get_succ(int x, int val) { 
    if(! x) return INF; 
    if(val >= tr[x].val) return get_succ(tr[x].son[1], val); 
    else return min(tr[x].val, get_succ(tr[x].son[0], val)); 
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
    int n, m, k;
    ret(n, m, k);
    
    for (int i = 0; i < n; ++i) ret(arr[i]);
    init(); 
    for (int i = 0; i < m; ++i) {
        Insert(root, arr[i]);
    }
    printf("%d\n", get_kth(root, k));
    for (int i = m; i < n; ++i) {
        del(root, arr[i - m]);
        Insert(root, arr[i]);
        printf("%d\n", get_kth(root, k));
    }
    return 0; 
}
