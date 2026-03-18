#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main() {
    // Main goal of this block of code:
    // Allocate an array, which have the following pointers stored within, in the given order:
    // An integer pointer,
    // A char pointer,
    // A float pointer.
    // Set their values and read them.

    // What are the sizes of each type? 
    std::cout << "sizeof(int): " << sizeof(int) << "\n"; // On my system, 4bytes
    std::cout << "sizeof(char): " << sizeof(char) << "\n"; // On my system, 1Byte
    std::cout << "sizeof(float): " << sizeof(float) << "\n"; // On my system, 4Byte

    // What are the sizes of each types pointer?
    std::cout << "sizeof(int *): " << sizeof(int *) << "\n"; // On my system, 8bytes
    std::cout << "sizeof(char *): " << sizeof(char *) << "\n"; // On my system, 8Byte
    std::cout << "sizeof(float *): " << sizeof(float *) << "\n"; // On my system, 8byte

    // Create a double void pointer of size 24bytes (for each pointer)
    // We will treat void **, our double pointer, as an array of pointers. If we want 3 slots for 3 pointers, we should allocate
    // 24 bytes, 8 bytes * 3.
    void ** vpr = (void **)malloc(24);
    // Why is this allowed? Aren't we dereferencing? 

    // Well, as we will see towards the end, void pointers (void *) and void double pointers (void **) DO have 
    // definite sizes. On my system, that is 8 bytes, same as our integer, char and float pointers.
    // So, when you dereference a void **, the compiler knows that a void * of size 8 bytes awaits on the other side
    // of the memory address. 

    // This is also why we are allowed to do pointer arithmetic here, and treat it as a normal array. 
    // Our compiler knows that each void* stored in this array is 8 bytes, so, heres what happens when
    // we use normal pointer arithmetic:

    // vpr[0] starts at the beginning of our allocated memory, and reads 8 bytes forward.
    // vpr[1] adds exactly 8 bytes to our beginning address, and reads 8 bytes forward.
    // vpr[2] adds exactly 16 bytes to our beginning address, and reads 8 bytes forward.

    // Let's allocate some memory each pointer in our array. We didn't do that yet!
    *vpr = malloc(4);
    *(vpr + 1) = malloc(1);
    *(vpr + 2) = malloc(4);

    // Make sure to cast!
    int * ipr = (int *)vpr[0];
    char * cpr = (char *)vpr[1];
    float * fpr = (float *)vpr[2];

    // Set our values
    *ipr = 1;
    *cpr = 'a';
    *fpr = 1.1f;

    // What happened? Will they be set properly?
    std::cout << "*ipr: " << *ipr << "\n"; 
    std::cout << "*cpr: " << *cpr << "\n"; 
    std::cout << "*fpr: " << *fpr << "\n"; 

    // Here is the exact size of each pointer. 
    std::cout << "sizeof(void *): " << sizeof(void *) << "\n"; // On my system, 8bytes!
    std::cout << "sizeof(void **): " << sizeof(void **) << "\n"; // On my system, 8bytes!

    // Our main takeaway:
    // We can dereference a void ** because we know the size of each void * waiting for us on the other size.
    // We CANNOT dereference a void* because we DO NOT know the size of the block of memory awaiting us on the other side.

    free(vpr[0]);
    free(vpr[1]);
    free(vpr[2]);
    free(vpr);
    return 0;
}