#include <bits/stdc++.h>
using namespace std;
#define N 1000005
int arr[N];
priority_queue<int, vector<int>, less<int> > p;
priority_queue<int, vector<int>, greater<int> > q;
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
int get_kth(int x, int idx) {
	if (p.size() <= idx) {
		if (p.empty())
			p.push(x);
		else {
			q.push(x);
			p.push(q.top());
			q.pop();
			/*
			if (x > p.top()) {
				q.push(x);
				p.push(q.top());
				q.pop();
			}
			else
				p.push(x);
			*/
		}
	}
	else {
		p.push(x);
		q.push(p.top());
		p.pop();
		/*
		if (x < p.top()) {
			q.push(p.top());
			p.pop();
			p.push(x);
		}
		else {
			q.push(x);
		}
		*/
	}
	return p.top();
}
int main() {
    int t, n, k;
    ret(t);
    while (t--) {
        ret(n, k);
        for (int i = 0; i < n; ++i) ret(arr[i]);
        unsigned long long sum = 0;
    	priority_queue<int, vector<int>, less<int> > tmp1;
		priority_queue<int, vector<int>, greater<int> > tmp2;
    	p = tmp1;
    	q = tmp2;
        for (int i = 0; i < n; ++i) {
            sum += (i + 1) * get_kth(arr[i], i/k);
        }
        printf("%lld\n", sum % (1LL<<32));
    }
    return 0;
}