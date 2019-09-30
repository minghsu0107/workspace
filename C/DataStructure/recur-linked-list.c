#include <stdio.h>
#include <stdlib.h>

struct listnode {
	int data;
	struct listnode *next;
};
typedef struct listnode Listnode;

void print_linked_list(Listnode *head) {
	if (head == NULL) {
		printf("\n");
		return;
	}
	printf("data = %d\n", head->data);
	print_linked_list(head->next);
}
Listnode* insert_linked_list(Listnode *head, int data) {
	Listnode *cur = (Listnode*)malloc(sizeof(Listnode));
	cur->data = data;
	if (head == NULL || head->data >= data) {
		cur->next = head;
		return cur;
	}
	head->next = insert_linked_list(head->next, data);
	return (head);
}
Listnode* delete_linked_list(Listnode *head, int data) {
	Listnode *tmp;
	if (head == NULL) return NULL;
	if (data == head->data) {
		tmp = head->next;
		free(head);
		return tmp;
	}
	head->next = delete_linked_list(head->next, data);
	return (head);
}
int main() {
	int insert_keys[5];
	int delete_keys[3];
	Listnode *head = NULL;
	for (int i = 0; i < 5; i++) {
		scanf("%d", &insert_keys[i]);
	}
	for (int i = 0; i < 3; i++) {
		scanf("%d", &delete_keys[i]);
	}
    for (int i = 0; i < 5; i++) {
    	head = insert_linked_list(head, insert_keys[i]);
    }
    print_linked_list(head);
    for (int i = 0; i < 3; i++) {
    	head = delete_linked_list(head, delete_keys[i]);
    }
    print_linked_list(head);
    return 0;
}