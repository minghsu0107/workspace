#include <stdio.h>
void merge(int A[], int B[], int* a[], int* b[]){
     int i = 0, j = 0;
     int alen = 1, blen = 1;
     for(int q = 0; a[q]!=NULL;q++){
         alen++;
     }
     for(int p = 0; b[p]!=NULL;p++){
         blen++;
     }
     while ( i < alen  && j < blen ){
        if (A[i] < B[j]){
            if(i+1 < alen){
                if(A[i+1]>B[j]) a[i] = &B[j]; 
            }
            else{
                a[i] = &B[j];
            }
            i++;
        }
        else{
            if(j+1 < blen){
                if(B[j+1]>A[i]) b[j] = &A[i]; 
            }
            else{
                b[j] = &A[i];
            }
            j++;
        }
     }

}
int main()
{
    int A[10], B[10];
    int *a[10], *b[10], *ans_a[10], *ans_b[10];
    int i, N, M;
 
    scanf("%d%d", &N, &M);
    for(i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for(i = 0; i < M; i++)
        scanf("%d", &B[i]);
    for(i = 0; i < N-1; i++)
        a[i] = &A[i+1];
    a[N-1] = NULL;
    for(i = 0; i < M-1; i++)
        b[i] = &B[i+1];
    b[M-1] = NULL;
 
    merge(A, B, a, b);
 
    ans_a[0] = &B[0]; ans_a[1] = &A[2]; ans_a[2] = &B[1]; ans_a[3] = &B[2];
    ans_b[0] = &A[1]; ans_b[1] = &A[3]; ans_b[2] = NULL;
 
    for(i = 0; i < N; i++){
        if(a[i] != ans_a[i])
            printf("a[%d] is Wrong!\n", i);
    }
    for(i = 0; i < M; i++){
        if(b[i] != ans_b[i])
            printf("b[%d] is Wrong!\n", i);
    }
    printf("Finish!\n");
    int flag = -1, x = 0, y = 0;
    int *tmp;
    if(A[x] < B[y]){
        tmp = &A[x];
        flag = 0;
        x++;
    }else{
        tmp = &B[y];
        flag = 1;
        y++;
    }
    printf("%d",*tmp);
    if(!flag){
        tmp = a[tmp-A];
    }else{
        tmp = b[tmp-B];
    }
    while(tmp != NULL){
        printf(" %d",*tmp);
        if(A[x] < B[y]){
          flag = 0;
          x++;
        }else{
          flag = 1;
          y++;
        }
        if(!flag){
           tmp = a[tmp-A];
        }else{
           tmp = b[tmp-B];
        }
    }
    return 0;
}
