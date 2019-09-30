// hw1: naive copy & sort
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
      std::deque<int> cloned(
        int_sequence.begin()+(i+1-M), 
        int_sequence.begin()+(i+1));
      std::sort(cloned.begin(), cloned.end());
      printf("%d\n", cloned[K-1]);
    }
  }
}