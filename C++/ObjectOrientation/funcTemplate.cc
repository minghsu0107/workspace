#include <iostream> 
using namespace std; 

template <class X> // // or template <typename X>
void bubbleSort(X[], int); 

int main() { 
    int iarr[] = {5, 3, 11, 6, 8, 9, 20, 11}; 
    float farr[] = {5.1, 3.4, 11.3, 6.6, 8.9, 9.11, 20.2, 11.4}; 

    bubbleSort(iarr, 8); 
    for(int i = 0; i < 8; i++) 
        cout << " " << iarr[i]; 
    cout << endl; 

    bubbleSort(farr, 8); 
    for(int i = 0; i < 8; i++) 
        cout << " " << farr[i]; 
    cout << endl; 
 
    return 0; 
} 

template <class X> // or template <typename X>
void bubbleSort(X number[], int length) { 
    int i, j, k, flag = 1; 
    X tmp; 

    for(i = 0; i < length-1 && flag == 1; i++) { 
        flag = 0; 
        for(j = 0; j < length-i-1; j++) { 
            if(number[j+1] < number[j]) { 
                tmp = number[j]; 
                number[j] = number[j+1]; 
                number[j+1] = tmp; 
                flag = 1; 
            } 
        } 
    } 
}