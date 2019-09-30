#include <stdio.h>
#define MAXN 1024
const int A[MAXN][MAXN];
const int *B[MAXN][MAXN];
int x[MAXN*MAXN];
int y[MAXN*MAXN];
void constructPointerArray(const int A[1024][1024], const int *B[1024][1024], int N){
    for(int i = 0; i < N; i++){
       for(int j = 0; j < N; j++){
           x[A[i][j]] = i;
           y[A[i][j]] = j;
       }
    }
    for(int i = 0; i < N; i++){
       for(int j = 0; j < N; j++){
           if(A[i][j]+1 == N*N) {
               B[i][j] = &A[x[0]][y[0]];
           }
           else {
               int newr = x[A[i][j]+1], newc = y[A[i][j]+1];
               B[i][j] = &A[newr][newc];
           }
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
