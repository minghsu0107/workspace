// find_if example
#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
#include <functional>   // std::ref
using namespace std;

bool IsOdd (int i) {
  return ((i%2)==1);
}
bool IsMatch(int a, int b) {
  return (a == b);
} 
int main () {
  std::vector<int> myvector;

  myvector.push_back(10);
  myvector.push_back(25);
  myvector.push_back(40);
  myvector.push_back(55);

  std::vector<int>::iterator it 
  = std::find_if (myvector.begin(), myvector.end(), IsOdd);

  std::vector<int>::iterator it2 
  = std::find_if (myvector.begin(), myvector.end(), bind2nd(ptr_fun(IsMatch), 40));

  std::vector<int>::iterator it3 
  = std::find_if (myvector.begin(), myvector.end(), bind2nd(ref(IsMatch), 55));

  std::cout << "The first odd value is " << *it << '\n';
  std::cout << *it2 << '\n';
  std::cout << *it3 << '\n';
  return 0;
}