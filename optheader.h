#ifndef OPTHEADER_H
#define OPTHEADER_H
#include <iostream>
#include <vector>
#include <fstream>

typedef unsigned char BYTE;

class OPTHeader
{
	public:
		uint16_t base_address;
		uint16_t magic_number;
		uint8_t major_linker_version;
		uint8_t minor_linker_version;
		uint32_t size_of_code;
		uint32_t size_of_initialized_data;
		uint32_t size_of_uninitialized_data;
		uint32_t address_of_entry_point;
		uint32_t base_of_code;
		uint32_t base_of_data;
		
		OPTHeader(std::vector<BYTE> bytes_from_file, uint32_t offset);
};

#endif