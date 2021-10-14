#include "readelf.hpp"

#include <string>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <iterator>
#include <iostream>

namespace ELF
{
    static inline
    bool 
    validate_elf_magic(uint8_t (&magic)[4]) 
    {
        return magic[0] == 0x7FU &&
               magic[1] == 0x45U && // E
               magic[2] == 0x4CU && // L
               magic[3] == 0x46U;   // F
    }

    // ------------------------------------------------------------------------------------------------

    static
    details::FileHeader 
    read_file_header(const std::vector<char>& buffer)
    {
        if(buffer.size() < sizeof(details::FileHeader))
            throw std::runtime_error("File header does not have an expected size.");

        // TODO: Fix has offsets.
        details::FileHeader header;
        std::memcpy(&header, buffer.data(), sizeof(details::FileHeader));

        if(!validate_elf_magic(header.magic))
            throw std::runtime_error("File is not an ELF file.");

        return header;
    }

    Reader::Reader(const std::string& filename)
    {
        std::ifstream ifs(filename, std::ios::binary);

        if(ifs.is_open())
        {
            std::vector<char> buffer(std::istream_iterator<char>{ifs},
                                     std::istream_iterator<char>{});

            file_header = read_file_header(buffer);
        }
        else
            throw std::runtime_error("File couldn't be opened.");
    }
    // ------------------------------------------------------------------------------------------------

    std::array<uint8_t, 4> 
    Reader::get_file_header_magic_number() 
        const
    {
        // return std::to_array(file_header.magic);
        return {
            file_header.magic[0], 
            file_header.magic[1], 
            file_header.magic[2], 
            file_header.magic[3]
        };
    }

    uint8_t 
    Reader::get_file_header_32_or_64_bit() 
        const 
    {
        return file_header.bits == 1 ? 32 : 64;
    }

    Endianness 
    Reader::get_file_header_endianness() 
        const 
    {
        return file_header.endian == 1 ? Endianness::Little : Endianness::Big;
    }

    ABIType 
    Reader::get_file_header_abi() 
        const 
    {
        return static_cast<ABIType>(file_header.osabi);
    }

    ObjectFileType 
    Reader::get_file_header_object_file_type() 
        const 
    {
        return static_cast<ObjectFileType>(file_header.type);
    }

    InstructionSetArchitectureType 
    Reader::get_file_header_isa_type() 
        const 
    {
        return static_cast<InstructionSetArchitectureType>(file_header.machine);
    }

    uint64_t 
    Reader::get_file_header_entry_point() 
        const
    {
        return static_cast<uint64_t>(file_header.entry);
    }

    uint64_t 
    Reader::get_file_header_start_of_program_header_table() 
        const
    {
        return static_cast<uint64_t>(file_header.shoff);
    }
}
