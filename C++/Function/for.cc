#include <bits/stdc++.h>
using namespace std;
// function object type
struct myclass {
    void operator()(int i) {cout << i << " ";}
} myobject;

void myFunction(int &i) {
	 i += 1;
}

void print_i(int t, std::string separator)
{
   std::cout << t << separator;
}

int main() {
	vector<int> v({1, 2, 3, 4, 5});
	for_each(v.begin(), v.end(), myFunction);
	for_each(v.begin(), v.end(), myclass()); 
    // myclass() is a functor(a class where () is reloaded)
    // or for_each(v.begin(), v.end(), myobject);
	cout << endl;

    std::string delim = "\n";
    for_each(v.begin(), 
             v.end(),
            std::bind2nd(std::ptr_fun(print_i),delim));
    cout << endl;

    for_each(v.begin(), 
             v.end(),
            std::bind2nd(std::ref(print_i),delim));
}