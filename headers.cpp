#include "headers.h"


typedef unsigned char BYTE;

void DOSHeader::DOSHeader(std::vector<BYTE> bytes_from_file) 
{
    e_magic = ((uint16_t)bytes_from_file[1] << 8) | bytes_from_file[0];
    e_cblp = ((uint16_t)bytes_from_file[3] << 8) | bytes_from_file[2];
    e_cp = ((uint16_t)bytes_from_file[5] << 8) | bytes_from_file[4];
    e_crlc = ((uint16_t)bytes_from_file[7] << 8) | bytes_from_file[8];
    e_cparhdr = ((uint16_t)bytes_from_file[9] << 8) | bytes_from_file[10];
    e_minalloc = ((uint16_t)bytes_from_file[11] << 8) | bytes_from_file[12];
    e_maxalloc = ((uint16_t)bytes_from_file[13] << 8) | bytes_from_file[14];
    e_ss = ((uint16_t)bytes_from_file[15] << 8) | bytes_from_file[16];
    e_sp = ((uint16_t)bytes_from_file[17] << 8) | bytes_from_file[18];
    e_csum = ((uint16_t)bytes_from_file[19] << 8) | bytes_from_file[20];
     e_ip = ((uint16_t)bytes_from_file[21] << 8) | bytes_from_file[22];
    e_cs = ((uint16_t)bytes_from_file[23] << 8) | bytes_from_file[24];
    e_lfarlc = ((uint16_t)bytes_from_file[25] << 8) | bytes_from_file[26];
    e_ovno = ((uint16_t)bytes_from_file[27] << 8) | bytes_from_file[28];

    for (int i = 0; i < 4; i++)
    {
        e_res[i] = ((uint16_t)bytes_from_file[29+2*i] << 8) | bytes_from_file[28+2*i];
    }

    e_oemid = ((uint16_t)bytes_from_file[37] << 8) | bytes_from_file[36];
    e_oeminfo = ((uint16_t)bytes_from_file[39] << 8) | bytes_from_file[38];

    for (int i = 0; i < 10; i++)
    {
        e_res2[i] = ((uint16_t)bytes_from_file[41+2*i] << 8) | bytes_from_file[40+2*i];
    }
    
    e_lfanew = 0;
    e_lfanew += bytes_from_file[63] << 24;
    e_lfanew += bytes_from_file[62] << 16;
    e_lfanew += bytes_from_file[61] << 8;
    e_lfanew += bytes_from_file[60];
}
