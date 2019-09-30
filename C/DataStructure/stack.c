#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
void init_stack(Stack *s) {
	s->top = NULL;
}
int stack_full(Stack *s) {
	return 0;
}
int stack_empty(Stack *s) {
	return (s->top == NULL);
}
void push_stack(Stack *s, Data i) {
    Listnode *cur = (Listnode*)malloc(sizeof(Listnode));
    cur->data = i;
    cur->next = s->top;
    s->top = cur;
}
Data pop_stack(Stack *s) {
	if (stack_empty(s)) {
		printf("stack is empty\n");
		return -1;
	}
	Listnode *cur = s->top;
	s->top = s->top->next;
	Data c = cur->data;
	free(cur);
	return c;
}