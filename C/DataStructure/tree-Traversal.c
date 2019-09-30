#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
 
#define MAXLEN 4000
 
typedef struct treenode
{
    int num;
    struct treenode *left;
    struct treenode *right;
}TreeNode;
 
char str[MAXLEN+1];
int pos = 0;
 
void HLHR(TreeNode *);
void HRHL(TreeNode *);
 
void HRHL(TreeNode *root) {
    if(root == NULL)
        return;
    printf("%d\n",root->num);
    HLHR(root->right);
    printf("%d\n",root->num);
    HLHR(root->left);
    return;
}
 
void HLHR(TreeNode *root) {
    if(root == NULL)
        return;
    printf("%d\n",root->num);
    HRHL(root->left);
    printf("%d\n",root->num);
    HRHL(root->right);
    return;
}
 
TreeNode* construct_tree() {
    TreeNode* current = NULL;
    if (str[pos] == '(') {
       pos++;
       current = (TreeNode *)malloc(sizeof(TreeNode));
       assert(current != NULL);
       current->left = construct_tree();
       pos++;
       current->right = construct_tree();
       pos++;
       current->num = current->left->num + current->right->num;
       return current;
    }
    else if (isdigit(str[pos])) {
        int n = 0;
        while (isdigit(str[pos])) {
            n *= 10;
            n += str[pos] - '0';
            pos++;
        }
        TreeNode* current = (TreeNode *)malloc(sizeof(TreeNode));
        current->num = n;
        current->left = current->right = NULL;
        return current;
    }
}
 
int main(int argc, char const *argv[]) {
    TreeNode *root;
    fgets(str,MAXLEN,stdin);
    root = construct_tree();
    HLHR(root);
    return 0;
}