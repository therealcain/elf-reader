#include "readelf.hpp"
#include <iostream>

int main()
{
    ELF::Reader reader("test");

    std::cout << std::hex;

    // ELF magic header.
    auto magic = reader.get_file_header_magic_number();
    std::cout << "Magic: " << 
        static_cast<int>(magic[0]) << " " << 
        static_cast<int>(magic[1]) << " " << 
        static_cast<int>(magic[2]) << " " << 
        static_cast<int>(magic[3]) << std::endl;


    std::cout << std::dec;

    // 32 or 64 bit format
    int8_t format_bits = reader.get_file_header_32_or_64_bit();
    std::cout << "Class: " << (format_bits == 32 ? "ELF32" : "ELF64") << std::endl;

    // Little or Big endian
    auto endian = reader.get_file_header_endianness();
    std::cout << "Endianness: " << (endian == ELF::Endianness::Little ? "Little" : "Big") << std::endl;

    // OS ABI
    auto abi = reader.get_file_header_abi();
    std::cout << "ABI: ";

    switch(abi) {
    case ELF::ABIType::AIX:
        std::cout << "AIX";
        break;
    
    case ELF::ABIType::AROS:
        std::cout << "AROS";
        break;
    
    case ELF::ABIType::CloudABI:
        std::cout << "CloudABI";
        break;

    case ELF::ABIType::FenixOS:
        std::cout << "FenixOS";
        break;

    case ELF::ABIType::FreeBSD:
        std::cout << "FreeBSD";
        break;

    case ELF::ABIType::GNU_Hurd:
        std::cout << "GNU Hurd";
        break;

    case ELF::ABIType::HP_UX:
        std::cout << "HP UX";
        break;

    case ELF::ABIType::IRIX:
        std::cout << "IRIX";
        break;

    case ELF::ABIType::Linux:
        std::cout << "Linux";
        break;

    case ELF::ABIType::NetBSD:
        std::cout << "NetBSD";
        break;

    case ELF::ABIType::NonStop_Kernel:
        std::cout << "NonStop Kernel";
        break;

    case ELF::ABIType::Novell_Modesto:
        std::cout << "Novell Modesto";
        break;

    case ELF::ABIType::OpenBSD:
        std::cout << "OpenBSD";
        break;

    case ELF::ABIType::OpenVMS:
        std::cout << "OpenVMS";
        break;

    case ELF::ABIType::Solaris:
        std::cout << "Solaris";
        break;

    case ELF::ABIType::Stratus_Technologies_OpenVOS:
        std::cout << "Stratus Technologies OpenVOS";
        break;
    
    case ELF::ABIType::SystemV:
        std::cout << "SystemV";
        break;

    case ELF::ABIType::Tru64:
        std::cout << "Tru64";
        break;
    }
    
    std::cout << std::endl;

    // Object File Type
    auto obj_type = reader.get_file_header_object_file_type();
    std::cout << "Object File Type: ";

    switch (obj_type)
    {
        case ELF::ObjectFileType::CORE:
            std::cout << "CORE";
            break;

        case ELF::ObjectFileType::DYN:
            std::cout << "DYN";
            break;

        case ELF::ObjectFileType::EXEC:
            std::cout << "EXEC";
            break;

        case ELF::ObjectFileType::HIOS:
            std::cout << "HIOS";
            break;

        case ELF::ObjectFileType::HIPROC:
            std::cout << "HIPROC";
            break;

        case ELF::ObjectFileType::LOOS:
            std::cout << "LOOS";
            break;

        case ELF::ObjectFileType::LOPROC:
            std::cout << "LOPROC";
            break;

        case ELF::ObjectFileType::NONE:
            std::cout << "NONE";
            break;
        
        case ELF::ObjectFileType::REL:
            std::cout << "REL";
            break;
    }
    std::cout << std::endl;

    // ISA
    auto isa = reader.get_file_header_isa_type();
    std::cout << "Instruction Set: ";
    switch(isa)
    {
        // TODO: Implement their print.
    }
    std::cout << std::endl;

    // Entry Point
    uint64_t entry = reader.get_file_header_entry_point();
    std::cout << "Entry Point: " << std::hex << entry << std::dec << std::endl;

    // Start of program header
    uint64_t shoff = reader.get_file_header_start_of_program_header_table();
    std::cout << "Start of Program Header: " << std::hex << shoff << std::dec << std::endl;


}
