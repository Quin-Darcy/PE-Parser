#ifndef COFFHEADER_H
#define COFFHEADER_H
#include <iostream>
#include <vector>
#include <fstream>

typedef unsigned char BYTE;

class COFFHeader
{
	public:
		long pe_offset;
		uint32_t pe_signature;
		uint16_t machine;
		uint16_t number_of_sections;
		uint32_t time_date_stamp;
		uint32_t pointer_to_symbol_table;
		uint32_t number_of_symbols;
		uint16_t size_of_optional_header;
		uint16_t characteristics;

		COFFHeader(std::vector<BYTE> bytes_from_file, long pe_sig);
};

#endif