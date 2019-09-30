#ifndef _TREE_H
#define _TREE_H
 
typedef struct Node {
    int label;
    struct Node *left, *right;
} Node;
 
Node* construct(int array[], int n);
 
#endif