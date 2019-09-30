#include <stdio.h>
#include <stdlib.h>
int tail[100000];
void split(int A[], int *a[], int *head[], int k){ 
    int Alen = 1;
    for(Alen = 0 ; a[Alen] != NULL ; Alen++);
    for(int i = 0;i<k;i++){
        head[i] = NULL;
        tail[i] = -1;
    }
    for(int i = 0;i<Alen;i++){
        int idx = A[i]%k;
        if(tail[idx] == -1) head[idx] = &A[i];
        else a[tail[idx]] = &A[i];
        tail[idx] = i;
        a[tail[idx]] = NULL;
    }
    return;
}
int **last[100001] = {NULL};
void split2(int A[], int *a[], int *head[], int k){
    int Alen = 1;
    for(Alen = 0 ; a[Alen] != NULL ; Alen++);
    for(int i = 0 ; i < k ; i++)
        head[i] = NULL;
    for(int i = 0 ; i < Alen ; i++){
        int idx = A[i] % k;
        if(last[idx] == NULL) head[idx] = &A[i];
        else *last[idx] = &A[i];
        last[idx] = &a[i];
        *last[idx] = NULL;
    }
}
int main(int argc, char const *argv[])
{
    int N, k;
    scanf("%d%d", &N, &k);
    int A[N];
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    int *a[N], *head[k];
    for (int i = 0; i < N-1; ++i)
        a[i] = &A[i+1];
    a[N-1] = NULL;
    for (int i = 0; i < k; ++i)
        head[i] = NULL;
    split(A, a, head, k);
    for (int i = 0; i < k; ++i) {
        if (head[i] == NULL)
            printf("NULL\n");
        else {
            int *tmp = head[i]; // tmp指標指向該list的所有元素的位址
            printf("%d", *tmp); // 印出元素
            tmp = *(tmp-A+a);   // tmp = a[tmp-A] (對應此元素的a[]存的是下一個元素的位址)
            while (tmp != NULL) {
                printf(" %d", *tmp);
                tmp = *(tmp-A+a);
            }
            printf("\n");
        }
    }
    return 0;
}
