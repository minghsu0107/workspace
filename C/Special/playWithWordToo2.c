#include <stdio.h>
#include <stdlib.h>
 
typedef struct node {
    char c;
    int n;
    int left_cnt;
    int right_cnt;
    struct node *left;
    struct node *right;
} Node;
 
Node *insert_left(char c, int n, Node *root)
{
    if (root == NULL) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->c = c;
        node->n = n;
        node->left_cnt = 0;
        node->right_cnt = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
 
    root->left_cnt += n;
    root->left = insert_left(c, n, root->left);
    return root;
}
 
Node *insert_right(char c, int n, Node *root)
{
    if (root == NULL) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->c = c;
        node->n = n;
        node->left_cnt = 0;
        node->right_cnt = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
 
    root->right_cnt += n;
    root->right = insert_right(c, n, root->right);
    return root;
}
 
Node *insert_mid(int k, char c, int n, Node *root)
{
    if (root == NULL) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->c = c;
        node->n = n;
        node->left_cnt = 0;
        node->right_cnt = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
 
    if (k <= root->left_cnt) {
        //fprintf(stderr, "1-\n");
        root->left_cnt += n;
        root->left = insert_mid(k, c, n, root->left);
    } else if (k > root->left_cnt + root->n + 1) {
        //fprintf(stderr, "2-\n");
        root->right_cnt += n;
        root->right = insert_mid(k - root->left_cnt - root->n, c, n, root->right);
    } else if (k == root->left_cnt + 1) {
        //fprintf(stderr, "3-\n");
        root->left_cnt += n;
        root->left = insert_right(c, n, root->left);
    } else if (k == root->left_cnt + root->n + 1) {
        //fprintf(stderr, "4-\n");
        root->right_cnt += n;
        root->right = insert_left(c, n, root->right);
    } else {
        //fprintf(stderr, "5-\n");
        int index = k - root->left_cnt - 1;
 
        root->left_cnt += index;
        root->left = insert_right(root->c, index, root->left);
        root->right_cnt += root->n - index;
        root->right = insert_left(root->c, root->n - index, root->right);
 
        root->c = c;
        root->n = n;
    }
 
    return root;
}
 
char pre_c;
int  pre_n;
void printTree(Node *root)
{
    if (root == NULL)
        return;
 
    printTree(root->left);
    if (root->c != pre_c) {
        if (pre_c != '-')
            printf("%c %d ", pre_c, pre_n);
        pre_n = root->n;
        pre_c = root->c;
    } else {
        pre_n += root->n;
    }
    printTree(root->right);
 
    return;
}
 
int main(void)
{
    char cmd[15], c;
    Node *root = NULL;
    int n;
 
    while (~scanf("%s", cmd)) {
        if (*cmd == 'p') {
            if (root != NULL) {
                pre_c = '-';
                pre_n = 0;
                printTree(root);
                printf("%c %d $\n", pre_c, pre_n);
            } else
                puts("$");
        } else {
            scanf("%s %c %d", cmd, &c, &n);
            switch (*cmd) {
            case 'l':
                root = insert_left(c, n, root);
                break;
            case 'r':
                root = insert_right(c, n, root);
                break;
            default:
                root = insert_mid(atoi(cmd), c, n, root);
            }    
        }
    }
 
    return 0;
}