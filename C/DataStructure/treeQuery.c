#include "treeQuery.h"
#include <string.h>
#include <stdlib.h>
static Node *myconstruct(Node *root, char instruction[MAXN], int d, int n) {
    if (root == NULL) {
       Node *cur = malloc(sizeof(Node));
       cur->left = NULL, cur->right = NULL;
       cur->data = 1;
       root = cur;
    }
    else (root->data)++;
    if (d == n) return root;
    if (instruction[d] == 'L') root->left = myconstruct(root->left, instruction, d+1, n);
    else root->right = myconstruct(root->right, instruction, d+1, n);
    return root;
}
Node *construct(Node *root, char instruction[MAXN]) {
    int n = strlen(instruction);
    return myconstruct(root, instruction, 0, n);
}
static int myquery(Node *root, char instruction[MAXN], int d, int n) {
    if (d == n) return root == NULL ? 0: root->data;
    if (instruction[d] == 'L' && root->left != NULL) 
       return myquery(root->left, instruction, d+1, n);
    else if (instruction[d] == 'R' && root->right != NULL)
       return myquery(root->right, instruction, d+1, n);
    return 0;
}
int query(Node *root, char instruction[MAXN]) {
    int n = strlen(instruction);
    return myquery(root, instruction, 0, n);
}