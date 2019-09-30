#include <iostream>
#include <set>
#include <map>
using namespace std;

// using R-B tree

int main() {
    multiset<int> s;
    for (int i = 0; i < 5; i++) s.insert(i);
    s.insert({2, 2, 3});

    for (int x: s) cout << x << " ";
    cout << endl;
    
    cout << s.erase(3) << endl;
    cout << s.count(3) << endl;

    for (int x: s) cout << x << " ";
    cout << endl;
    
    auto ans = s.equal_range(2);
    auto l = ans.first;
    auto u = ans.second;
    for (auto i = l; i != u; i++)
    	cout << *i << " ";
    cout << endl;

    multimap<int, int> m;
    for (int i = 0; i < 5; i++) 
    	m.insert(make_pair(i, i + 10));
    m.insert(make_pair(2, 22));
    m.insert(make_pair(2, 32));

    auto ans1 = m.equal_range(2);
    auto l1 = ans1.first;
    auto u1 = ans1.second;
    for (auto i = l1; i != u1; i++)
    	cout << i->first << " " << i->second << endl;
}