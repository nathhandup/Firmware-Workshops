#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main() {
    // What are the sizes of each type? 
    std::cout << "sizeof(int): " << sizeof(int) << "\n"; // On my system, 4bytes
    std::cout << "sizeof(char): " << sizeof(char) << "\n"; // On my system, 1Byte

    // Allocate a void pointer the size of an integer (4 Bytes)
    void * vpr = malloc(sizeof(int));
    // KEY: we cannot deallocate this pointer as is. Our compiler does not know what to do when we dereference this pointer.
    // When we dereference an int *, our compiler knows we are looking at the 4 bytes of memory that follow this address.
    // However, void pointers are unique, and have dynamic size. Therefore, there is no defined size. 

    // Now, with this pointer, we could either cast it as an integer pointer, or a char array of size 4.
    // We could also treat it as any data type LESS than 4 bytes, but we run the risk of memory leaks. 
    // So, we'll do both. Cast it as an integer, and then use the same pointer and cast it as a char array. 
    
    // Cast as an integer pointer
    int * ipr = (int *)vpr;
    // We can now dereference and set a value
    *ipr = 5;
    // Prints 5!
    std::cout << "Int: " << *ipr << "\n";

    // Now we recast our void pointer as a char pointer. 
    char * cpr = (char *) vpr;
    // This overwrites each byte previously written when we casted our pointer as an integer.
    cpr[0] = 'a';
    cpr[1] = 'b';
    cpr[2] = 'c';
    cpr[3] = 'd';
    // Print all locations!
    for (int i = 0; i < 4; i++) {
        std::cout << "Char pointer at index " << i << " : " << cpr[i] << "\n";
    }

    // Let's try to print our integer pointer. What do we think will happen?
    std::cout << "Int: " << *ipr << "\n";
    // This line now prints "1684234849. Very specific number, Can we guess why this happens?
    // Hint:    'a' as a byte: 01100001
    //          'b' as a byte: 01100010 
    //          'c' as a byte: 01100011 
    //          'd' as a byte: 01100100 
    // Lined up: 01100001 01100010 01100011 01100100
    // Think about how we read binary. 

    free(vpr);
    return 0;
}