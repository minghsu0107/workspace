// equal_to example
#include <iostream>     // std::cout
#include <utility>      // std::pair
#include <functional>   // std::equal_to
#include <algorithm>    // std::mismatch

int main () {
  std::pair<int*,int*> ptiter;
  int foo[]={10,20,30,40,50};
  int bar[]={10,20,40,80,160};

  ptiter = std::mismatch (foo, foo+5, bar, std::equal_to<int>());
  // std::not_equal_to<int>()
  std::cout << "First mismatching pair is: " << *ptiter.first;
  std::cout << " and " << *ptiter.second << '\n';
  return 0;
}