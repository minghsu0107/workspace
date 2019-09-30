#include <stdio.h>
#include <string.h>
#include "stack.h"
int main(int argc, char const *argv[])
{
	char str[128];
	Stack stack;
	scanf("%s", str);
	int len = strlen(str);
	int half = len / 2;
	init_stack(&stack);
	for (int i = 0; i < half; i++) {
		push_stack(&stack, str[i]);
	}
	for (int i = len - half; i < len; i++) {
		if (str[i] != pop_stack(&stack)) {
			printf("not a palindrome\n");
			return 0;
		}
	}
	printf("palindrome\n");
	return 0;
}