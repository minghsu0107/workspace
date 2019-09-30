// inserter example
#include <iostream>     // std::cout
#include <iterator>     // std::front_inserter
#include <list>         // std::list
#include <algorithm>    // std::copy

// Container on which the iterator will insert new elements.
// Container should be a container class with member insert defined.

int main () {
  std::list<int> foo,bar;
  for (int i=1; i<=5; i++)
  { foo.push_back(i); bar.push_back(i*10); }

  std::list<int>::iterator it = foo.begin();
  advance (it,3);

  std::copy (bar.begin(),bar.end(),std::inserter(foo,it));

  std::cout << "foo contains:";
  for ( std::list<int>::iterator it = foo.begin(); it!= foo.end(); ++it )
	  std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}