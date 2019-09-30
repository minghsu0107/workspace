#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#define MAXN 128
typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;
Node *construct(Node *root, char instruction[MAXN]);
int query(Node *root, char instruction[MAXN]);
#endif