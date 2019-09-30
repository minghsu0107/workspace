#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct treenode {
	int data;
	struct treenode *left;
	struct treenode *right;
};
typedef struct treenode TreeNode;

void inorder_bs_tree(TreeNode *root) {
	if (root == NULL) return;
	inorder_bs_tree(root->left);
	printf("data = %d\n", root -> data);
	inorder_bs_tree(root->right);
}
void preorder_bs_tree(TreeNode *root) {
	if (root == NULL) return;
	printf("data = %d\n", root -> data);
	preorder_bs_tree(root->left);
	preorder_bs_tree(root->right);
}
void postorder_bs_tree(TreeNode *root) {
	if (root == NULL) return;
	postorder_bs_tree(root->left);
	postorder_bs_tree(root->right);
	printf("data = %d\n", root -> data);
}
TreeNode *insert_bs_tree(TreeNode *root, int data) {
	struct treenode *cur;
	if (root == NULL) {
       cur = (TreeNode*)malloc(sizeof(TreeNode));
       assert(cur != NULL);
       cur->data = data;
       cur->left = NULL, cur->right = NULL;
       return cur;
	}
	if (data < root->data) {
       root->left = insert_bs_tree(root->left, data);
	}
	else {
	   root->right = insert_bs_tree(root->right, data);
	}
	return root;
}
void find(TreeNode *root, int val) {
	if (root == NULL) printf("not found\n");
	if (val == root->data) {
		printf("found\n");
		return;
	}
	else if (val < root->data) find(root->left, val);
	else find(root->right, val);
}
int main() {
    int insert_keys[5], query;
    for (int i = 0; i < 5; i++) {
        scanf("%d", &(insert_keys[i]));
    }
    scanf("%d", &query);
    TreeNode *root = NULL;
    for (int i = 0; i < 5; i++) {
    	root = insert_bs_tree(root, insert_keys[i]);
    }
    printf("inorder\n");
    inorder_bs_tree(root);

    printf("preorder\n");
    preorder_bs_tree(root);

    printf("postorder\n");
    postorder_bs_tree(root);
    find(root, query);
    return 0;
}