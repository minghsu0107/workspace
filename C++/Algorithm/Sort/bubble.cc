#include <iostream>
#include <algorithm>

void bubble_sort(int* array, int length)
{
    for (int i = length - 1; i > 0; --i)
    {
        bool swapped = false;
        for (int j = 0; j < i; ++j)
            if (array[j] > array[j + 1])
            {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        if(!swapped)
            break;
    }
 
}

int main() {
    int A[] = {9, 1, 3, 6, 4};
    bubble_sort(A, 5);
    for (auto &x: A) std::cout << x << " ";
}