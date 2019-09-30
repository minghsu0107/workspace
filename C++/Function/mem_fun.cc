// mem_fun example
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main () {
  vector <string*> numbers;

  // populate vector of pointers:
  numbers.push_back ( new string ("one") );
  numbers.push_back ( new string ("two") );
  numbers.push_back ( new string ("three") );
  numbers.push_back ( new string ("four") );
  numbers.push_back ( new string ("five") );

  vector <int> lengths ( numbers.size() );

  transform (numbers.begin(), numbers.end(), lengths.begin(), mem_fun(&string::length));
	
  for (int i=0; i<5; i++) {
    cout << *numbers[i] << " has " << lengths[i] << " letters.\n";
  }

  // deallocate strings:
  for (vector<string*>::iterator it = numbers.begin(); it!=numbers.end(); ++it)
    delete *it;

  return 0;
}