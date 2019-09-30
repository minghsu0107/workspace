#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for(int j = front; j < end; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[end]);
    return i + 1;
}
void sort(int arr[], int front, int end) {
    if (front >= end) return;
    int index = partition(arr, front, end);
    sort(arr, front, index-1);
    sort(arr, index+1, end);
}
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
}
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7}; 
	int arr_size = sizeof(arr)/sizeof(arr[0]); 

	printf("Given array is \n"); 
	printArray(arr, arr_size); 

	sort(arr, 0, arr_size - 1); 

	printf("\nSorted array is \n"); 
	printArray(arr, arr_size); 
	return 0; 
}