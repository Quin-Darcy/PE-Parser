#include <iostream>
#include <vector>
#include <fstream>
#include "dosheader.h"
#include "coffheader.h"

typedef unsigned char BYTE;


static std::vector<BYTE> get_bytes(char const *filename)
{
    // Open the file as an ifstream object ifs
    // ios::binary - open file in binary mode and ignore newlines
    // ios::ate - open and seek to end immediately after opening 
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);

    // Get position of file pointer, i.e., length
    std::ifstream::pos_type file_length = ifs.tellg();

    // If file has 0 length, return empty vector
    if (file_length == 0)
    {
        return std::vector<BYTE>{};
    }

    // Create vector of size length
    std::vector<BYTE> bytes_from_file(file_length);

    // Move file pointer back to beginning of stream
    ifs.seekg(0, std::ios::beg);

    // Read contents of file into vector
    ifs.read((char *) &bytes_from_file[0], file_length);

    return bytes_from_file;
}

int main(int argc, char* argv[])
{
    char const *file_path;
    std::vector<BYTE> bytes_from_file;

    if (argc != 2) 
    {
        printf("[Usage] ./pe_parser </path/to/file>\n");
        return -1;
    }
    else 
    {
        file_path = argv[1];
    }

    bytes_from_file = get_bytes(file_path);

    DOSHeader dos_header(bytes_from_file);
    COFFHeader coff_header(bytes_from_file, dos_header.e_lfanew);

    printf("Magic Number: 0x%02X\n", dos_header.e_magic);
    printf("PE Signature: 0x%02X\n\n", coff_header.pe_signature); 
    printf("Machine: 0x%02X\n", coff_header.machine); 
    printf("NumberOfSections: %d\n", coff_header.number_of_sections); 
    printf("TimeDateStamp: %d\n", coff_header.time_date_stamp); 
    printf("PointerToSymbolTable: 0x%02X\n", coff_header.pointer_to_symbol_table);
    printf("NumberOfSymbols: %d\n", coff_header.number_of_symbols);
    printf("SizeOfOptionalHeader: %d\n", coff_header.size_of_optional_header);
    printf("Characteristics: 0x%02X\n", coff_header.characteristics);


    return 0;
}
