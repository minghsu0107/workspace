#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define OUTOFBOUND -2147483648
#define HAVENOTSET -2147483647
#define SETSUCCESS 1
typedef struct {
    int val, has;
} ELE;
typedef struct {
    ELE dat[2048];
    int l, r;
} ARRAY;
static int outOfBound(int x, int l, int r) {
    return x < l || x > r;
}
static int cmp(const void *x, const void *y) {
    ELE *a = (ELE*) x, *b = (ELE*) y;
    if (a->has != b->has)    return a->has - b->has;
    return a->val - b->val;
}
void init(ARRAY *a,  int l, int r) {
    a->l = l, a->r = r;
    memset(a->dat, 0, sizeof(a->dat));
}
int set(ARRAY *a, int index, int value) {
    if (outOfBound(index, a->l, a->r))
        return OUTOFBOUND;
    a->dat[index - a->l].has = 1;
    a->dat[index - a->l].val = value;
    return SETSUCCESS;
}
int get(ARRAY *a, int index) {
    if (outOfBound(index, a->l, a->r))
        return OUTOFBOUND;
    if (!a->dat[index - a->l].has)
        return HAVENOTSET;
    return a->dat[index - a->l].val;
}
void print(ARRAY *a) {
    for (int i = a->l, j = 0; i <= a->r; i++, j++) {
        if (a->dat[j].has)    printf("%d\n", a->dat[j].val);
        else                printf("No value\n");
    }
}
void sort(ARRAY *a) {
    qsort(a->dat, a->r - a->l + 1, sizeof(ELE), cmp);
}
void test_specall() {
    int n, l, r;
    int cmds, cmd, aid;
    int index, value;
    scanf("%d", &n);
    ARRAY *a = (ARRAY *) malloc(sizeof(ARRAY)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l, &r);
        init(&a[i], l, r);
    }
    scanf("%d", &cmds);
    for (int i = 0; i < cmds; i++) {
        scanf("%d %d", &cmd, &aid);
        if (cmd == 1) {
            print(&a[aid]);
        } else if (cmd == 2) {
            scanf("%d %d", &index, &value);
            int ret = set(&a[aid], index, value);
            printf("ARRAY ID %d, set(%d, %d) %s\n", aid, index, value,
                ret == SETSUCCESS ? "SUCCESS" : (ret == OUTOFBOUND ? "OUTOFBOUND" : "HAVENOTSET"));
        } else if (cmd == 3) {
            scanf("%d", &index);
            int ret = get(&a[aid], index);
            printf("ARRAY ID %d, get(%d) ", aid, index);
            if (ret == OUTOFBOUND)   
                printf(": OUTOFBOUND\n");
            else if (ret == HAVENOTSET)
                printf(": HAVENOTSET\n");
            else
                printf("= %d\n", ret);
        } else if (cmd == 4) {
            sort(&a[aid]);
        } else {
            assert(0);
        }
    }
}
int main() {
    int spec = 0;
    void (*FUNC[])() = {test_specall};
    FUNC[spec]();
    return 0;
}