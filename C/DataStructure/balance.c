#include <stdio.h>
#include "stack.h"
int main(int argc, char const *argv[])
{
	char str[128];
	Stack stack;
	int balanced = 1;
	scanf("%s", str);
	init_stack(&stack);
	for (int i = 0; str[i] && balanced; i++) {
		switch(str[i]) {
		case '(': case '[': case '{':
		  push_stack(&stack, str[i]);
		  break;
		case ')':
		  if (pop_stack(&stack) != '(')
		  	 balanced = 0;
		  break;
		case ']':
          if (pop_stack(&stack) != '[')
		  	 balanced = 0;
		  break;
		case '}':
		  if (pop_stack(&stack) != '{')
		  	 balanced = 0;
		  break;
		default:
		  balanced = 0;
		}
	}
	if (balanced == 0 || !stack_empty(&stack))
	   printf("not balanced\n");
	else
	   printf("balanced\n");
	return 0;
}