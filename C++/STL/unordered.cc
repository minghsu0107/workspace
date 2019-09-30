#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;
// using hash-table
// set and map without order(no upper/lower_bound), one-way iterator
// faster than (multi)set and (multi)map by about one log (期望複雜度)
struct Type {
    int x; string y;
    // overload == in case of collisions
    bool operator== (const Type &a) const {
    	return x == a.x && y == a.y;
    }
};

struct HashFunc {
    std::size_t operator() (const Type &o) const {
    	return ((hash<int>()(o.x)
    		    ^ (hash<string>()(o.y) << 1)) >> 1);
    } 
};
int main() {
	unordered_map<int, int> m;
	unordered_set<int> s;
	m.insert(make_pair(3, 2));
	m.insert(make_pair(4, 1));
	m.insert(make_pair(3, 2));
    s.insert(2);
    s.insert(1);
    s.insert(2);
	for (auto x: m)
		cout << x.first << " " << x.second << endl;
	for (int x: s)
		cout << x << " ";
	cout << endl;

	unordered_map<Type, string, HashFunc> testHash =
	{
        { {1, "1"}, "one"},
        { {2, "2"}, "two"},
        { {3, "3"}, "three"}
	};
	for (const auto & kv: testHash)
		cout << kv.first.x << " " << kv.first.y << " " << kv.second << endl;
	cout << testHash[{2, "2"}] << endl;

	std::unordered_map<std::string,std::string> mymap;
	mymap.reserve(10); // reserve spaces -> faster

    mymap["Bakery"]="Barbara";  // new element inserted
    mymap["Seafood"]="Lisa";    // new element inserted
    mymap["Produce"]="John";    // new element inserted

    std::string name = mymap["Bakery"];   // existing element accessed (read)
    mymap["Seafood"] = name;              // existing element accessed (written)

    mymap["Bakery"] = mymap["Produce"];   // existing elements accessed (read/written)

    name = mymap["Deli"];      // non-existing element: new element "Deli" inserted!

    mymap["Produce"] = mymap["Gifts"];    // new element "Gifts" inserted, "Produce" written

    for (auto& x: mymap) {
        std::cout << x.first << ": " << x.second << std::endl;
    }
    

    std::unordered_map<std::string,double> mymap2 = {
       {"mom",5.4},
       {"dad",6.1},
       {"bro",5.9} };

    std::string input;
    std::cout << "who? ";
    getline (std::cin,input);

    std::unordered_map<std::string,double>::const_iterator got = mymap2.find (input);

    if ( got == mymap2.end() )
        std::cout << "not found";
    else
    	std::cout << got->first << " is " << got->second;

    std::cout << std::endl;  
}