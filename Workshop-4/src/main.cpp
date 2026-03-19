#include <iostream>
#include <fstream>

int main() {

    // Main goal of our program:
    // Create a char array of length 5 and store the information in a binary file, such that
    // the data created persists past the programs termination.

    // We will be using the fstream library to read and write to our .bin file.
    // If you are unfamiliar with the inner workings, and the functions, don't worry.
    // This program is meant to demonstrate how, commonly, blocks of contiguous or partitioned 
    // memory contain "headers" that give us vital information about the memory we are about to read.
    // For example, in this program, we store the length of our character array in the first byte 
    // written to data.bin, which tells future us exactly how much data we want to read / write.

    // Also, it is meant to show that we have complete control over this format!

    // Name of our .bin file
    const char* filename = "data.bin";

    // Allocate character array of length 5
    const unsigned char length = 5;
    char data[length];

    // Define our data.bin file as "infile"
    std::ifstream infile(filename, std::ios::binary);

    // Our data length, to be grabbed from the first byte of data.bin
    unsigned char fileLength;

    // Read length byte
    infile.read(reinterpret_cast<char*>(&fileLength), 1);

    // Read into our character array "length" amount of bytes.
    infile.read(data, length);
    std::cout << "Loaded data from file: ";

    // Print our data!
    for (int i = 0; i < length; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // Close our data.bin file
    infile.close();

    // MODIFY DATA 
    data[0] = 'X'; 
    data[1] = 'X'; 
    data[2] = 'B'; 
    data[3] = 'X'; 
    data[4] = 'X'; 


    // Again, define our data.bin file as "outfile", to write data. 
    std::ofstream outfile(filename, std::ios::binary);

    // Write length byte 
    outfile.write(reinterpret_cast<const char*>(&length), 1);

    // Write data bytes
    outfile.write(data, length);

    // Close file.
    outfile.close();

    std::cout << "Data saved to file.\n";

    return 0;
}