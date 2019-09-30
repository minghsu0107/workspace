#include <stdlib.h>
#include "treeStatistics.h"

//static int stk = -1;
void trace(Node *u, Answer *ret, int stk) {
	ChildList *c = u->list;
	//stk++;
	if (c != NULL)
		ret->InternalNode++;
	else
		ret->Leaf++;
	int branch = 0;
	while (c != NULL) {
		trace(c->node, ret, stk + 1);
		c = c->next;
		branch++;
	}
	if (branch > ret->MaxBranchFactor)
		ret->MaxBranchFactor = branch;
	if (stk > ret->Depth)
		ret->Depth = stk;
	//stk--;
}