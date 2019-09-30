#include <stdio.h>
#include <stdlib.h>
#include "build-tree-array.h"
Node *build_tree(int array[], int i, int n) {
	if (i >= n) return NULL;
    Node *cur = (Node*)malloc(sizeof(Node));
    cur->label = array[i];
    cur->left = build_tree(array, 2 * i + 1, n);
    cur->right = build_tree(array, 2 * i + 2, n);
    return cur;
}
Node *construct(int array[], int n) {
	return build_tree(array, 0, n);
}