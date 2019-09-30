#include <stdio.h>
#include <string.h>
//#include "eval.h"  //只需要include 標頭檔

// eval.h
int eval(int exp[]); // .h檔放函式原型
int main() {
    int exp[1024];
    memset(exp, -1, sizeof(exp));
    scanf("%d", &exp[0]);
    for (int i = 1; i <= exp[0]; i++)
        scanf("%d", &exp[i]);
    int ret = eval(exp);
    printf("%d\n", ret);
    return 0;
}
//eval.c
//#include "eval.h"
int eval(int exp[]) {   //.c檔實作函式內容
    int n = exp[0];
    int ret = 0;
    for (int i = 2; i <= n; i += 2) {
        if (exp[i] < 1 || exp[i] > 4)        return -2147483646;
    }
    for (int i = 2; i <= n; i += 2) {
        if (exp[i] == 4 && exp[i+1] == 0)    return -2147483647;
    }
    int s = exp[1];
    for (int i = 3; i <= n; i += 2) {
        if (exp[i-1] == 1)   
            ret += s, s = exp[i];
        else if (exp[i-1] == 2)
            ret += s, s = -exp[i];
        else if (exp[i-1] == 3)
            s *= exp[i];
        else
            s /= exp[i];
    }
    ret += s;
    return ret;
}