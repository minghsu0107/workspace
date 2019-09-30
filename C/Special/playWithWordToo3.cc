#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    int left_sum;
    int right_sum;
    char c;
    int len;
};
 
typedef struct node Node;
 
Node *new_node(char c, int len, Node *prnt)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    assert(tmp != NULL);
    tmp->len = len;
    tmp->c = c;
    tmp->parent = prnt;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->left_sum = 0;
    tmp->right_sum = 0;
    return tmp;
}
 
void print_tree(Node *root)
{
    if ( root == NULL || root->len == 0 ) {return;}
    else {
        print_tree(root->left);
        printf("%c %d ", root->c, root->len);
        print_tree(root->right);
    }
}
 
void insert_left(Node *root, char c, int len)
{
    if ( root->len == 0 ) {
        root->c = c;
        root->len = len;
    } else if ( root->left == NULL ) {
        if ( root->c == c ) {
            root->len += len;
            return;
        }
        root->left_sum += len;
        root->left = new_node(c, len, root);
    } else {
        root->left_sum += len;
        insert_left(root->left, c, len);
    }
}
 
void insert_right(Node *root, char c, int len) {
    if ( root->len == 0 ) {
        root->c = c;
        root->len = len;
    } else if ( root->right == NULL ) {
        if ( root->c == c ) {
            root->len += len;
            return;
        }
        root->right = new_node(c, len, root);
        root->right_sum += len;
    } else {
        root->right_sum += len;
        insert_right(root->right, c, len);
    }
}
 
void insert_k(Node *root, char c, int len, int k, int lower, int upper)
{
    if ( root->len == 0 ) {
        root->c = c;
        root->len = len;
    } else if ( k <= lower ) {
        // left
        if ( root->left == NULL ) {
            insert_left(root, c, len);
            return;
        }
        root->left_sum += len;
        insert_k(root->left, c, len, k, lower - root->left->len - root->left->right_sum, lower - root->left->right_sum);
    } else if ( k > upper ) {
        // right
        if ( k == upper + 1 && c == root->c ) {
            root->len += len;
            return;
        }
        if ( root->right == NULL ) {
            insert_right(root, c, len);
            return;
        }
        root->right_sum += len;
        insert_k(root->right, c, len, k, upper + root->right->left_sum, upper + root->right->len + root->right->left_sum);
    } else if ( k > lower + 1 && k <= upper ) {
        if ( c != root->c ) {
            Node *tmp_left = new_node(root->c, k - lower - 1, root);
            tmp_left->left = root->left;
 
            Node *tmp_right = new_node(root->c, upper - k + 1, root);
            tmp_right->right = root->right;
 
            root->c = c;
            root->len = len;
            root->left = tmp_left;
            root->right = tmp_right;
            root->left_sum += tmp_left->len;
            root->right_sum += tmp_right->len;
        } else {
            root->len += len;
        }
    } else if ( k == lower + 1 ) {
        if ( root->left == NULL ) {
            insert_left(root, c, len);
        } else {
            if ( c == root->c ) {
                root->len += len;
                return;
            }
            root->left_sum += len;
            insert_right(root->left, c, len);
        }
    }
}
 
int main()
{
    char cmd[8];
 
    Node root = {NULL, NULL, NULL, 0, '\0', 0, 0};
    Node *root_ptr = &root;
 
    while ( scanf("%s", cmd) != EOF ) {
        if ( cmd[0] == 'p' ) {
            print_tree(root_ptr);
            printf("$\n");
        } else {
            char dir[16];
            char c[2];
            int len;
            scanf("%s %s %d", dir, c, &len);
            if ( dir[0] == 'l' ) {
                insert_left(root_ptr, c[0], len);
            } else if ( dir[0] == 'r' ) {
                insert_right(root_ptr, c[0], len);
            } else {
                int k = atoi(dir);
                insert_k(root_ptr, c[0], len, k, root_ptr->left_sum, root_ptr->left_sum + root_ptr->len);
            }
        }
    }
 
    return 0;
}