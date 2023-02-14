#include "coffheader.h"

typedef unsigned char BYTE;
        
COFFHeader::COFFHeader(std::vector<BYTE> bytes_from_file, long pe_os) 
{
    pe_offset = pe_os;

    pe_signature = 0;
    pe_signature += bytes_from_file[pe_offset+3] << 24;
    pe_signature += bytes_from_file[pe_offset+2] << 16;
    pe_signature += bytes_from_file[pe_offset+1] << 8;
    pe_signature += bytes_from_file[pe_offset];

    machine = ((uint16_t)bytes_from_file[pe_offset+5] << 8) | bytes_from_file[pe_offset+4];
    number_of_sections = ((uint16_t)bytes_from_file[pe_offset+7] << 8) | bytes_from_file[pe_offset+6];

    time_date_stamp = 0;
    time_date_stamp += bytes_from_file[pe_offset+11] << 24; 
    time_date_stamp += bytes_from_file[pe_offset+10] << 16; 
    time_date_stamp += bytes_from_file[pe_offset+9] << 8; 
    time_date_stamp += bytes_from_file[pe_offset+8]; 

    pointer_to_symbol_table = 0;
    pointer_to_symbol_table += bytes_from_file[pe_offset+15] << 24;
    pointer_to_symbol_table += bytes_from_file[pe_offset+14] << 16;
    pointer_to_symbol_table += bytes_from_file[pe_offset+13] << 8;
    pointer_to_symbol_table += bytes_from_file[pe_offset+12];

    number_of_symbols = 0;
    number_of_symbols += bytes_from_file[pe_offset+19] << 24;
    number_of_symbols += bytes_from_file[pe_offset+18] << 16;
    number_of_symbols += bytes_from_file[pe_offset+17] << 8;
    number_of_symbols += bytes_from_file[pe_offset+16];
    
    size_of_optional_header = ((uint16_t)bytes_from_file[pe_offset+21] << 8) | bytes_from_file[pe_offset+20];
    characteristics = ((uint16_t)bytes_from_file[pe_offset+23] << 8) | bytes_from_file[pe_offset+22];
}