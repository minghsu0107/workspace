#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
 
#define MAXLEN 4000
 
typedef struct treenode
{
    int num;
    struct treenode *left;
    struct treenode *right;
}TreeNode;
 
char str[MAXLEN+1];
 
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
 
TreeNode* construct_tree(int l, int r) {
    if (str[l] == '(') {
       int p = 0;
       for (int i = l + 1; i <= r - 1; ++i) {
           if (str[i] == '(') p++;
           if (str[i] == ')') p--;
           if (p == 0 && str[i] == ',') {
              TreeNode* current = (TreeNode *)malloc(sizeof(TreeNode));
              current->left = construct_tree(l + 1, i);
              current->right = construct_tree(i + 1, r - 1);
              current->num = current->left->num + current->right->num;
              return current;
           }
       }
    }
    else if (isdigit(str[l])) {
        int n;
        sscanf(str + l, "%d", &n);
        TreeNode* current = (TreeNode *)malloc(sizeof(TreeNode));
        current->num = n;
        current->left = current->right = NULL;
        return current;
    }
}
 
int main(int argc, char const *argv[]) {
    TreeNode *root;
    fgets(str,MAXLEN,stdin);
    int len = strlen(str);
    root = construct_tree(0, len);
    HLHR(root);
    return 0;
}