#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
	int data;
	struct treenode *left;
	struct treenode *right;
};
typedef struct treenode TreeNode;

void preorder_bs_tree(TreeNode *root) {
	if (root == NULL) return;
	printf("%c", root -> data);
	preorder_bs_tree(root->left);
	preorder_bs_tree(root->right);
}

TreeNode *reconstruct(int n, char post[], char in[]) {
	if (n == 0) return NULL;
	int leftn = strchr(in, post[n - 1]) - in;
	int rightn = n - leftn - 1;
	TreeNode *cur = (TreeNode*)malloc(sizeof(TreeNode));
    cur->data = post[n - 1];
    cur->left = reconstruct(leftn, post, in);
    cur->right = reconstruct(rightn, post + leftn, in + leftn + 1);
    return cur;
}
int main() {
	char postorder[80], inorder[80];
	scanf("%s%s", postorder, inorder);
	int len = strlen(postorder);
	TreeNode *root = reconstruct(len, postorder, inorder);
	preorder_bs_tree(root);
	return 0;
}