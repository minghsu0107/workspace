// top-down (pointer method)
#include <iostream>
#include <stdio.h>
using namespace std;
 
struct Node
{
    Node* Lc;
    Node* Rc;
    int sum;
};
 
void buildTree(Node* &O, int L, int R);
void destroyTree(Node* &O, int L, int R);
int querySum(Node* O, int L, int R, int qL, int qR);
void updateNode(Node* O, int L, int R, int index, int value);
 
Node *root;
int num[1000000];

// index starts from 1
int main()
{
    int N, M;
 
    while(scanf("%d %d", &N, &M) == 2)
    {
        for(int Ni = 1; Ni <= N; Ni++)
            scanf("%d", &num[Ni]);
 
        buildTree(root, 1, N);
 
        for(int Mi = 1; Mi <= M; Mi++)
        {
            int action;
 
            scanf("%d",&action);
            if(action == 1)
            {
                int qL, qR;
                scanf("%d %d", &qL, &qR);
                printf("%d\n", querySum(root, 1, N, qL, qR) );
            }
            else if(action == 2)
            {
                int index, value;
                scanf("%d %d", &index, &value);
                updateNode(root, 1, N, index, value);
            }
        }
 
        destroyTree(root, 1, N);
    }
 
    return 0;
}
 
void buildTree(Node* &O, int L, int R)
{
    O = new Node;
 
    if(L == R)
    {
        O->sum = num[L];
        return;
    }
 
    int M = (L + R) / 2;
 
    buildTree(O->Lc, L, M);
    buildTree(O->Rc, M + 1, R);
 
    O->sum = O->Lc->sum + O->Rc->sum;
}
 
void destroyTree(Node* &O, int L, int R)
{
    if(L != R)
    {
        int M = (L + R) / 2;
 
        destroyTree(O->Lc, L, M);
        destroyTree(O->Rc, M + 1, R);
    }
 
    delete O;
}
 
int querySum(Node* O, int L, int R, int qL, int qR)
{
    if(R < qL || qR < L) return 0;
    if(qL <= L && R <= qR) return O->sum;
 
    int M = (L + R) / 2;
    int sumL = querySum(O->Lc, L, M, qL, qR);
    int sumR = querySum(O->Rc, M + 1, R, qL, qR);
 
    return sumL + sumR;
}
 
void updateNode(Node* O, int L, int R, int index, int value)
{
    if(L == R)
    {
        O->sum = value;
        return;
    }
 
    int M = (L + R) / 2;
 
    if(index <= M)
        updateNode(O->Lc, L, M, index, value);
    else
        updateNode(O->Rc, M + 1, R, index, value);
 
    O->sum = O->Lc->sum + O->Rc->sum;
 
}