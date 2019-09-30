#include "tree.h"
#include <stdlib.h>
 
Node *new_node() {
    Node *ret = (Node*)calloc(1, sizeof(Node));
    ret->data = 0;
    return ret;
}
Node *construct(Node *root, char instruction[MAXN]) {
    char *s = instruction;
    if ( !root )
        root = new_node();
    Node *cur = root;
    while (1) {
        cur->data++;
        switch (*(s++)) {
            case 'L':
                if ( !cur->left )
                    cur->left = new_node();
                cur = cur->left;
                break;
            case 'R':
                if ( !cur->right )
                    cur->right = new_node();
                cur = cur->right;
                break;
            default:
                return root;
        }
    }
}
int query(Node *root, char instruction[MAXN]) {
    char *s = instruction;
    while (1) {
        if ( !root )
            return 0;
        switch (*(s++)) {
            case 'L':
                root = root->left;
                break;
            case 'R':
                root = root->right;
                break;
            default:
                return root->data;
        }
    }
}