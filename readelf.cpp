#include "readelf.hpp"

#include <string>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <type_traits>
#include <climits>
// #include <elf.h>

// ------------------------------------------------------------------------------------------------

static constexpr size_t SysBits = (CHAR_BIT * sizeof(void*));

template<typename T32, typename T64>
using BitsBasedType = 
    typename std::conditional<SysBits == 32, T32, T64>::type;

class EmptyClass{};
using ZeroAllocType = EmptyClass[0]; // sizeof(ZeroAllocType) = 0.

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

        struct ProgramHeader
        {
            uint32_t type;
            BitsBasedType<ZeroAllocType, uint32_t> flags64; // flags for 64bit
            BitsBasedType<uint32_t, uint64_t> offset;
            BitsBasedType<uint32_t, uint64_t> vaddr;
            BitsBasedType<uint32_t, uint64_t> paddr;
            BitsBasedType<uint32_t, uint64_t> filesz;
            BitsBasedType<uint32_t, uint64_t> memsz;
            BitsBasedType<uint32_t, ZeroAllocType> flags32; // flags for 32bit
            BitsBasedType<uint32_t, uint64_t> align;
        };

        struct SectionHeader
        {
            uint32_t name;
            uint32_t type;
            BitsBasedType<uint32_t, uint64_t> flags;
            BitsBasedType<uint32_t, uint64_t> addr;
            BitsBasedType<uint32_t, uint64_t> offset;
            BitsBasedType<uint32_t, uint64_t> size;
            uint32_t link;
            uint32_t info;
            BitsBasedType<uint32_t, uint64_t> addralign;
            BitsBasedType<uint32_t, uint64_t> entsize;
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

    void 
    Reader::read_file_header(const std::vector<uint8_t>& buffer)
    {
        if(buffer.size() < sizeof(details::FileHeader))
            throw std::runtime_error("File header does not have an expected size.");

        std::memcpy(file_header.get(), buffer.data(), sizeof(details::FileHeader));

        if(!validate_elf_magic(file_header->magic))
            throw std::runtime_error("File is not an ELF file.");
    }

    void
    Reader::read_program_headers(const std::vector<uint8_t>& buffer)
    {
        auto phnum = file_header->phnum;
        const uint8_t* p_header = buffer.data() + file_header->ehsize;

        for (size_t i = 0; i < phnum; i++)
        {
            PtrProgramHeader ph = std::make_unique<details::ProgramHeader>();
            std::memcpy(ph.get(), p_header, sizeof(details::ProgramHeader));

            program_headers.push_back(std::move(ph));

            p_header += sizeof(details::ProgramHeader);
        }
    }

    Reader::Reader(const std::string& filename)
        : file_header(std::make_unique<details::FileHeader>())
    {
        std::ifstream ifs(filename, std::ios::binary | std::ios::in);

        if(ifs.is_open())
        {
            std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(ifs),
                                        std::istreambuf_iterator<char>{});

            read_file_header(buffer);
            read_program_headers(buffer);
        }
        else
            throw std::runtime_error("File couldn't be opened.");
    }

    Reader::~Reader() = default;

    // ------------------------------------------------------------------------------------------------

    const FileHeaderInfo 
    Reader::get_file_header() 
        const
    {
        FileHeaderInfo info;
        
        info.magic[0] = file_header->magic[0];
        info.magic[1] = file_header->magic[1];
        info.magic[2] = file_header->magic[2];
        info.magic[3] = file_header->magic[3];

        info.bits = file_header->bits == 1 ? 32 : 64;

        info.endian = file_header->endian == 1 ? Endianness::Little : Endianness::Big;

        info.abi = static_cast<ABIType>(file_header->osabi);

        info.object_file_type = static_cast<ObjectFileType>(file_header->type);

        info.instruction_set_architecture_type = static_cast<InstructionSetArchitectureType>(file_header->machine);

        info.entry_point = static_cast<uint64_t>(file_header->entry);

        info.start_of_program_header_table = static_cast<uint64_t>(file_header->phoff);
        info.start_of_section_header_table = static_cast<uint64_t>(file_header->shoff);

        info.flags = file_header->flags;

        info.size = file_header->ehsize;
        info.program_header_size = file_header->phentsize;
        info.section_header_size = file_header->shentsize;

        info.number_of_program_entries = file_header->phnum;
        info.number_of_section_entries = file_header->shnum;

        info.index_of_section_header = file_header->shstrndx;

        return info;
    }

    const std::vector<ProgramHeaderInfo>
    Reader::get_program_headers() 
        const
    {
        std::vector<ProgramHeaderInfo> headers;

        for(auto& p_header : program_headers)
        {
            ProgramHeaderInfo info;
            info.type             = static_cast<SegmentType>(p_header->type);
            info.offset           = p_header->offset;
            info.virtual_address  = p_header->vaddr;
            info.physical_address = p_header->paddr;
            info.file_size        = p_header->filesz;
            info.memory_size      = p_header->memsz;
            info.alignment        = p_header->align;

            if(sizeof(p_header->flags32) != 0)
                info.flags = *reinterpret_cast<uint32_t*>(&p_header->flags32);
            else
                info.flags = *reinterpret_cast<uint32_t*>(&p_header->flags64);

            headers.push_back(info);
        }

        return headers;
    }
}
