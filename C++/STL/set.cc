#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

// using R-B tree

int main() {
   set<int> s;
   set<int> s1(s); // copy constructor
   for (int i = 0; i < 10; i++) {
   	   s.insert(i); // O(log size)

   }
   for (auto x: s) cout << x << " ";
   cout << endl;

   s.insert(9); // nothing happens
   
   // s.erase(K k) returns the number of elements erased (0 or 1 in set)
   // s.count(K k) returns the number of elements whose key == k (0 or 1 in set)
   cout << s.erase(6) << endl;
   // O(log size) 
   // amortized O(1), if erasing multiple elements, then O(C), C == const
   cout << s.count(6) << endl; // O(log size)

   set<int>::iterator it = s.find(8); // O(log size), if can't find, return s.end()
   cout << *it << endl;
   
   // for sorted data
   set<int>::iterator l = s.lower_bound(3); // O(log size)
   set<int>::iterator u = s.upper_bound(3); // O(log size)
   for (auto i = l; i != u; i++) {
   	   cout << *i << endl;
   }

   set<int> a, b, c1, c2, c3;
   a.insert({1, 2, 3, 4});
   b.insert({3, 4, 5, 6});

   // following 4 functions are only for sorted data
   // directly output the result with a " " between
   set_union(a.begin(), a.end(), b.begin(), b.end(), ostream_iterator<int>(cout," "));
   cout << endl;
   set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c1, c1.begin()));
   // a - b
   set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c2, c2.begin()));
   // a XOR b
   set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c3, c3.begin()));

   for (auto x: c1) cout << x << " ";
   cout << endl;
   for (auto x: c2) cout << x << " ";
   cout << endl;
   for (auto x: c3) cout << x << " ";
   cout << endl;
}
/*
自平衡二元查找樹，可以O(logn)
插入、刪除或查詢一個值有沒有在其中
*/