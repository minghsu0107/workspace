// bottom-up
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
 
const int MAXN = 100000;
int segtree[MAXN * 4] = {}; 
                            //PS 此處以陣列實作二元樹，也可以用類似鏈結串列的方法實作
inline int p(int node){ return node / 2; }
inline int lc(int node){ return node * 2; }
inline int rc(int node){ return node * 2 + 1; }
 
/*
目標區間 和 當下區間 只可能有三種情況
1. 當下區間 在 目標區間 內，此時返回 當下區間 MAX，代表當下區間對組成目標有貢獻
2. 當下區間 在 目標區間 外，此時返回 -1(答案最小為0)，代表當下區間跟目標完全無關
3. 當下區間 和 目標區間 有重疊，則把當下區間切成兩小塊，遞迴下去，
   試著找出可用的子區間以組成目標區間，並將無用的捨棄
*/
int queryMax(int node, int L, int R, int qL, int qR)
{
    if(qL <= L && R <= qR) return segtree[node]; // 1
    if(R < qL || qR < L) return -1; // 2
    // 3
    int M = (L + R) / 2;
    int L_res = queryMax(lc(node), L, M, qL, qR);
    int R_res = queryMax(rc(node), M + 1, R, qL, qR);
 
    return max(L_res, R_res);
}
/*
從最下層的葉子往上更新直到根
*/
void updateNode(int node)
{
    if(node == 0) return;
 
    int L_max = segtree[lc(node)];
    int R_max = segtree[rc(node)];
 
    segtree[node] = max(L_max, R_max);
    updateNode(p(node));
}
 
int main()
{
    int N, Q;
    int action;
    int index, value;
    int qL, qR;
    int size = 1;
 
    scanf("%d %d", &N, &Q);
 
    // Build SegmentTree(bottom-up) 也可用top-down動態建造線段樹
    while(size < N) size *= 2;
    // read in the bottom nodes
    for(int i = 0; i < N; i++)
        scanf("%d", &segtree[size+i]);
    // start building trees from level h-1 to 0
    for(int i = size - 1; i >= 1; i--)
        segtree[i] = max(segtree[lc(i)], segtree[rc(i)]);
 
    while(Q--)
    {
        scanf("%d", &action);
 
        if(action == 1)
        {
            scanf("%d %d", &index, &value);
            int node = size + index - 1; // index starts from 1
            segtree[node] = value; // modify the bottom node
            updateNode(p(node));
        }
        else if(action == 2)
        {
            scanf("%d %d", &qL, &qR);
            printf("%d\n", queryMax(1, 1, size, qL, qR));
        }
    }   
 
    return 0;
}