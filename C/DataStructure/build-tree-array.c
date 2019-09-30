#include <stdio.h>
#include <stdlib.h>
#include "build-tree-array.h"
Node *build_tree(Node *root, int array[], int i, int n) {
	if (i >= n) return NULL;
	if (root == NULL) {
	   Node *cur = (Node*)malloc(sizeof(Node));
	   cur->label = array[i];
	   cur->left = cur->right = NULL;
	   cur->left = build_tree(cur->left, array, 2 * i + 1, n);
	   cur->right = build_tree(cur->right, array, 2 * i + 2, n);
	   return cur;
    }
}
Node *construct(int array[], int n) {
	Node *root = NULL;
	root = build_tree(root, array, 0, n);
	return root;
}