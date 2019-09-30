#include <stdio.h>

int **first[100];
int *second[1000000];

int ***constructTable(int A[], int B[])
{
  int ***firstPtr = first;
  int **secondPtr = second;
  //int ***firstPtr = (int ***) malloc(sizeof(int**) * 100);
  // int ***head = firstPtr;
  //int **secondPtr = (int **) malloc(sizeof(int*) * 1000000);
  int *Bptr = B;
  // 將移動的指標的值設為陣列首的位址 當指標移動時即可拜訪陣列中每一元素的位址
  // 當我們將*Ptr設為某值 意義為將Ptr拜訪到的元素內容指定為該值 
  for (int i = 0; A[i] != 0; i++) {
    *firstPtr++ = secondPtr;
    for (int j = 0; j < A[i]; j++) {
      *secondPtr++ = Bptr;
      while (*Bptr != 0) Bptr++;
      Bptr++;            /* skip 0 */
    }
    *secondPtr++ = NULL;
  }
  *firstPtr = NULL;
  return first;
  // return head;
}
 
int main(){
    int N, M;
    int A[100] = {}, B[500] = {};
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for(int i = 0; i < M; i++)
        scanf("%d", &B[i]);
 
    int ***ptr;
    ptr = constructTable(A, B);
    for(int i = 0; *(ptr+i) != NULL; i++)
        for(int j = 0; j < A[i]; j++)
            for(int k = 0; *(*(*(ptr+i)+j)+k) != 0; k++)
                printf("%d ", *(*(*(ptr+i)+j)+k));
    return 0;
}