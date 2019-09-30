#include <stdio.h>
typedef struct Node {
    int label;
    struct Node *left, *right;
} Node;
 
void print(Node *node) {
    printf("%d\n", node->label);
}
 
void traversal(Node *root, int N, int command[]) {
    Node *ptr[1000];
    int current = 0;
    ptr[0] = root;
    for (int i = 0, end = 0; i < N && !end; i++) {
        switch (command[i]) {
        case 0:
            print(ptr[current]);
            end = 1;
            break;
        case 1:
            print(ptr[current]);
            break;
        case 2:
            if (current > 0) {
                current--;
            } else {
                print(ptr[current]);
                end = 1;
            }
            break;
        case 3:
            if (ptr[current]->left != NULL) {
                ptr[current + 1] = ptr[current]->left;
                current++;
            } else {
                print(ptr[current]);
                end = 1;
            }
            break;
        case 4:
            if (ptr[current]->right != NULL) {
                ptr[current + 1] = ptr[current]->right;
                current++;
            } else {
                print(ptr[current]);
                end = 1;
            }
            break;
        case 5:
            if (current > 0 && ptr[current - 1]->left != NULL && ptr[current - 1]->right != NULL) {
                if (ptr[current - 1]->left == ptr[current])
                    ptr[current] = ptr[current - 1]->right;
                else
                    ptr[current] = ptr[current - 1]->left;
            } else {
                print(ptr[current]);
                end = 1;
            }
            break;
        }
    }
}