#include <stdio.h>
#include <stdlib.h>
#include "treeQuery.h"
int main()
{
    char instruction[MAXN];
    Node node[7];
    for(int i = 0; i < 7; i++){
        node[i].left = NULL;
        node[i].right = NULL;
    }
    node[0].data = 2;
    node[0].left = &node[1];
    node[1].data = 2;
    node[1].right = &node[2];
    node[2].data = 2;
    node[2].left = &node[3];
    node[2].right = &node[4];
    node[3].data = 1;
    node[3].left = &node[5];
    node[4].data = 1;
    node[4].right = &node[6];
    node[5].data = 1;
    node[6].data = 1;
    Node *root = &node[0];
    while (scanf("%s", instruction) != EOF) {
        printf("%d\n", query(root, instruction));
    }
    return 0;
}