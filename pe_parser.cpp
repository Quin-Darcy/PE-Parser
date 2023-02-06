#include <iostream>
#include <vector>
#include <fstream>

typedef unsigned char BYTE;

class DOSHeader
{
    public:
        uint16_t e_magic;                     // Magic number
        uint16_t e_cblp;                      // Bytes on last page of file
        uint16_t e_cp;                        // Pages in file
        uint16_t e_crlc;                      // Relocations
        uint16_t e_cparhdr;                   // Size of header in paragraphs
        uint16_t e_minalloc;                  // Minimum extra paragraphs needed
        uint16_t e_maxalloc;                  // Maximum extra paragraphs needed
        uint16_t e_ss;                        // Initial (relative) SS value
        uint16_t e_sp;                        // Initial SP value
        uint16_t e_csum;                      // Checksum
        uint16_t e_ip;                        // Initial IP value
        uint16_t e_cs;                        // Initial (relative) CS value
        uint16_t e_lfarlc;                    // File address of relocation table
        uint16_t e_ovno;                      // Overlay number
        uint16_t e_res[4];                    // Reserved words
        uint16_t e_oemid;                     // OEM identifier (for e_oeminfo)
        uint16_t e_oeminfo;                   // OEM information; e_oemid specific
        uint16_t e_res2[10];                  // Reserved words
        long e_lfanew;                        // File address of new exe header
        
        DOSHeader(std::vector<BYTE> bytes_from_file) 
        {
            this->e_magic = ((uint16_t)bytes_from_file[1] << 8) | bytes_from_file[0];
            this->e_cblp = ((uint16_t)bytes_from_file[3] << 8) | bytes_from_file[2];
            this->e_cp = ((uint16_t)bytes_from_file[5] << 8) | bytes_from_file[4];
            this->e_crlc = ((uint16_t)bytes_from_file[7] << 8) | bytes_from_file[8];
            this->e_cparhdr = ((uint16_t)bytes_from_file[9] << 8) | bytes_from_file[10];
            this->e_minalloc = ((uint16_t)bytes_from_file[11] << 8) | bytes_from_file[12];
            this->e_maxalloc = ((uint16_t)bytes_from_file[13] << 8) | bytes_from_file[14];
            this->e_ss = ((uint16_t)bytes_from_file[15] << 8) | bytes_from_file[16];
            this->e_sp = ((uint16_t)bytes_from_file[17] << 8) | bytes_from_file[18];
            this->e_csum = ((uint16_t)bytes_from_file[19] << 8) | bytes_from_file[20];
            this-> e_ip = ((uint16_t)bytes_from_file[21] << 8) | bytes_from_file[22];
            this->e_cs = ((uint16_t)bytes_from_file[23] << 8) | bytes_from_file[24];
            this->e_lfarlc = ((uint16_t)bytes_from_file[25] << 8) | bytes_from_file[26];
            this->e_ovno = ((uint16_t)bytes_from_file[27] << 8) | bytes_from_file[28];

            for (int i = 0; i < 4; i++)
            {
                this->e_res[i] = ((uint16_t)bytes_from_file[29+2*i] << 8) | bytes_from_file[28+2*i];
            }

            this->e_oemid = ((uint16_t)bytes_from_file[37] << 8) | bytes_from_file[36];
            this->e_oeminfo = ((uint16_t)bytes_from_file[39] << 8) | bytes_from_file[38];

            for (int i = 0; i < 10; i++)
            {
                this->e_res2[i] = ((uint16_t)bytes_from_file[41+2*i] << 8) | bytes_from_file[40+2*i];
            }
            
            this->e_lfanew = 0;
            this->e_lfanew += bytes_from_file[63] << 24;
            this->e_lfanew += bytes_from_file[62] << 16;
            this->e_lfanew += bytes_from_file[61] << 8;
            this->e_lfanew += bytes_from_file[60];
        }

};

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

    printf("%02X\n", dos_header.e_lfanew); 

    return 0;
}
