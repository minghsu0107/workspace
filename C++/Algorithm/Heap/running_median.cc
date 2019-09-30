#include <bits/stdc++.h>
using namespace std;
int n, a, b, x;
priority_queue<int, vector<int>, less<int> > max_hp;
priority_queue<int, vector<int>, greater<int> > min_hp;
int main() {
	cin >> n;
	cin >> a >> b;
	cout << a << endl;
    int cur = (float)(a + b)/2;
    cout << cur << endl;
	if (a > b) swap(a, b);
	max_hp.push(a);
	min_hp.push(b);
	for (int i = 2; i < n; i++) {
		// insert
		cin >> x;
		if (x > cur) min_hp.push(x);
		else max_hp.push(x);

		//maintain
		if (max_hp.size() > min_hp.size() + 1) {
			int k = max_hp.top();
			max_hp.pop();
			min_hp.push(k);
		}
		else if (min_hp.size() > max_hp.size() + 1) {
			int k = min_hp.top();
			min_hp.pop();
			max_hp.push(k);
		}

		// get median
		if (max_hp.size() > min_hp.size())
			cout << max_hp.top() << endl;
		else if (max_hp.size() < min_hp.size())
			cout << min_hp.top() << endl;
		else
			cout << (float)(max_hp.top() + min_hp.top())/2 << endl;
	}
	return 0;
}