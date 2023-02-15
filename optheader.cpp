#include "optheader.h"

typedef unsigned char BYTE;

OPTHeader::OPTHeader(std::vector<BYTE> bytes_from_file, uint32_t offset)
{
	base_address = offset;
	magic_number = ((uint16_t)bytes_from_file[base_address+1] << 8) | bytes_from_file[base_address];
}