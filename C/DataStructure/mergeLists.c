#include <stdio.h>
#include <stdlib.h>
#define LEN 1000
struct node {
    int value;
    struct node * next;
};
struct node *merge(struct node *list1, struct node *list2) {
	if (list1 == NULL) return list2;
	if (list2 == NULL) return list1;
	if (list1->value < list2->value) {
		list1->next = merge(list1->next, list2);
		return list1;
	}
	else {
		list2->next = merge(list1, list2->next);
		return list2;
	}
}
struct node *merge2(struct node *list1, struct node *list2) {
	struct node *ptr1 = list1, *ptr2 = list2, *tmp, *head;
	if (list1->value < list2->value) head = list1;
	else head = list2;
	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->value < ptr2->value){
			tmp = ptr1->next;
            if (ptr1->next == NULL || ptr1->next->value > ptr2->value) {
			   ptr1->next = ptr2;
            }
            ptr1 = tmp;
        }
        else{
        	tmp = ptr2->next;
            if (ptr2->next == NULL || ptr2->next->value > ptr1->value) {
			   ptr2->next = ptr1;
            }
            ptr2 = tmp;
        }
	}
	return head;
}
struct node * build(int v[], int n) {
    struct node * head, * ptr;
    int i;
 
    if (!n)
        return 0;
 
    head = (struct node *) malloc(sizeof(struct node));
    ptr = head;
    head -> value = v[0];
    for (i = 1; i < n; i++) {
        ptr -> next = (struct node *) malloc(sizeof(struct node));
        ptr = ptr -> next;
        ptr -> value = v[i];
    }
    ptr -> next = 0;
    return head;
}
 
void print(struct node * ptr) {
    printf("%d", ptr -> value);
    if (ptr -> next) {
        putchar(' ');
        print(ptr -> next);
    }
}
int main(int argc, char const *argv[])
{
	int n1, n2;
    int v1[LEN], v2[LEN];
    int i;
    struct node * list1, * list2;
 
    scanf("%d", &n1);
    for (i = 0; i < n1; i++)
        scanf("%d", &v1[i]);
    scanf("%d", &n2);
    for (i = 0; i < n2; i++)
        scanf("%d", &v2[i]);
    list1 = build(v1, n1);
    list2 = build(v2, n2);
 
    print(merge2(list1, list2));
    putchar('\n');
	return 0;
}