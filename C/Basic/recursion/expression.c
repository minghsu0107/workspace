#include <stdio.h>
#include <string.h>
#include <ctype.h>
int pos = 0;
int eval(char *s) {
  if (s[pos] == '-' && !isdigit(s[pos+1])) {
     pos++;
     int k = eval(s);
     if (k == -2147483648) return -2147483648;
     return 0 - k;
  }
  else if (s[pos] == '(') {
    pos++;
    int left = eval(s);
    if (left == -2147483648) return -2147483648;
    if (s[pos] != '+' && s[pos] != '-' && 
        s[pos] != '*' && s[pos] != '/' ) 
       return -2147483648;
    char OP = s[pos];
    pos++;
    int right = eval(s);
    if (right == -2147483648) return -2147483648;
    if (s[pos] != ')') return -2147483648;
    pos++;
    switch (OP) {
       case '+': return left + right;
       case '-': return left - right;
       case '*': return left * right;
       case '/':
         if (right != 0) return left/right;
         return -2147483648;
    }
  }
  else if (s[pos] >= '0' && s[pos] <= '9') {
    int num = s[pos] - '0';
    pos++;
    return num;
  }
  else if (s[pos] == '-' && isdigit(s[pos+1])) {
    int num = s[pos+1] - '0';
    pos += 2;
    return 0 - num;
  }
  return -2147483648;
}
int expression(char *s) {
    int len = strlen(s);
    pos = 0;
    int val = eval(s);
    if (pos != len) return -2147483648;
    return val;
}
char buf[1<<20];
int main() {
    while (scanf("%s", buf) == 1) {
        int ret = expression(buf);
        printf("%d\n", ret);
    }
    return 0;
}