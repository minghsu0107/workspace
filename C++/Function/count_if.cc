// greater_equal example
#include <iostream>     // std::cout
#include <functional>   // std::greater_equal, std::bind2nd
#include <algorithm>    // std::count_if
using namespace std;
int main () {
  int numbers[]={20,-30,10,-40,0};
  int cx = std::count_if (numbers, numbers+5, std::bind2nd(std::greater_equal<int>(),0));
  // std::less_equal<int>()
  std::cout << "There are " << cx << " non-negative elements.\n";

  int num[] = {10,20,30,40,50,10};
  int cx2;
  cx2 = count_if (num, num+6, bind1st(equal_to<int>(),10) );
  cout << "There are " << cx2 << " elements that are equal to 10.\n";
  return 0;
}