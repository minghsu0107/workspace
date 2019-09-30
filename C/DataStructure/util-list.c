#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
 
Node* mk_list(int n) {
    Node *pre = NULL, *head = NULL;
    for (int i = 0; i < n; i++) {
        Node *cur = malloc(sizeof(Node));
        cur->v = sp_rand(), cur->next = NULL;
        if (!i) head = cur;
        if(pre != NULL) pre->next = cur;
        pre = cur;
    }
    return head;
}
void rm_list(Node *head) {
    while (head != NULL) {
          Node *tmp = head;
          free(head);
          head = tmp->next;
    }
}