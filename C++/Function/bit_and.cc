// bit_and example
#include <iostream>     // std::cout
#include <functional>   // std::bit_and
#include <algorithm>    // std::transform
#include <iterator>     // std::end


int main () {
  int values[] = {100,200,300,400,500};
  int masks[] = {0xf,0xf,0xf,255,255};
  int results[5];

  std::transform (values, std::end(values), masks, results, std::bit_and<int>());

  std::cout << "results:";
  for (const int& x: results)
    std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}