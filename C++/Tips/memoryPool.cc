#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Pool {
   vector<T*> buf;
   T* createNew() {
   	  buf.push_back(new T());
   	  return buf.back();
   }

   void dispose() {
   	    for (int i = 0; i < buf.size(); ++i) delete buf[i];
   	    buf.clear();
   } 
};

struct Node {
	int x; string y;
};
struct Node2 {
	char x; int y;
};

int main() {
	Pool <Node> n1Pool;
	Pool <Node2> n2Pool;
	Node *p = n1Pool.createNew();
	Node2 *p2 = n2Pool.createNew();
	// implement new nodes
	n1Pool.dispose(), n2Pool.dispose();
   return 0;
}