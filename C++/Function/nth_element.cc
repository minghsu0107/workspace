// nth_element example
#include <iostream>     // std::cout
#include <algorithm>    // std::nth_element, std::random_shuffle
#include <vector>       // std::vector

// Rearranges the elements in the range [first,last), 
// in such a way that the element at the nth position 
// is the element that would be in that position in a sorted sequence.

bool myfunction (int i,int j) { return (i<j); }

int main () {
  std::vector<int> myvector;

  // set some values:
  for (int i=1; i<10; i++) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9

  std::random_shuffle (myvector.begin(), myvector.end());

  // using default comparison (operator <):
  std::nth_element (myvector.begin(), myvector.begin()+5, myvector.end());

  // using function as comp
  std::nth_element (myvector.begin(), myvector.begin()+5, myvector.end(),myfunction);

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  // ex: 3 1 4 2 5 6 9 7 8
  return 0;
}