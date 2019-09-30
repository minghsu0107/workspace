#include <stdio.h>
int evaluate_f(int *iptr[], int n, int *index){
    int max=-100;
    for(int i=0;i<n;i++){
        if(4*iptr[i][0]-6*iptr[i][1]>max){
            max = 4*iptr[i][0]-6*iptr[i][1];
            *index = i;
        }
    }
    return max;
}
int main(){
  int a[] = { 9, 7 };
  int b[] = { 3, 2 };
  int c[] = { 3, 2 };
  int d[] = { 9, 7 };
  int *iptr[] = { a, b, c, d };
  int max, index;
  max = evaluate_f(iptr, 4, &index);
  printf("%d %d\n", max, index);
  return 0;
}