// bit_or example
#include <iostream>     // std::cout
#include <functional>   // std::bit_or
#include <numeric>      // std::accumulate
#include <iterator>     // std::end

int main () {
  int flags[] = {1,2,4,8,16,32,64,128};
  // 0->initial value of acc = 0
  int acc = std::accumulate (flags, std::end(flags), 0, std::bit_or<int>());
  // acc = acc | flags[i], for i from 0 to 7
  std::cout << "accumulated: " << acc << '\n';
  return 0;
}