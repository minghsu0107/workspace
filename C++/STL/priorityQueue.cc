#include <iostream>
#include <queue>
using namespace std;
struct Greater
{
  bool operator() (int a, int b) { return a > b; }
};

int main() {
  priority_queue<int> q;
  // or priority_queue<int, vector<int>, less<int> > q;

  // O(nlogn) construction
  for(int n : {3, 1, 4 }) {
    q.push(n);
  }
  // O(n) construction
  int arr[] = {3, 1, 4};
  priority_queue<int> q3(arr, arr + 3);

  cout << q.top() << " " << q3.top() << endl; // 4
  q.pop(), q3.pop();
  cout << q.top() << " " << q3.top() << endl; // 3
  cout << q.empty() << " sz " << q.size() << endl; // false, 2

  priority_queue<int, vector<int>, greater<int> > q2;
  // priority_queue<int, vector<int>, Greater> q2;

  for(int n : {3, 1, 4 }) {
    q2.push(n);
  }

  cout << q2.top() << endl; // 1
  q2.pop();
  cout << q2.top() << endl; // 3
}