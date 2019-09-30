// 小寫是運算元，大寫是運算子。
// 給一個 post-order 輸出 level-order。
// 使用遞迴建樹，之後用 queue 找到 level-order
#include <stdio.h>
#include <string.h>
char post[10005], pre[10005], tree[10005];
// tree[node_index] saves the content of that node
int node[10005][2]; 
// node[i][0] saves the node_index of the left child
// node[i][1] saves the node_index of the right child
int ptr, node_idx;
void build_by_post(int nd) {
    tree[nd] = post[ptr--];
    // variables are always leaves
    if(tree[nd] >= 'a' && tree[nd] <= 'z')
        return;
    node[nd][1] = ++node_idx;
    build_by_post(node_idx);
    node[nd][0] = ++node_idx;
    build_by_post(node_idx);
}
void build_by_pre(int nd) {
    tree[nd] = pre[ptr++];
    // variables are always leaves
    if(tree[nd] >= 'a' && tree[nd] <= 'z')
        return;
    node[nd][0] = ++node_idx;
    build_by_pre(node_idx);
    node[nd][1] = ++node_idx;
    build_by_pre(node_idx);
}
int main() {
    int t, flag, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &flag);
        node_idx = 1;
        if (flag) {
            scanf("%s", post);
            ptr = strlen(post) - 1;
            build_by_post(node_idx);
        }
        else {
            scanf("%s", pre);
            ptr = 0;
            build_by_pre(node_idx);
        }
        int qu[10005], qidx = 0;
        qu[0] = 1;
        for(i = 0; i <= qidx; i++) {
            // leaves have no children
            if(tree[qu[i]] >= 'a' && tree[qu[i]] <= 'z')
                continue;
            qu[++qidx] = node[qu[i]][0];
            qu[++qidx] = node[qu[i]][1];
        }
        // level order
        for(i = 0; i <= qidx; i++)
            putchar(tree[qu[i]]);
        puts("");
    }
    return 0;
}
/*
Sample input:
3 
1
xyPzwIM
1
abcABdefgCDEF
0
ZYaXcbd

Sample Output:

MPIxyzw
FBEaAdDbceCfg
ZYdaXcb
*/