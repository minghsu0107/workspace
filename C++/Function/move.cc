// move example
#include <utility>      // std::move
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string

int main () {
  std::string foo = "foo-string";
  std::string bar = "bar-string";
  std::vector<std::string> myvector;

  myvector.push_back (foo);                    // copies
  myvector.push_back (std::move(bar));         // moves

  std::cout << "myvector contains:";
  for (std::string& x:myvector) std::cout << ' ' << x;
  std::cout << '\n';

  std::vector<int> v = {1, 2, 3, 4};
  std::vector<int> w = move(v);

  std::cout << "v: ";
  for (auto i: v)
	  std::cout << i << ' ';

  std::cout << "\nw: ";
  for (auto i: w)
   	  std::cout << i << ' ';

  return 0;
}
/*
The first call to myvector.push_back copies the value of foo 
into the vector (foo keeps the value it had before the call).
The second call moves the value of bar into the vector.
This transfers its content into the vector 
(while bar loses its value, and now is in a valid but unspecified state).
*/