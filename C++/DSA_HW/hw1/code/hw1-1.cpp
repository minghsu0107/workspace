#include <bits/stdc++.h>
using namespace std;
#define MAX 200001
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0) 
char _;
int arr[MAX];
/*
void insertion(vector<int> &v, int n) {
	int x = v.back();
	int j = n - 2;
	while (j >= 0 && v[j] > x) {
		v[j + 1] = v[j];
		j--;
	}
	v[j + 1] = x;
}
*/
int main() {
	//cin.tie(0),ios::sync_with_stdio(0);
	int n, m, k, tmp;
	scan(n);
	scan(m);
	scan(k);
	vector<int> v;
	for (int i = 0; i < n; ++i) {
		scan(tmp);
		arr[i] = tmp;
	}
	for (int i = 0; i < m; ++i) {
		v.push_back(arr[i]);		
	}
	sort(v.begin(), v.end());
	printf("%d\n", v[k-1]);
	int idx = 0;
	for (int i = 0; i < n - m; ++i) {
		v.erase(lower_bound(v.begin(), v.end(), arr[idx]));
		v.insert(lower_bound(v.begin(), v.end(), arr[idx + m]), 1, arr[idx + m]);
		//v.emplace_back(arr[idx + m]);
		//insertion(v, m);
		printf("%d\n", v[k-1]);
		++idx;
	}
	return 0;
}