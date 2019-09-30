#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
struct LessThan7 {
    bool operator()(int i) const { return i < 7; }
    typedef int argument_type;
};
/*
struct LessThan7 : std::unary_function<int, bool>
{
    bool operator()(int i) const { return i < 7; }
};
*/
int main()
{
    vector<int> v({3, 4, 5, 7, 10});
 
    cout << count_if(begin(v), end(v), not1(LessThan7())) << "\n";
 
    //same as above, but using std::function
    std::function<bool(int)> less_than_9 = [](int x){ return x < 9; };
    std::cout << count_if(begin(v), end(v), not1(less_than_9)) << "\n";
    // lambda expression
    std::cout << count_if(begin(v), end(v), [](int x){ return x < 5; }) << "\n";
}