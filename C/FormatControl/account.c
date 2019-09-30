#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define AGE 1
#define ZIPCODE 2
 
int fsize(FILE *fp) {
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return size;
}
int bcmp(const void *a, const void *b) {
    Account *x = (Account *) a;
    Account *y = (Account *) b;
    if (x->accountNum < y->accountNum)
        return -1;
    if (x->accountNum > y->accountNum)
        return 1;
    return 0;
}
int cmp(const void *a, const void *b) {
    Account *x = (Account *) a;
    Account *y = (Account *) b;
#if !defined(SORTBY) || (defined(SORTBY) && SORTBY == ZIPCODE)
// if SORTBY is not defined or SORTBY is defined and equals to ZIPCODE
    if (x->zipcode < y->zipcode)
        return -1;
    if (x->zipcode > y->zipcode)
        return 1;
#elif defined SORTBY && SORTBY == AGE
    if (x->age < y->age)
        return -1;
    if (x->age > y->age)
        return 1;
#endif
    return 0;
}
int main() {
    char fileName[128];
    scanf("%s", fileName);
    FILE *fin = fopen(fileName, "rb");
    assert(fin != NULL);
    int n = fsize(fin) / sizeof(Account);
    Account *A = (Account*) malloc(sizeof(Account) * n);
    fread(A, sizeof(Account), n, fin);
 
    qsort(A, n, sizeof(Account), bcmp);
    printf("account, age, zipcode, balance\n");
    for (int i = 0; i < n; i++) {
        printf("%d, %d, %d, %d\n", A[i].accountNum,
            A[i].age, A[i].zipcode, A[i].balance);
    }
 
    qsort(A, n, sizeof(Account), cmp);
#if defined(SORTBY) && SORTBY == ZIPCODE
    printf("zipcode, sum_balance\n");
#elif defined(SORTBY) && SORTBY == AGE
    printf("age, sum_balance\n");
#endif
    for (int i = 0; i < n; i++) {
        int j = i, sum = 0;
#if defined(SORTBY) && SORTBY == ZIPCODE
        while (j < n && A[j].zipcode == A[i].zipcode)
            sum += A[j].balance, j++;
        i = j-1;
        printf("%d, %d\n", A[i].zipcode, sum);
#elif defined(SORTBY) && SORTBY == AGE
        while (j < n && A[j].age == A[i].age)
            sum += A[j].balance, j++;
        i = j-1;
        printf("%d, %d\n", A[i].age, sum);
#endif
    }
 
    free(A);
    return 0;
}