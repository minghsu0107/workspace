// copy_backward example
#include <iostream>     // std::cout
#include <algorithm>    // std::copy_backward
#include <vector>       // std::vector

// Copies the elements in the range [first,last) 
// starting from the end into the range terminating at result.

int main () {
  std::vector<int> myvector;

  // set some values:
  for (int i=1; i<=5; i++)
    myvector.push_back(i*10);          // myvector: 10 20 30 40 50

  myvector.resize(myvector.size()+3);  // allocate space for 3 more elements

  std::copy_backward ( myvector.begin(), myvector.begin()+5, myvector.end());

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  // every element shifts right for 3 units
  return 0;
}