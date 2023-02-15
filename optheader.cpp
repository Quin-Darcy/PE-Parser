#include "optheader.h"

typedef unsigned char BYTE;

OPTHeader::OPTHeader(std::vector<BYTE> bytes_from_file, uint32_t offset)
{
	base_address = offset;
	magic_number = ((uint16_t)bytes_from_file[base_address+1] << 8) | bytes_from_file[base_address];
	major_linker_version = bytes_from_file[base_address+2];
	minor_linker_version = bytes_from_file[base_address+3];

	size_of_code = 0;
    size_of_code += bytes_from_file[base_address+7] << 24;  
    size_of_code += bytes_from_file[base_address+6] << 16; 
    size_of_code += bytes_from_file[base_address+5] << 8; 
    size_of_code += bytes_from_file[base_address+4]; 

    size_of_initialized_data = 0;
    size_of_initialized_data += bytes_from_file[base_address+11] << 24;  
    size_of_initialized_data += bytes_from_file[base_address+10] << 16; 
    size_of_initialized_data += bytes_from_file[base_address+9] << 8; 
    size_of_initialized_data += bytes_from_file[base_address+8]; 

    size_of_uninitialized_data = 0;
    size_of_uninitialized_data += bytes_from_file[base_address+15] << 24;  
    size_of_uninitialized_data += bytes_from_file[base_address+14] << 16; 
    size_of_uninitialized_data += bytes_from_file[base_address+13] << 8; 
    size_of_uninitialized_data += bytes_from_file[base_address+12]; 

    address_of_entry_point = 0;
    address_of_entry_point += bytes_from_file[base_address+19] << 24;  
    address_of_entry_point += bytes_from_file[base_address+18] << 16; 
    address_of_entry_point += bytes_from_file[base_address+17] << 8; 
    address_of_entry_point += bytes_from_file[base_address+16]; 

    base_of_code = 0;
    base_of_code += bytes_from_file[base_address+23] << 24;  
    base_of_code += bytes_from_file[base_address+22] << 16; 
    base_of_code += bytes_from_file[base_address+21] << 8; 
    base_of_code += bytes_from_file[base_address+20]; 

    base_of_data = 0;
    if (magic_number == 267) 
    {
    	base_of_data += bytes_from_file[base_address+27] << 24;  
    	base_of_data += bytes_from_file[base_address+26] << 16; 
    	base_of_data += bytes_from_file[base_address+25] << 8; 
    	base_of_data += bytes_from_file[base_address+24];
    }
}