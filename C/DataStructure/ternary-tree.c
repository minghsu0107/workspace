#include <stdio.h>
#include <stdlib.h>
#include "ternary-tree.h"
Node *create(Node *root, int num) {
	if (root == NULL) {
		Node *cur = (Node*)calloc(1, sizeof(Node));
		cur->small = -1, cur->large = num;
        return cur;
	}
	if (root->small == -1) {
		root->small = num < root->large ? num : root->large;
		root->large = num > root->large ? num : root->large;
	}
	else {
		if (num < root->small)
		   root->left = create(root->left, num);
	    else if (num > root->small && num < root->large)
	       root->mid = create(root->mid, num);
        else if (num > root->large)
           root->right = create(root->right, num);
	}
	return root;
}
Node *ConstructTree(int sequence[], int N) {
	Node *root = NULL;
    for (int i = 0; i < N; i++) {
    	root = create(root, sequence[i]);
    }
    return root;
}