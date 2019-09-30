#include <stdio.h>
void prepare_array(int buffer[], int *array[], int row, int column[]){
  int sum=0;
  for(int i=0;i<row;i++){
    array[i]=&buffer[sum];
    sum+=column[i];
  }
  return;
}
int main(){
    int row = 4;
    int column[4] = {10, 20, 30, 10};// columns in each row can be diferrent
    int *array[50];
    int buffer[10000]; // buffer 裡面放所有的元素
    prepare_array(buffer, array, row, column);
    for (int i = 0; i < 4; i++)
     for (int j = 0; j < column[i]; j++)
       array[i][j] = i * 100 + j;  // array[i][j] == *(array[i]+j) == *(*(array+i)+j)
       
    for (int i = 0; i < 4; i++){
       int sum=0;
       for (int j = 0; j < column[i]; j++){
           printf("%d",buffer[sum+j]);
       }
       sum+=column[i];
       puts("");
    }
     
    return 0;
}