#include <windows.h>
#include <stdio.h>

void MapFile(LPCSTR lpSourceFile)
{
    HANDLE hFile;
    HANDLE hFileMapping;
    LPVOID lpFileBase;
    PIMAGE_DOS_HEADER dosHeader;
    PIMAGE_NT_HEADERS ntFileHeader;
    PIMAGE_FILE_HEADER fileHeader;

    hFile = CreateFileA(lpSourceFile, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Could not open file with CreateFile()\n");
        return;
    }

    hFileMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hFileMapping == NULL)
    {
        CloseHandle(hFile);
        printf("Could not create file mapping with CreateFileMappingA()\n");
        return;
    }

    lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (lpFileBase == NULL)
    {
        printf("Could not map view of file with MapViewOfFile()\n");
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        return;
    }

    dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
    ntFileHeader = (PIMAGE_NT_HEADERS)lpFileBase;
    

    CloseHandle(hFileMapping);
    CloseHandle(hFile);

    return;
}

int main(const int argc, char* argv[])
{
    LPCSTR lpSourceFile;

    if (argc == 2)
    {
        lpSourceFile = argv[1];
    }
    else
    {
        printf("[USAGE] .\\MemMapTest <source_file> \n");
        return -1;
    }

    MapFile(lpSourceFile);

    return 0;
}
