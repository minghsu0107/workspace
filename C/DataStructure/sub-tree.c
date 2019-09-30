#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int label;
    struct Node *left, *right;
} Node; 
static int dfs(Node *u, int k, int **p) {
    if (u == NULL)
        return 0;
    int lh = dfs(u->left, k, p);
    int rh = dfs(u->right, k, p);
    if (lh && rh && u->label != k) {
        (*p)[0] = u->label;
        (*p)++;
    }
    return lh || rh || u->label == k;
}
int getNode(Node *root, int label[], int k) {
    int *p = label;
    dfs(root, k, &p);
    return p - label;
}
Node* newNode(int label, Node *l, Node *r) {
    Node *u = (Node *) malloc(sizeof(Node));
    u->label = label, u->left = l, u->right = r;
    return u;
}
int main() {
    Node *root = newNode(
        10,
            newNode(
                5,
                    newNode(1, NULL, NULL),
                    newNode(1, NULL, NULL)               
            ),
            newNode(
                7,
                    newNode(1, NULL, NULL),
                    newNode(5, NULL, NULL)               
            )
    );
    int k;
    while (scanf("%d", &k) == 1) {
        int A[128];
        int n = getNode(root, A, k);
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
            printf("%d%c", A[i], i == n-1 ? '\n' : ' ');
    }
    return 0;
}