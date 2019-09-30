#include"memory.h"
 
int main() {
        Memory myMemory;
        initMemory(&myMemory, 100);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 50, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 70, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 0, 10);
        printMemory(&myMemory);
        allocateMemory(&myMemory, 30, 10);
        printMemory(&myMemory);
        return 0;
}