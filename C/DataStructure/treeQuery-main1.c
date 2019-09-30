#include <stdio.h>
#include <stdlib.h>
#include "treeQuery.h"
void preorder(Node *root) {
    if (root == NULL)
        return ;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node *root) {
    if (root == NULL)
        return ;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
int main()
{
    char instruction[MAXN];
    Node *root = NULL;
    while (scanf("%s", instruction) != EOF) {
        root = construct(root, instruction);
        preorder(root);
        printf("\n");
        inorder(root);
        printf("\n");
    }
    return 0;
}