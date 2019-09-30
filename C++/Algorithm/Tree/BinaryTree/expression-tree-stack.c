#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
char str[1024], node[1024][100], variable[100][100];
int value[100], len, l, idx, a, b, c, ans;
int main() {
    Stack stack;
    init_stack(&stack);
    len = 0, l = 0;
    fgets(str, 1024, stdin);
    while (sscanf(str + l, "%s", node[len]) == 1) {
        l += strlen(node[len]) + 1;
        ++len;
    }
    idx = 0;
    while (fgets(str, 1024, stdin) != NULL) {
        char tmp; // "="
        sscanf(str,"%s %c %d",variable[idx], &tmp, &value[idx]);
        idx++;
    }
    for (int i = 0; i < len; ++i) {
        switch(node[i][0]) {
            case '(':
            break;

            case '+':
            push_stack(&stack, -1);
            break;

            case '-':
            push_stack(&stack, -2);
            break;

            case '*':
            push_stack(&stack, -3);
            break;

            case '/':
            push_stack(&stack, -4);
            break;

            case ')':
            a = pop_stack(&stack); b = pop_stack(&stack); c = pop_stack(&stack);
            if(c == -1) ans = b + a;
            else if(c == -2) ans = b - a;
            else if(c == -3) ans = b * a;
            else if(c == -4) ans = b / a;
            push_stack(&stack, ans);
            break;

            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9':
            push_stack(&stack, atoi(node[i]));
            break;

            default:
            for(int k = 0; k < idx; k++) {
                if(!strcmp(node[i],variable[k])) {
                    push_stack(&stack, value[k]);
                    break;
                }
            }
            break;
        }
    }
    printf("%d", pop_stack(&stack));
    return 0;
}