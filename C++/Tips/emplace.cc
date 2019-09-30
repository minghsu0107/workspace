#include <bits/stdc++.h>
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;
typedef tuple<int,int,int> State; // operator< defined

int main(){
  int a,b,c;
  tie(a,b,c) = mt(1,2,3); // assign
  tie(a,b) = mt(b,a); // swap(a,b)

  vector<pair<int,int>> v;
  v.eb(a,b); // shorter and faster than pb(mp(a,b))
/*
  // Dijkstra
  priority_queue<State> q;
  q.emplace(0, source, -1);
  while(q.size()){
    int dist, node, prev;
    tie(dist, node, prev) = q.top(); q.pop();
    dist = -dist;
    // ~~ find next state ~~
    q.emplace(-new_dist, new_node, node);
  }
*/
  map<int, string> m;
  m.emplace(1, "hello");
}
/*
emplace_back is faster than push_back 'cause
it just construct value at the end of vector
but push_back construct it somewhere else
and then move it to the vector.
*/