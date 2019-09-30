// elements are unique
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7; 
struct Node { 
	int v, id; 
	bool operator < (const Node a) const { 
		return  v < a.v; 
	} //排序用 
}a[N]; 
int n, rank[N]; 
int main() { 
	cin >> n; 
	for (int i = 0; i < n; i++){ 
		cin >> a[i].v;
		a[i].id = i;
	} 
	sort(a, a + n); 
	for (int i = 0; i < n; i++) 
		rank[a[i].id] = i; 
	for (int i = 0; i < n; i++)
		cout << rank[i] << " ";
	cout << endl;
	return 0;
}
