// test data generator
// you don't need to know how this works
#include <cstdio>
#include <iostream>
using std::cout;
using std::cerr;
static auto dummy = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return nullptr;
}();
static inline int SeedRandint(int a, int b, uint64_t new_seed=0) {
  const uint64_t default_seed=1337;
  auto get_next = [=](uint64_t new_seed=0) -> uint64_t{
    static uint64_t next = default_seed;
    if (new_seed) { next = new_seed; }
    const uint64_t alpha = 1442695040888963407ULL;
    const uint64_t beta = 6364136223846793005ULL;
    next = (alpha + beta * next) % 2147483647;
    return next;
  };
  return get_next(new_seed)%(b-a+1)+a;
}
int main(int argn, char** argv) {
  if (argn<4) {
    cerr << "usage: generator N M k [data_max] [seed]\n";
    return -1;
  }
  int N, M, K, data_max=2147483647, seed=1337;
  sscanf(argv[1], "%d", &N);
  sscanf(argv[2], "%d", &M);
  sscanf(argv[3], "%d", &K);
  if (argn>=5) { sscanf(argv[4], "%d", &data_max); }
  if (argn>=6) { sscanf(argv[5], "%d", &seed); }
  SeedRandint(0, 0, seed);
  cout << N << ' ' << M << ' ' << K << '\n';
  for (int i=0; i<N; i++) {
    if (i) { cout << ' '; }
    cout << SeedRandint(1, data_max);
  }
  cout << '\n';
  return 0;
}