#include <bits/stdc++.h>
using namespace std;
#define MAX 200001
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;

int arr[MAX];
typedef pair<int, int> proot; 

struct node { 
	int l, r, val, pri, sz; 
	void init(int _val, int _pri, int _sz) {
		val = _val, pri = _pri, sz = _sz; l = r = 0; 
	} 
} tr[MAX];

int root, tot;

void init() { 
	root = 0, tot = 0; 
	tr[0].init(0, 0, 0); 
} 
int new_node(int val) { 
	tr[++tot].init(val, rand(), 1); 
	return tot; 
} 
void update(int x) { 
	tr[x].sz = 1 + tr[tr[x].l].sz + tr[tr[x].r].sz; 
} 
proot split(int x, int k) {//把树x分裂成两个树，前k个元素一个，剩余的元素一个树 
	if (! k) return proot(0, x); 
	proot y; 
	if (tr[tr[x].l].sz >= k) { 
		y = split(tr[x].l, k);
		tr[x].l = y.second; 
		update(x); 
		y.second = x; 
	} else { 
		y = split(tr[x].r, k - tr[tr[x].l].sz - 1); 
		tr[x].r = y.first;
		update(x); 
		y.first = x; 
	} 
	return y; 
} 
int Merge(int x, int y) {//把树x,y合并成一棵，并返回树根
	if (!x || !y) return x + y; 
	if (tr[x].pri < tr[y].pri) { 
		tr[x].r = Merge(tr[x].r, y); 
		update(x); 
		return x; 
	} else { 
		tr[y].l = Merge(x, tr[y].l); 
		update(y); 
		return y; 
	} 
} 
bool Find(int x, int val) {
	if (!x) return false; 
	if(val == tr[x].val) return true; 
	else if(val < tr[x].val) return Find(tr[x].l, val); 
	else return Find(tr[x].r, val); 
} 
/*
int get_rank(int x, int val) {// when there are all unique keys
	if (!x) return 0; 
	if (val == tr[x].val) return tr[tr[x].l].sz + 1;
	else if(val < tr[x].val) return get_rank(tr[x].l, val);
	else return tr[tr[x].l].sz + 1 + get_rank(tr[x].r, val);
} 
*/
int get_rank(int x, int val) { // (rank start from 1(smallest))
	if(!x) return 0; 
	return val <= tr[x].val ? get_rank(tr[x].l, val) : get_rank(tr[x].r, val) + tr[tr[x].l].sz + 1; 
} 
// k starts from 1
int get_kth(int x, int k) { 
	if(tr[tr[x].l].sz + 1 == k) return tr[x].val; 
	else if(k <= tr[tr[x].l].sz) return get_kth(tr[x].l, k); 
	else return get_kth(tr[x].r, k - tr[tr[x].l].sz - 1); 
} 
void Insert(int val) { //插入元素。首先确定新元素的排名，然后依据这个排名把树分裂成两个，然后把新元素夹在两个树中间，合并 
	int k = get_rank(root, val)+1; 
	proot x = split(root, k-1); 
	int y = new_node(val); 
	root = Merge(Merge(x.first, y), x.second); 
} 
void del(int val) { //删除元素。首先确定元素排名k，然后前k-1个分裂成一个树，剩余的元素再进行一次分裂，把第一个也就是待删除元素单独分裂出来，然后合并即可
	int k = get_rank(root, val) + 1; 
	proot x = split(root, k-1); 
	proot y = split(x.second, 1); 
	root = Merge(x.first, y.second); 
} 
int get_prec(int root, int val) { 
	int k = get_rank(root, val); 
	proot x = split(root, k-1); 
	proot y = split(x.second, 1); 
	int ans = tr[y.first].val; 
	root = Merge(Merge(x.first, y.first), y.second); 
	return ans; 
} 
int get_succ(int root, int val) { 
	int k = get_rank(root, val) + 1; 
	proot x = split(root, k); 
	proot y = split(x.second, 1); 
	int ans = tr[y.first].val; 
	root = Merge(Merge(x.first, y.first), y.second); 
	return ans; 
} 
int main() { 

	int n, m, k, tmp;
	scan(n);
	scan(m);
	scan(k);
	
	for (int i = 0; i < n; ++i) scan(arr[i]); 
	init(); 
	for (int i = 0; i < m; ++i) {
		Insert(arr[i]);
	}
	printf("%d\n", get_kth(root, k));
    for (int i = m; i < n; ++i) {
        del(arr[i - m]);
        Insert(arr[i]);
        printf("%d\n", get_kth(root, k));
    }
    return 0;
}
