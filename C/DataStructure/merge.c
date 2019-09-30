#include "merge.h"
#include <stdlib.h>
static int newn(int n, int K, int *level, int *flag) {
	do {
	   if ((*level) % 2) {
	      n++;
	      if (n == K)
	   	     n = K - 1, (*level)++;
	   } else {
	      n--;
	      if (n < 0)
	         n = 0, (*level)++;
	   }
    } while (flag[n]);
    return n;
}
Node *merge(Node *list[], int K) {
	int *flag = calloc(K, sizeof(int));
	int n = 0, first = 1, level = 1, remain = K;
	Node *pre = NULL, *cur = list[n], *head = cur; 
	while(1) {
		if (remain == 1) {
           if (pre != NULL) pre->next = cur;
           break;
		}
		if (cur == NULL) {
			flag[n] = 1;
			remain--;
		} else {
		   if (first) {
		   	  head = cur;
		   	  first = 0;
		   }
		   if (pre != NULL) pre->next = cur;
		   list[n] = list[n]->next;
		   pre = cur;
		}
		n = newn(n, K, &level, flag);  
		cur = list[n];      
	}
	return head;
}