#include "readelf.hpp"

#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <iostream>
// #include <elf.h>

// ------------------------------------------------------------------------------------------------

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

    void 
    Reader::read_file_header()
    {
        if(data.size() < sizeof(FileHeader))
            throw std::runtime_error("File header does not have an expected size.");

        std::memcpy(&file_header, data.data(), sizeof(FileHeader));

        if(!validate_elf_magic(file_header.magic))
            throw std::runtime_error("File is not an ELF file.");
    }

    void
    Reader::read_program_headers()
    {
        auto phnum     = file_header.phnum;
        auto phoff     = file_header.phoff;
        auto phentsize = file_header.phentsize;

        if(phoff + (phnum * sizeof(ProgramHeader)) > data.size())
            throw std::runtime_error("Program headers does not have an expected size.");

        const uint8_t* p_header = data.data() + phoff;

        for (size_t i = 0; i < phnum; i++)
        {
            ProgramHeader ph;
            std::memcpy(&ph, p_header, sizeof(ProgramHeader));

            program_headers.push_back(ph);

            p_header += phentsize;
        }
    }

    void 
    Reader::read_section_headers()
    {
        auto shnum     = file_header.shnum;
        auto shoff     = file_header.shoff;
        auto shentsize = file_header.shentsize;

        const uint8_t* p_header = data.data() + shoff;

        if(shoff + (shnum * sizeof(SectionHeader)) > data.size())
            throw std::runtime_error("Section headers does not have an expected size.");

        for (size_t i = 0; i < shnum; i++)
        {
            SectionHeader sh;
            std::memcpy(&sh, p_header, sizeof(SectionHeader));

            section_headers.push_back(sh);

            p_header += shentsize;
        }
    }

    // ------------------------------------------------------------------------------------------------

    Reader::Reader(const std::string& filename)
    {
        std::ifstream ifs(filename, std::ios::binary | std::ios::in);

        if(ifs.is_open())
        {
            std::copy(std::istreambuf_iterator<char>(ifs), 
                      std::istreambuf_iterator<char>(), 
                      std::back_inserter(data));

            ifs.close();

            read_file_header();
            read_program_headers();
            read_section_headers();
        }
        else
            throw std::runtime_error("File couldn't be opened.");
    }

    Reader::~Reader() = default;
}
