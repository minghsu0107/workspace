#include <bits/stdc++.h>
#define _for(i, a, b) for(int i=(a); i<(b); ++i)
#define _rep(i, a, b) for(int i=(a); i<=(b); ++i)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
using namespace std;

int main() {
	vector<int> b;
	_for (i, 0, 3) { b.push_back(i); }
	_for (i, 0, 3) { cout << b[i] << " "; }
	cout << endl;

	vector<int> v = {4, 5, 6, 4, 8};
    rep (it, end(v), begin(v)) {
        cout << *it << ' ';
    }
    cout << endl;

    rep (it, begin(v), end(v)) {
        cout << *it << ' ';
    }
}
