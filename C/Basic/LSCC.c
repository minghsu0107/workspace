#include <stdio.h>
int main(int argc, char const *argv[])
{
  int task;
  unsigned int l;
  unsigned short s;
  char str[5], c[3]; 
  scanf("%d", &task);
  if (!task) {
       while (scanf("%s%u%hu%s", str, &l, &s, c) != EOF) {
           unsigned long long result = 0;
           int len = 64, flag = 1;
           for (int i = 0; i < 4; i++) {
              if (str[i] == 'L') {
                  result |= ((unsigned long long) l << (len - 32));
                  len -= 32;
              }
              else if (str[i] == 'S') {
                  result |= ((unsigned long long) s << (len - 16));
                  len -= 16;
              }
              else {
                  if (flag) {
                     result |= ((unsigned long long) c[0] << (len - 8));
                     flag = 0;
                  }
                  else {
                     result |= ((unsigned long long) c[1] << (len - 8));
                  }
                  len -= 8;
              }
           }
           printf("%llu\n", result);
       }
  } 
  else {
     unsigned long long result = 0;
       while (scanf("%s%llu", str, &result) != EOF) {
           int flag = 1;
           char c1, c2;
           l = 0, s = 0;
           for (int i = 0; i < 4; i++) {
              if (str[i] == 'L') {
                  l = (unsigned int)(result >> (64 - 32));
                  result <<= 32;

              }
              else if (str[i] == 'S') {
                  s = (unsigned short)(result >> (64 - 16));
                  result <<= 16;
              }
              else {
                  if (flag) {
                     c1 = (char)(result >> (64 - 8));
                     flag = 0;
                  }
                  else {
                     c2 = (char)(result >> (64 - 8));
                  }
                  result <<= 8;
              }
           }
           c[0] = (char) c1;
           c[1] = (char) c2;
           c[2] = '\0';
           printf("%u %hu %s\n", l, s, c);
       }
  }
  return 0;
}