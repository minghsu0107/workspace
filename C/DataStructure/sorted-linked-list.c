#include <stdio.h>
#include <stdlib.h>

struct listnode {
	int data;
	struct listnode *next;
};
typedef struct listnode Listnode;

void print_linked_list(Listnode *head) {
	for (; head != NULL; head = head->next)
		printf("data = %d\n", head->data);
	printf("\n");
}

Listnode* insert_linked_list(Listnode *head, int data) {
	Listnode *cur = (Listnode*)malloc(sizeof(Listnode));
	cur->data = data;
	if (head == NULL) {
		cur->next = NULL;
		return cur;
	}
	Listnode *ptr = head, *pre = NULL;
	for (; ptr != NULL; pre = ptr, ptr = ptr->next)
		if (ptr->data >= data) break;
	if (pre == NULL) {
		cur->next = head; // cur->next = ptr
		return (cur);
	}
	else {
		cur->next = pre->next; // cur->next = ptr
		pre->next = cur;
		return (head);
	}
}
Listnode* delete_linked_list(Listnode *head, int data) {
	if (head == NULL) return NULL;
	Listnode *ptr = head, *pre = NULL;
	for (; ptr != NULL; pre = ptr, ptr = ptr->next)
		if (ptr->data == data) break;
	Listnode *tmp;
	if (pre == NULL) {
        tmp = head->next;
		free(head);
		return tmp;
	}
	else {
		pre->next = ptr->next;
		free(ptr);
		return head;
	}
}
Listnode* reverse_linked_list(Listnode *head) {
    Listnode *prev = NULL, *cur = head, *tmp;
    while (cur != NULL) {
    	 tmp = cur->next;
         cur->next = prev;
         prev = cur, cur = tmp;
    }
    return prev;
}
void clear(Listnode *head) {
    while (head != NULL) {
    	Listnode *cur = head;
    	head = head->next;
    	free(cur);
    }
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

    head = reverse_linked_list(head);
    print_linked_list(head);

    for (int i = 0; i < 3; i++) {
    	head = delete_linked_list(head, delete_keys[i]);
    }
    print_linked_list(head);
    
    clear(head);
    return 0;
}
/*
4 6 2 9 7
2 7 4
*/