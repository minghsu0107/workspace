// search_n example
#include <iostream>     // std::cout
#include <algorithm>    // std::search_n
#include <vector>       // std::vector

// The function returns an iterator to the first of such elements, 
// or last if no such sequence is found.

bool mypredicate (int i, int j) {
  return (i==j);
}

int main () {
  int myints[]={10,20,30,30,20,10,10,20};
  std::vector<int> myvector (myints,myints+8);

  std::vector<int>::iterator it;

  // using default comparison:
  it = std::search_n (myvector.begin(), myvector.end(), 2, 30);

  if (it!=myvector.end())
    std::cout << "two 30s found at position " << (it-myvector.begin()) << '\n';
  else
    std::cout << "match not found\n";

  // using predicate comparison:
  it = std::search_n (myvector.begin(), myvector.end(), 2, 10, mypredicate);

  if (it!=myvector.end())
    std::cout << "two 10s found at position " << int(it-myvector.begin()) << '\n';
  else
    std::cout << "match not found\n";

  return 0;
}
/*
template<class ForwardIterator, class Size, class T>
  ForwardIterator search_n (ForwardIterator first, ForwardIterator last,
                            Size count, const T& val)
{
  ForwardIterator it, limit;
  Size i;

  limit=first; std::advance(limit,std::distance(first,last)-count); // shift limit

  while (first!=limit)
  {
    it = first; i=0;
    while (*it==val)       // or: while (pred(*it,val)) for the pred version
      { ++it; if (++i==count) return first; }
    ++first;
  }
  return last;
}

  

*/