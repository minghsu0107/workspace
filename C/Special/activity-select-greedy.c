#include <stdio.h>
#include <stdlib.h>
 
static int cmp(const void *x, const void *y) {
    Activity *a = (Activity *) x;
    Activity *b = (Activity *) y;
    if (a->end < b->end)
        return -1;
    if (a->end > b->end)
        return 1;
    return 0;
}
int select(Activity A[], int n) {
    if (n == 0)    return 0;
    qsort(A, n, sizeof(Activity), cmp);
    int ret = 0, r = A[0].start;
 
    for (int i = 0; i < n; i++) {
        if (A[i].start >= r) {
#ifdef PRINT
            printf("%d %d\n", A[i].start, A[i].end);
#endif           
            r = A[i].end, ret++;
        }
    }
    return ret;
}

/*
First you need to sort the activities according to their ending time. 
Then you keep selecting the activity with the earliest ending time, 
then removing any activities that overlap with with the activity you just selected. 
*/