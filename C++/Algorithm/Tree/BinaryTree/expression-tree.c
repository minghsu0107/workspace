#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXLEN 1000
char var_arr[51][40];
int value[51];
int pos = 0;
int find_var(char v[], int n) {
    for (int i = 0; i < n; i++) {
        if (!strcmp(v, var_arr[i]))
            return value[i];
    }
}
int eval(char *str, int n) {
    if (str[pos] == '(') {
       pos += 2;
       char op = str[pos];
       pos += 2;
       int left = eval(str, n);
       int right = eval(str, n);
       pos += 2;
       switch (op) {
       case '+': return left + right;
       case '-': return left - right;
       case '*': return left * right;
       case '/': return left / right;
       }
    }
    else if (isdigit(str[pos])) {
        int number = 0;
        while (isdigit(str[pos])) {
            number *= 10;
            number += str[pos] - '0';
            pos++;
        }
        pos++;
        return number;
    }
    else {
        char v[40];
        int len = 0;
        sscanf(&str[pos], "%s", v);
        pos += strlen(v);
        pos++;
        return find_var(v, n);
    }
}
int main(int argc, char const *argv[])
{
    char str[MAXLEN + 2], tmp[40];
    int n = 0;
    fgets(str, MAXLEN, stdin);
    while (fgets(tmp, 40, stdin) != NULL) {
        char *ptr = strtok(tmp, " ");
        strcpy(var_arr[n], ptr);
        ptr = strtok(NULL, " ");
        ptr = strtok(NULL, "\n");
        value[n] = atoi(ptr);
        n++;
    }
    printf("%d", eval(str, n));
    return 0;
}