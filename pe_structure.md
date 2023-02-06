## PE File Structure

---

### PE File Header

* #### MS-DOS Header
  
  The first 64 bytes of the PE file is occupied by the DOS header. The first two bytes of this header will always be `0x4D5A`, which in ASCII is `MZ`. This is referred to as the signature. This magic number is one of the mutliple ways of identifying MS-DOS compatible files.
  
  ![msdosheader](resources/msdosheader.png)
  
  These 64 bytes are broken down into 19 members which define and outline the environment which the DOS EXE contained in the MS-DOS stub is run. One very note worthy member is located (and always located) at offset `0x3C`. The value at this address is equal to the offset of the PE signature which is a 4-byte signature that identifies the file as a PE format image file. 

* #### MS-DOS Stub
  
  The MS-DOS stub is a valid application that runs under MS-DOS. It is placed at the front of the EXE image and immediately after the DOS header. The linker places a default stub here, which prints out the message "This program cannot be run in DOS mode" when the image is run in MS-DOS. 
  
  ![msdosstub](resources/msdosstub.png)

* #### PE Signature
  
  After the MS-DOS stub, at the file offset specified at offset `0x3C` , is a 4-byte signature that identifies the file as a PE format image file. The complete signature is `0x50450000` which in ASCII is `PE\0\0`.

* #### COFF File Header
  
  This header contains the following pieces of information as described in this table
  
  ![b](resources/coff-table.png)
  
  Based on the table above we have the following values for the example EXE
  
  * **Machine**: The follwoing two bytes 
    
    ![c](resources/machine.png)
    
    `0x4C01`, written in big endian as`0x014C`, would indicate the target machine would be Intel 386 or later processors and compatible processors.
  
  * **NumberOfSections**: The following two bytes
    
    ![d](resources/numberofsections.png)
    
    `0x0D00`, written in big endian as`0x000D`, indicate there are 13 sections in the section table.
  
  * **TimeDateStamp**: The following 4 bytes
    
    ![e](resources/timedatestamp.png)
    
    `0x61B7DC63`, written in big endian as`0x63DCB761`, indicates that at the time the EXE was created it had been 1,675,409,249 many seconds since 00:00 January 1, 1970. This comes out to be about 53.09 years. Thus, the EXE was created in Feb of 2023.
  
  * **PointerToSymbolTable**: The following 4 bytes
    
    ![f](resources/pointertosymboltable.png)
    
    `0x00780000`, written in big endian as`0x00007800`, indicates that the symbol table starts at offset `0x7800`.
  
  * **NumberOfSymbols**: The following 4 bytes
    
    ![numofsymbols](resources/numberofsymbols.png)
    
    `0xFB010000`, written in big endian as`0x000001FB`, indicates there are `0x1FB` = 507 entries in the symbol talbe.
  
  * **SizeOfOptionalHeader**: The following 2 bytes
    
    ![sizeofoptionalheader](resources/sizeofoptionalheader.png)
    
    `0xE000`, written in big endian as`0x00E0`, indicates that the optional header is 224 bytes.
  
  * **Characteristics**: The last 2 bytes of the COFF header
    
    ![characteristics](resources/characteristics.png)
    
    `0x0701`, written in big endian as `0x0107`, is the sum of the following bit flags
    
    * `0x0100`- IMAGE_FILE_32BIT_MACHINE: Machine is based on a 32-bit word architecture
    
    * `0x0004`- IMAGE_FILE_LINE_NUMS_STRIPPED: COFF line numbers have been removed.
    
    * `0x0002` - IMAGE_FILE_EXECUTABLE_IMAGE: Image only. This indicates that the image file is valid and can be run. If this flag is not set, it indicates a linker error.
    
    * `0x0001` - IMAGE_FILE_RELOCS_STRIPPED: Image only. This indicates that the file does not contain base relocations and must therefore be loaded at its preferred base address. If the base address is not available, the loader reports an error.  
