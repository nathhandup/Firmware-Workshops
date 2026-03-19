#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main() {
    // What are the sizes of each type? 
    std::cout << "sizeof(int): " << sizeof(int) << "\n"; // On my system, 4bytes
    std::cout << "sizeof(char): " << sizeof(char) << "\n"; // On my system, 1Byte

    // Allocate a void pointer the size of an integer (4 Bytes)
    void * vpr = malloc(sizeof(int));

    int * ipr = (int *)vpr;
    *ipr = 5;
    std::cout << "Int: " << *ipr << "\n";

    char * cpr = (char *) vpr;
    cpr[0] = 'a';
    cpr[1] = 'b';
    cpr[2] = 'c';
    cpr[3] = 'd';
    for (int i = 0; i < 4; i++) {
        std::cout << "Char pointer at index " << i << " : " << cpr[i] << "\n";
    }

    // Will this be an error?
    // std::cout << "Int: " << *ipr << "\n";

    free(vpr);
    return 0;
}