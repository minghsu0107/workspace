#include <iostream>
#include <vector>
#include <string>
using namespace std;

int bell(string &s, int &pos){
  if (s[pos] == '(') {
    pos++;

    int left = bell(s, pos);
    if (left < 0) return -1;

    if (s[pos] != ',') return -1;
    pos++;

    int right = bell(s, pos);
    if (right < 0) return -1;

    if (s[pos] != ')') return -1;
    pos++;

    if(left!=right) return -1;

    return left + right;
  } else if (s[pos] >= '0' and s[pos] <= '9') {
    int sz = s[pos] - '0';
    pos++;
    return sz;
  }
  return -1;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    int pos = 0;
    int size = bell(s, pos);
    if (size == -1) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }
}