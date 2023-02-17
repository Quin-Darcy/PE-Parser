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
		uint32_t image_base;
		uint64_t image_base_pe_plus;
		uint32_t section_allignment;
		uint32_t file_allignment;
		uint16_t major_operating_system_version;
		uint16_t minor_operating_system_version;
		uint16_t major_image_version;
		uint16_t minor_image_version;
		uint16_t major_subsystem_version;
		uint16_t minor_subsystem_version;
		uint32_t win32_version_value;
		uint32_t size_of_image;
		uint32_t size_of_headers;
		uint32_t checksum;
		uint16_t subsystem;
		uint16_t sll_characteristics;
		uint32_t size_of_stack_reserve;
		uint64_t size_of_stack_reserve_pe_plus;
		uint32_t size_of_stack_commit;
		uint64_t size_of_stack_commit_pe_plus;
		uint32_t size_of_heap_reserve;
		uint64_t size_of_heap_reserve_pe_plus;
		uint32_t size_of_heap_commit;
		uint64_t size_of_heap_commit_pe_plus;
		uint32_t loader_flags;
		uint32_t number_of_rva_and_sizes;
		
		OPTHeader(std::vector<BYTE> bytes_from_file, uint32_t offset);
};

#endif