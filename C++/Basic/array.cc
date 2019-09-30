#include <iostream>
using namespace std;
int sumArray(int arr[], int len) {
  int sum = 0;
  for (int i=0; i<len; i++) {
    sum += arr[i];
  }
  return sum;
}
int main() {
  int pi[100] = { 3, 1, 4, 1, 5, 9 };
  cout << sumArray(pi, 6) << endl;

  int len = sizeof(pi)/sizeof(int);
  cout << sumArray(pi, len) << endl;
}