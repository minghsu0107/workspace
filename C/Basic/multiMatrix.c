#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 1000
void matrix_multiplication(int N, int **ptrA, int M, int **ptrB, int S, int *result){
    // 稀疏矩陣(sparse matrix)
    for(int i=0; i < S * S; ++i) // result is a S*S matrix
        result[i] = 0;
    for(int i = 0; i < N; ++i){ // A的非零元素有N個(至多S*S個)
        for(int j = 0 ; j < M ; ++j) // B的非零元素有M個(至多S*S個)
            if(ptrA[2][i] == ptrB[1][j])  // 當A矩陣的c等於B矩陣的r
                    result[ptrA[1][i] * S + ptrB[2][j]] += ptrA[0][i] * ptrB[0][j];
                    // A的r為result矩陣的r B的c為result矩陣的c 
    }
    return;
}
void matrix_multiplication2(int N, int **ptrA, int M, int **ptrB, int S, int *result){
        int A[S][S];
        int B[S][S];
        for(int i = 0; i < S; ++i)
                for(int j = 0; j < S; ++j)
                        A[i][j] = 0, B[i][j] = 0;
        for(int i = 0; i < N; ++i)
                A[ptrA[1][i]][ptrA[2][i]] = ptrA[0][i];
        for(int i = 0; i < M; ++i)
                B[ptrB[1][i]][ptrB[2][i]] = ptrB[0][i];
        for(int i = 0; i < S * S; ++i)
                result[i] = 0;
        for(int i = 0; i < S; ++i)
                for(int j = 0; j < S; ++j)
                        for(int k = 0; k < S; ++k)
                                result[i * S + k] += A[i][j] * B[j][k];
 
}
static int A_elements[MAX], A_rowind[MAX], A_colind[MAX];
static int B_elements[MAX], B_rowind[MAX], B_colind[MAX];
int main(int argc, char const *argv[])
{   
    int N, M, S;
    assert(scanf("%d %d %d", &N, &M, &S) == 3);
 
    int *ptrA[3];
    int *ptrB[3];
    ptrA[0] = A_elements, ptrA[1] = A_rowind, ptrA[2] = A_colind;
    ptrB[0] = B_elements, ptrB[1] = B_rowind, ptrB[2] = B_colind;
 
    for(int i = 0; i < N; ++i)
        assert(scanf("%d", &A_elements[i]) == 1);
    for(int i = 0; i < N; ++i)
        assert(scanf("%d", &A_rowind[i]) == 1);   
    for(int i = 0; i < N; ++i)
        assert(scanf("%d", &A_colind[i]) == 1);           
    for(int i = 0; i < M; ++i)
        assert(scanf("%d", &B_elements[i]) == 1);
    for(int i = 0; i < M; ++i)
        assert(scanf("%d", &B_rowind[i]) == 1);   
    for(int i = 0; i < M; ++i)
        assert(scanf("%d", &B_colind[i]) == 1);
 
    int *result = malloc(S*S*sizeof(int));
    matrix_multiplication(N, ptrA, M, ptrB, S, result);
    for (int i = 0; i < S; ++i)
        for (int j = 0; j < S; ++j)
              printf("%d%c", result[i * S + j], " \n"[j == S - 1]);
    return 0;
}