#include <stdio.h>
#include <assert.h>
void snake(const int *ptr_array[100][100], int m);
int main()
{
  int array[100][100], check[100][100];
  const int *ptr_array[100][100];
  int i, j, m;
 
  scanf("%d", &m);
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      ptr_array[i][j] = &(array[i][j]);
      scanf("%d", &(array[i][j]));
      check[i][j] = array[i][j];
    }
 
  snake(ptr_array, m);
 
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      assert(check[i][j] == array[i][j]);
      assert((ptr_array[i][j] >= &array[0][0]) && (ptr_array[i][j] <= &array[99][99]));
      printf("%d ", *(ptr_array[i][j]));
    }
    printf("\n");
  }
 
  return 0;
}
void snake(const int *ptr_array[100][100], int m){
    const int* arr[m*m];
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            arr[m*i+j]= ptr_array[i][j];
        }
    }
    int flag = 1; 
    for(int i = 0; i < m*m-1 && flag == 1; i++) { 
        flag = 0; 
        for(int j = 0; j < m*m-i-1; j++) { 
            if(*arr[j+1]<*arr[j]) {
                const int* tmp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=tmp;
                flag = 1; 
            } 
        } 
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i%2==0){
               ptr_array[i][j]=arr[m*i+j]; 
            }
            else{
               ptr_array[i][m-j-1]=arr[m*i+j]; 
            }
        }
    }
    return;
}