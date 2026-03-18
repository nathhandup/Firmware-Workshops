#include <iostream>
#include <fstream>

int main() {
    const char* filename = "data.bin";

    // Allocate array of length 5
    const unsigned char length = 5;
    char data[length];

    // -------- LOAD FROM FILE --------
    std::ifstream infile(filename, std::ios::binary);

    unsigned char fileLength;

    // Read length byte
    infile.read(reinterpret_cast<char*>(&fileLength), 1);

    infile.read(data, length);
    std::cout << "Loaded data from file: ";
    for (int i = 0; i < length; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    infile.close();

    // MODIFY DATA 
    data[0] = 'X'; 
    data[1] = 'X'; 
    data[2] = 'X'; 
    data[3] = 'X'; 
    data[4] = 'X'; 

    // SAVE TO FILE 
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error opening file for writing.\n";
        return 1;
    }

    // Write length byte
    outfile.write(reinterpret_cast<const char*>(&length), 1);

    // Write data bytes
    outfile.write(data, length);

    outfile.close();

    std::cout << "Data saved to file.\n";

    return 0;
}