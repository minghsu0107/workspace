// the wrong code you want to test
#include <cstdio>
#include <deque>
#include <algorithm>
int main() {
  int N, M, K, num;
  scanf("%d%d%d", &N, &M, &K);
  std::deque<int> int_sequence(N, 0);
  for (int i=0; i<N; i++) {
    scanf("%d", &int_sequence[i]);
    if (i>=M-1) {
      printf("%d\n", int_sequence[i]);
    }
  }
}
