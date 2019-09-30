#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
	int data;
	struct treenode *left;
	struct treenode *right;
};
typedef struct treenode TreeNode;

void postorder_bs_tree(TreeNode *root) {
	if (root == NULL) return;
	postorder_bs_tree(root->left);
	postorder_bs_tree(root->right);
	printf("%c", root -> data);
}

TreeNode *reconstruct(int n, char pre[], char in[]) {
	if (n == 0) return NULL;
	int leftn = strchr(in, pre[0]) - in;
	int rightn = n - leftn - 1;
	TreeNode *cur = (TreeNode*)malloc(sizeof(TreeNode));
    cur->data = pre[0];
    cur->left = reconstruct(leftn, pre + 1, in);
    cur->right = reconstruct(rightn, pre + 1 + leftn, in + leftn + 1);
    return cur;
}
int main() {
	char preorder[80], inorder[80];
	scanf("%s%s", preorder, inorder);
	int len = strlen(preorder);
	TreeNode *root = reconstruct(len, preorder, inorder);
	postorder_bs_tree(root);
	return 0;
}