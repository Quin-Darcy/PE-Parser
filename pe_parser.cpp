#include <iostream>
#include <vector>
#include <fstream>
#include "dosheader.h"
#include "coffheader.h"
#include "optheader.h"

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
    OPTHeader opt_header(bytes_from_file, coff_header.base_address+24);

    printf("\n%-25s 0x%x\n", "MagicNumber:", dos_header.e_magic);
    printf("%-25s 0x%x\n\n", "PESignature:", coff_header.pe_signature); 

    printf("%-25s 0x%x\n", "BaseAddress:", coff_header.base_address); 
    printf("%-25s 0x%x\n", "Machine:", coff_header.machine); 
    printf("%-25s %d\n", "NumberOfSections:", coff_header.number_of_sections); 
    printf("%-25s %d\n", "TimeDateStamp:", coff_header.time_date_stamp); 
    printf("%-25s 0x%x\n", "PointerToSymbolTable:", coff_header.pointer_to_symbol_table); 
    printf("%-25s %d\n", "NumberOfSymbols:", coff_header.number_of_symbols); 
    printf("%-25s %d\n", "SizeOfOptionalHeader:", coff_header.size_of_optional_header);  
    printf("%-25s 0x%x\n\n", "Characteristics:", coff_header.characteristics); 


    printf("%-25s 0x%x\n", "BaseAddress:", opt_header.base_address); 
    printf("%-25s 0x%x\n", "MagicNumber:", opt_header.magic_number); 
    printf("%-25s 0x%x\n", "MajorLinkerVersion:", opt_header.major_linker_version); 
    printf("%-25s 0x%x\n", "MinorLinkerVersion:", opt_header.minor_linker_version); 
    printf("%-25s %d\n", "SizeOfCode:", opt_header.size_of_code); 
    printf("%-25s %d\n", "SizeOfInitializedData:", opt_header.size_of_initialized_data); 
    printf("%-25s %d\n", "SizeOfUninitializedData:", opt_header.size_of_uninitialized_data); 
    printf("%-25s 0x%x\n", "AddressOfEntryPoint:", opt_header.address_of_entry_point);
    printf("%-25s 0x%x\n", "BaseOfCode:", opt_header.base_of_code);  

    if (opt_header.magic_number == 267)
    {
        printf("%-25s 0x%x\n\n", "BaseOfData:", opt_header.base_of_data);    
    }
    else
    {
        printf("\n");
    }

    printf("\n");

    return 0;
}
