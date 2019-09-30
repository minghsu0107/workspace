#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1024
typedef struct Node{
    char name[16];
    int height;
    int weight;
    struct Node *left, *right;
} Node;
char name[MAXN][16];
int height[MAXN];
int weight[MAXN];
static Node* newNode(char s[], int h, int w) {
    Node *p = calloc(1, sizeof(Node)); // calloc 將所有的空間值初始為 0 (NULL)
    strcpy(p->name, s), p->height = h, p->weight = w;
    return p;
}
static int cmp(Node *u, int h, int w) {
#ifdef HEIGHT
    return h - u->height;
#else
    return w - u->weight;
#endif
}
static Node* insert(Node *u, char s[], int h, int w) {
    if (u == NULL)
        return newNode(s, h, w);
    if (cmp(u, h, w) < 0)
        u->left = insert(u->left, s, h, w);
    else
        u->right = insert(u->right, s, h, w);
    return u;
}
Node* ConstructBSTree(int n, char name[][16], int h[], int w[]) {
    Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, name[i], h[i], w[i]);
    return root;
}
void PrintBSTree( Node *root ){
    if (root == NULL)
        return;
    printf("%s\n", root->name);
    PrintBSTree(root->left);
    PrintBSTree(root->right);
    return;
}
 
int main(){
    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%s %d %d", name[i], &height[i], &weight[i]);
 
    Node *tree = ConstructBSTree( N, name, height, weight );
 
    PrintBSTree( tree );
    return 0;
}