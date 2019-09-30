#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[] = {1, 2, 100, 200, 3, 4, 100, 300};

    vector<int> arr(a, a + 4), arr2(a + 4, a + 8);
    vector<int>::iterator pend;
    // remove all elements smaller than 100
    pend = remove_if( arr.begin(),  arr.end(),
                      bind2nd(less< int>(), 100));
    for (auto it = arr.begin(); it != pend; ++it) 
    	cout << *it << " ";
    cout << endl;
    // remove all elements greater than 100
    pend = remove_if( arr2.begin(),  arr2.end(),
                    bind1st(less< int>(), 100));
    for (auto it = arr2.begin(); it != pend; ++it) 
    	cout << *it << " ";
    cout << endl;
}
/*
remove:
The function cannot alter the properties of the object 
containing the range of elements 
(i.e., it cannot alter the size of an array or a container).
*/