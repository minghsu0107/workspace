#include <stdio.h>
#define MAXN 1024
const int A[MAXN][MAXN];
const int *B[MAXN][MAXN];
void constructPointerArray(const int A[1024][1024], const int *B[1024][1024], int N){
    const int **b = malloc(sizeof(const int*) * N*N);
    for(int i = 0; i < N; i++){
       for(int j = 0; j < N; j++){
           b[A[i][j]] = &A[i][j];
       }
    }
    //for(int i = 0;i<N*N;i++) printf("%d ",*b[i]);
    for(int i = 0; i < N; i++){
       for(int j = 0; j < N; j++){
           if(A[i][j]+1 == N*N) B[i][j] = b[0];
           else B[i][j] = b[A[i][j]+1];
		   // B[i][j] = b[(A[i][j]+1)%(N*N)];
       }
   }
}
int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    constructPointerArray(A, B, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d%c", *B[i][j], j == N - 1 ? '\n' : ' ');
        }
    }    
    return 0;
}
