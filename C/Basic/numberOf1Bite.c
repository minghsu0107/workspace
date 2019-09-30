#include <stdio.h>
 
int main() {
  long long int n;
  while (scanf("%lld", &n) != EOF) {
    int cnt = 0;
    while (n != 0) {
      cnt += n & 1; // n&1 即 (n%2 == 1)
      n >>= 1; // 即 n /= (2^1) (把每一個bit都向右移,左邊補上最左邊的bit; 往低位) 
               // n <<= 1 即 n *= (2^1) (把每一個bit都向左移,右邊補0; 往高位)
               // 0100 -> 0010 ; 0100 -> 1000
    }
    printf("%d\n", cnt);
  }
}
// n & 1 produces a value that is either 1 or 0, depending on the least significant bit of n (LSB)
// if the last bit is 1, the result of n & 1 is 1; otherwise, it is 0. 

// XOR : when two bits are different, the answer is 1, otherwise 0;
// n ^ 255 means reverse every bit in n (since all 32 bits in 255 are 1), same effect as ~n
// n & 0 == 0; n | 0 == n; n^0 == n;
// n & 1 == (n%2 == 1) ? 1 : 0;
// n | 1 == (n%2 == 1) ? n : n + 1;
// n ^ 1 == (n%2 == 1) ? n-1 : n+1;
// Example: 99 ^ 1
//          00000000-00000000-00000000-01100011  (99 in binary representation) 
//          00000000-00000000-00000000-00000001  (1 in binary representation)
//          -----------------------------------
//          00000000-00000000-00000000-01100010  (== 98)
// 1 int = 4 byte = 32 bits
// 1 long long int = 8 byte = 64 bits
// 1001 == 9 (1*2^3 + 0*2^2 + 0*2^1 + 1*2^0 = 9)
