#include <bits/stdc++.h>
using namespace std;

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
   for (int i = 0; i < v.size(); ++i) os << v[i] << " ";
   return os;
}
template <typename T>
ostream& operator<< (ostream& os, const set<T>& v) {
   for (typename set<T>::iterator it = v.begin(); it != v.end(); it++) 
       os << *it << " ";
   return os;
}
int main() {
	vector<int> a{1, 2, 3};
   set<string> b{"1", "2", "3"};
   cout << a;
   cout << endl;
   cout << b;
   return 0;
}