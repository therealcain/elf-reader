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
#include <type_traits>
#include <climits>
#include <iomanip>
// #include <elf.h>

// ------------------------------------------------------------------------------------------------

static constexpr size_t SysBits = (CHAR_BIT * sizeof(void*));

template<typename T32, typename T64>
using BitsBasedType = 
    typename std::conditional<SysBits == 32, T32, T64>::type;

// ------------------------------------------------------------------------------------------------

namespace ELF
{
    namespace details {
        struct FileHeader
        {
            uint8_t magic[4];          
            uint8_t bits; // class
            uint8_t endian;
            uint8_t version1;
            uint8_t osabi;
            uint8_t abiver;
            uint8_t unused[7];
            uint16_t type;
            uint16_t machine;
            uint32_t version2;
            BitsBasedType<uint32_t, uint64_t> entry;
            BitsBasedType<uint32_t, uint64_t> phoff;
            BitsBasedType<uint32_t, uint64_t> shoff;
            uint32_t flags;
            uint16_t ehsize;
            uint16_t phentsize;
            uint16_t phnum;
            uint16_t shentsize;
            uint16_t shnum;
            uint16_t shstrndx;
        };
    }

    // ------------------------------------------------------------------------------------------------

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
    void
    read_file_header(std::unique_ptr<details::FileHeader>& header, const std::vector<uint8_t>& buffer)
    {
        if(buffer.size() < sizeof(details::FileHeader))
            throw std::runtime_error("File header does not have an expected size.");

        std::memcpy(header.get(), buffer.data(), sizeof(details::FileHeader));

        if(!validate_elf_magic(header->magic))
            throw std::runtime_error("File is not an ELF file.");
    }

    Reader::Reader(const std::string& filename)
        : file_header(std::make_unique<details::FileHeader>())
    {
        std::ifstream ifs(filename, std::ios::binary | std::ios::in);

        if(ifs.is_open())
        {
            std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(ifs),
                                        std::istreambuf_iterator<char>{});

            read_file_header(file_header, buffer);
        }
        else
            throw std::runtime_error("File couldn't be opened.");
    }

    Reader::~Reader() = default;










    // ------------------------------------------------------------------------------------------------

    std::array<uint8_t, 4> 
    Reader::get_file_header_magic_number() 
        const
    {
        // return std::to_array(file_header.magic);
        return {
            file_header->magic[0], 
            file_header->magic[1], 
            file_header->magic[2], 
            file_header->magic[3]
        };
    }

    uint8_t 
    Reader::get_file_header_32_or_64_bit() 
        const 
    {
        return file_header->bits == 1 ? 32 : 64;
    }

    Endianness 
    Reader::get_file_header_endianness() 
        const 
    {
        return file_header->endian == 1 ? Endianness::Little : Endianness::Big;
    }

    ABIType 
    Reader::get_file_header_abi() 
        const 
    {
        return static_cast<ABIType>(file_header->osabi);
    }

    ObjectFileType 
    Reader::get_file_header_object_file_type() 
        const 
    {
        return static_cast<ObjectFileType>(file_header->type);
    }

    InstructionSetArchitectureType 
    Reader::get_file_header_isa_type() 
        const 
    {
        return static_cast<InstructionSetArchitectureType>(file_header->machine);
    }

    uint64_t 
    Reader::get_file_header_entry_point() 
        const
    {
        return static_cast<uint64_t>(file_header->entry);
    }

    uint64_t 
    Reader::get_file_header_start_of_program_header_table() 
        const
    {
        return static_cast<uint64_t>(file_header->phoff);
    }

    uint64_t 
    Reader::get_file_header_start_of_section_header_table() 
        const
    {
        return static_cast<uint64_t>(file_header->shoff);
    }

    uint32_t 
    Reader::get_file_header_flags() 
        const
    {
        return file_header->flags;
    }

    uint16_t
    Reader::get_file_header_size() 
        const
    {
        return file_header->ehsize;
    }

    uint16_t
    Reader::get_file_header_program_header_size() 
        const
    {
        return file_header->phentsize;
    }

    uint16_t 
    Reader::get_file_header_number_of_program_entries() 
        const
    {
        return file_header->phnum;
    }

    uint16_t 
    Reader::get_file_header_section_header_size() 
        const
    {
        return file_header->shentsize;
    }

    uint16_t 
    Reader::get_file_header_number_of_section_entries() 
        const
    {
        return file_header->shnum;
    }

    uint16_t 
    Reader::get_file_header_index_of_section_header() 
        const
    {
        return file_header->shstrndx;
    }
}
