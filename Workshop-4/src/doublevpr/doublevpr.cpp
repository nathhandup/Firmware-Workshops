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
    void ** vpr = (void **)malloc(24);
    // Why is this allowed? Aren't we dereferencing? 
    *vpr = malloc(4); 
    *(vpr + 1) = malloc(1);
    *(vpr + 2) = malloc(4);

    // Make sure to cast!
    int * ipr = (int *)vpr[0];
    char * cpr = (char *)vpr[1];
    float * fpr = (float *)vpr[2];

    *ipr = 1;
    *cpr = 'a';
    *fpr = 1.1f;

    // What will happen?
    std::cout << "*ipr: " << *ipr << "\n"; 
    std::cout << "*cpr: " << *cpr << "\n"; 
    std::cout << "*fpr: " << *fpr << "\n"; 

    // What do we expect from this? Do they have definite sizes?
    std::cout << "sizeof(void *): " << sizeof(void *) << "\n"; 
    std::cout << "sizeof(void **): " << sizeof(void **) << "\n";

    
    free(vpr[0]);
    free(vpr[1]);
    free(vpr[2]);
    free(vpr);
    return 0;
}