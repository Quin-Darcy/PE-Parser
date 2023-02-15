#include "coffheader.h"

typedef unsigned char BYTE;
        
COFFHeader::COFFHeader(std::vector<BYTE> bytes_from_file, uint32_t offset) 
{
    base_address = offset;

    pe_signature = 0;
    pe_signature += bytes_from_file[base_address+3] << 24;
    pe_signature += bytes_from_file[base_address+2] << 16;
    pe_signature += bytes_from_file[base_address+1] << 8;
    pe_signature += bytes_from_file[base_address];

    machine = ((uint16_t)bytes_from_file[base_address+5] << 8) | bytes_from_file[base_address+4];
    number_of_sections = ((uint16_t)bytes_from_file[base_address+7] << 8) | bytes_from_file[base_address+6];

    time_date_stamp = 0;
    time_date_stamp += bytes_from_file[base_address+11] << 24; 
    time_date_stamp += bytes_from_file[base_address+10] << 16; 
    time_date_stamp += bytes_from_file[base_address+9] << 8; 
    time_date_stamp += bytes_from_file[base_address+8]; 

    pointer_to_symbol_table = 0;
    pointer_to_symbol_table += bytes_from_file[base_address+15] << 24;
    pointer_to_symbol_table += bytes_from_file[base_address+14] << 16;
    pointer_to_symbol_table += bytes_from_file[base_address+13] << 8;
    pointer_to_symbol_table += bytes_from_file[base_address+12];

    number_of_symbols = 0;
    number_of_symbols += bytes_from_file[base_address+19] << 24;
    number_of_symbols += bytes_from_file[base_address+18] << 16;
    number_of_symbols += bytes_from_file[base_address+17] << 8;
    number_of_symbols += bytes_from_file[base_address+16];
    
    size_of_optional_header = ((uint16_t)bytes_from_file[base_address+21] << 8) | bytes_from_file[base_address+20];
    characteristics = ((uint16_t)bytes_from_file[base_address+23] << 8) | bytes_from_file[base_address+22];
}