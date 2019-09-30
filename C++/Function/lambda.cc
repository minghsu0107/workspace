#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sortV(vector<int> &v, int k) {
    sort(v.begin(), v.end(), [=](int a, int b){
    	return sin(k * a) > sin(k * b); // k is passed by value from scope outside
    });
}
int main() {
  int n = [] (int x, int y) { return x + y; }(5, 4);
  // int n = [] (int x, int y) -> int{ return x + y; }(5, 4);
  cout << n << endl;

  auto lambda = []() { cout << "Hello, Lambda" << endl; };
  lambda();

  vector<int> v{1, 2, 3, 4};
  sortV(v, 1);
  for (auto x: v) cout << x << " ";
}
/*
    []：只有兩個中括號，完全不抓取外部的變數。
    [=]：所有的變數都以傳值（by value）的方式抓取。
    [&]：所有的變數都以傳參考（by reference）的方式抓取。
    [x, &y]：x 變數使用傳值、y 變數使用傳參考。
    [=, &y]：除了 y 變數使用傳參考之外，其餘的變數皆使用傳值的方式。
    [&, x]：除了 x 變數使用傳值之外，其餘的變數皆使用傳參考的方式。
*/