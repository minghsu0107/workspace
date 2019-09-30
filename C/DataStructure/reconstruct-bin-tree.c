#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
struct node{
    int val, level;
    struct node *l;
    struct node *r;
};
typedef struct node Node;
typedef struct {
    int val, level;
}Pair;
Pair p[1000];
int find(int n, Node *root, int dist)
{
    if (n == root->val) return dist;
    else if (n < root->val) return find(n, root->l, dist + 1);
    else if (n > root->val) return find(n, root->r, dist + 1);
}
int search(int a,int b, Node *root)
{
    if (a < root->val && b < root->val) return search(a, b, root->l);
    else if (a > root->val && b > root->val) return search(a, b, root->r);
    else return find(a, root, 0) + find(b, root, 0);
}
int cmp(const void *a,const void *b)
{
    return (((Pair*)a)->level) - (((Pair*)b)->level);
}
Node *create(Node *root,Pair p)
{
    Node *cur;
    if (root == NULL) {
        cur = (Node*)malloc(sizeof(Node));
        assert(cur != NULL);
        cur->val = p.val, cur->level = p.level;
        cur->l = cur->r = NULL;
        return cur;
    }
    if (p.val < root->val) root->l = create(root->l, p);
    else if (p.val > root->val) root->r = create(root->r, p);
    return root;
}
int main()
{
    int n, m;
    Node *root = NULL;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) scanf("%d%d", &p[i].val, &p[i].level);
    qsort(p , n, sizeof(Pair),cmp);
    for (int i = 0; i < n; i++) root = create(root, p[i]);
    scanf("%d",&m);
    while (m--) {
    	int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n",search(a, b, root));
    }
    return 0;
}