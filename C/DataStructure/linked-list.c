#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct listnode {
	int data;
	struct listnode *next;
};
typedef struct listnode Listnode;

void print_linked_list(Listnode *head) {
	for (; head != NULL; head = head->next)
		printf("data = %d\n", head->data);
}
int main() {
	int array[5];
	Listnode *head;
	Listnode *prev = NULL;
	for (int i = 0; i < 5; i++) {
		scanf("%d", &(array[i]));
	}
	for (int i = 0; i < 5; i++) {
		head = (Listnode *)malloc(sizeof(Listnode));
		assert(head != NULL);
		head->data = array[i];
		head->next = prev;
		prev = head;
	}
	print_linked_list(head); // the answer will be backward
	// if input = 4, 6, 2, 9, 7, output: 7, 9, 2, 6, 4
	return 0;
} 