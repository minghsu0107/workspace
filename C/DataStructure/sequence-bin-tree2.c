#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence-bin-tree.h"

typedef struct pair {
	int val, idx;
} Pair;
static void swap(Pair *a, Pair *b) {
	int tmp = a->val, tmp2 = a->idx;
	a->val = b->val, a->idx = b->idx;
	b->val = tmp, b->idx = tmp2;
}
static Node* newNode(int val) {
    Node *p = (Node*) calloc(1, sizeof(Node));
    p->value = val;
    return p;
}
static int partition(Pair *B, int l, int r) {
	int pivot = B[r].val, i = l;
	for (int j = l; j <= r - 1; ++j) {
		if (B[j].val <= pivot) {
			swap(&B[i], &B[j]);
			++i;
		}
	}
	swap(&B[i], &B[r]);
	return i;
}
static int kth_smallest(Pair *B, int l, int r, int k) {
	if (k > 0 && k <= r - l + 1) { 
	   int index = partition(B, l, r);
	   if (index - l == k - 1) return B[index].idx;
	   if (index - l > k - 1) return kth_smallest(B, l, index - 1, k);
	   return kth_smallest(B, index + 1, r, k - index + l - 1); 
	}
}
Node *ConstructTree(int A[], int n) {
	if (n == 0)
		return NULL;
	if (n < MAXLENGTH) {
		Node *ret = newNode(A[n-1]), *p;
		p = ret;
		for (int i = n-2; i >= 0; i--)
			p->left = newNode(A[i]), p = p->left;
		return ret;
	}
	Pair *B = (Pair*)malloc(sizeof(Pair) * n);
	for (int i = 0; i < n; ++i)
		B[i].val = A[i], B[i].idx = i;
	int k = n + 1 - MAXLENGTH;
	int pos = kth_smallest(B, 0, n - 1, k);
	Node *ret = newNode(A[pos]);
	ret->left = ConstructTree(A, pos);
	ret->right = ConstructTree(A+pos+1, n-pos-1);
	return ret;
}
// gcc -DMAXLENGTH=1 sequence-bin-tree.c sequence-bin-tree-main.c