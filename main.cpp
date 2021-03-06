#include "readelf.hpp"
#include <iostream>

int main()
{
    ELF::Reader reader("test");
    auto header = reader.get_file_header();

    std::cout << std::hex;

    // ELF magic header.
    auto magic = header.magic;
    std::cout << "Magic: " << " 0x" <<
        static_cast<int>(magic[0]) << " 0x" << 
        static_cast<int>(magic[1]) << " 0x" << 
        static_cast<int>(magic[2]) << " 0x" << 
        static_cast<int>(magic[3]) << std::endl;


    // 32 or 64 bit format
    int8_t format_bits = header.bits;
    std::cout << "Class: " << (format_bits == 32 ? "ELF32" : "ELF64") << std::endl;

    // Little or Big endian
    auto endian = header.endian;
    std::cout << "Endianness: " << (endian == ELF::Endianness::Little ? "Little" : "Big") << std::endl;

    // OS ABI
    auto abi = header.osabi;
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
    auto obj_type = header.type;
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
    auto isa = header.machine;
    std::cout << "Instruction Set: ";
    switch(isa)
    {
    case ELF::InstructionSetArchitectureType::Advanced_Logic_TinyJ_Embedded_Processor_Family:
        std::cout << "Advanced Logic TinyJ Embedded Processor Family";
        break;
    
    case ELF::InstructionSetArchitectureType::AMD_X86_64:
        std::cout << "AMD X86_64";
        break;

    case ELF::InstructionSetArchitectureType::Argonaut_RISC_Core:
        std::cout << "Argonaut RISC Core";
        break;

    case ELF::InstructionSetArchitectureType::ARM_64bit:
    case ELF::InstructionSetArchitectureType::ARM:
        std::cout << "ARM";
        break;

    case ELF::InstructionSetArchitectureType::AT_And_T_WE_32100:
        std::cout << "AT&T WE 32100";
        break;

    case ELF::InstructionSetArchitectureType::Berkeley_Packet_Filter:
        std::cout << "Berkeley Packet Filter";
        break;

    case ELF::InstructionSetArchitectureType::Denso_NDR1_Microprocessor:
        std::cout << "Denso NDR1 Microprocessor";
        break;

    case ELF::InstructionSetArchitectureType::Digital_Alpha:
        std::cout << "Digital Alpha";
        break;

    case ELF::InstructionSetArchitectureType::Fujitsu_FR20:
        std::cout << "Fujitsu FR20";
        break;

    case ELF::InstructionSetArchitectureType::Fujitsu_MMA_Multimedia_Accelerator:
        std::cout << "Fujitsu MMA Multimedia Accelerator";
        break;

    case ELF::InstructionSetArchitectureType::Hewlett_Packard_PA_RISC:
        std::cout << "Hewlett Packard PA RISC";
        break;

    case ELF::InstructionSetArchitectureType::Hitachi_H8_300:
        std::cout << "Hitachi H8 300";
        break;

    case ELF::InstructionSetArchitectureType::Hitachi_H8_300H:
        std::cout << "Hitachi H8 300H";
        break;

    case ELF::InstructionSetArchitectureType::Hitachi_H8_500:
        std::cout << "Hitachi H8 500";
        break;

    case ELF::InstructionSetArchitectureType::Hitachi_H8S:
        std::cout << "Hitachi H8S";
        break;

    case ELF::InstructionSetArchitectureType::IA_64:
        std::cout << "IA 64";
        break;
    
    case ELF::InstructionSetArchitectureType::IBM_SPU_SPC:
        std::cout << "IBM SPU/SPC";
        break;

    case ELF::InstructionSetArchitectureType::IBM_System:
        std::cout << "IBM System";
        break;

    case ELF::InstructionSetArchitectureType::Intel_80860:
        std::cout << "Intel 80860";
        break;

    case ELF::InstructionSetArchitectureType::Intel_80960:
        std::cout << "Intel 80960";
        break;

    case ELF::InstructionSetArchitectureType::Intel_MCU:
        std::cout << "Intel MCU";
        break;

    case ELF::InstructionSetArchitectureType::M68k:
        std::cout << "M68k";
        break;

    case ELF::InstructionSetArchitectureType::M88k:
        std::cout << "M88k";
        break;

    case ELF::InstructionSetArchitectureType::MCST_Elbrus_e2k:
        std::cout << "MCST Elbrus e2k";
        break;

    case ELF::InstructionSetArchitectureType::MIPS:
        std::cout << "MIPS";
        break;

    case ELF::InstructionSetArchitectureType::MIPS_RS3000_Little_Endian:
        std::cout << "MIPS RS3000";
        break;

    case ELF::InstructionSetArchitectureType::Motorola_ColdFire:
        std::cout << "Motorola ColdFire";
        break;

    case ELF::InstructionSetArchitectureType::Motorola_M68HC12:
        std::cout << "Motorola M68HC12";
        break;

    case ELF::InstructionSetArchitectureType::Motorola_RCE:
        std::cout << "Motorola RCE";
        break;

    case ELF::InstructionSetArchitectureType::Motorola_StarCore_Processor:
        std::cout << "Motorola StarCore Processor";
        break;

    case ELF::InstructionSetArchitectureType::NEC_V800:
        std::cout << "NEC V800";
        break;

    case ELF::InstructionSetArchitectureType::No_Specific:
        std::cout << "No Specific";
        break;

    case ELF::InstructionSetArchitectureType::PowerPC_64bit:
    case ELF::InstructionSetArchitectureType::PowerPC:
        std::cout << "PowerPC";
        break;

    case ELF::InstructionSetArchitectureType::RISC_V:
        std::cout << "RISC V";
        break;

    case ELF::InstructionSetArchitectureType::S390:
        std::cout << "S390";
        break;

    case ELF::InstructionSetArchitectureType::Siemens_PCP:
        std::cout << "Siemens PCP";
        break;

    case ELF::InstructionSetArchitectureType::Siemens_TriCore_Embedded_Processor:
        std::cout << "Siemens TriCore Embedded Processor";
        break;

    case ELF::InstructionSetArchitectureType::Sony_nCPU_Embedded_RISC_Processor:
        std::cout << "Sony nCPU Embedded RISC Processor";
        break;

    case ELF::InstructionSetArchitectureType::SPARC_Ver9:
    case ELF::InstructionSetArchitectureType::SPARC:
        std::cout << "SPARC";
        break;

    case ELF::InstructionSetArchitectureType::Stanford_MIPS_X:
        std::cout << "Stanford MIPS X";
        break;

    case ELF::InstructionSetArchitectureType::STMicroelectronics_ST100_Processor:
        std::cout << "STMicroelectronics ST100 Processor";
        break;

    case ELF::InstructionSetArchitectureType::SuperH:
        std::cout << "SuperH";
        break;

    case ELF::InstructionSetArchitectureType::TMS320C6000_Family:
        std::cout << "TMS320C6000 Family";
        break;

    case ELF::InstructionSetArchitectureType::Toyota_ME16_Processor:
        std::cout << "Toyota ME16 Processor";
        break;

    case ELF::InstructionSetArchitectureType::TRW_RH32:
        std::cout << "TRW RH32";
        break;

    case ELF::InstructionSetArchitectureType::WDC_65C816:
        std::cout << "WDC 65C816";
        break;

    case ELF::InstructionSetArchitectureType::X86:
        std::cout << "X86";
        break;
    }
    std::cout << std::endl;

    // Entry Point
    uint64_t entry = header.entry;
    std::cout << "Entry Point: 0x" << entry << std::endl;

    // Start of program header
    uint64_t phoff = header.phoff;
    std::cout << "Start of Program Header: " << std::dec << phoff << std::endl;

    // Start of section header
    uint64_t shoff = header.shoff;
    std::cout << "Start of Section Header: " << std::dec << shoff << std::endl;

    // Flags
    uint32_t flags = header.flags;
    std::cout << "Flags: 0x" << std::hex << flags << std::endl;

    // Header Size
    uint16_t ehsize = header.ehsize;
    std::cout << "Header Size: " << std::dec << ehsize << std::endl;

    // Program Header Size
    uint16_t phentsize = header.phentsize;
    std::cout << "Program Header Table Entry Size: " << phentsize << std::endl;

    // Number of program entries
    uint16_t phnum = header.phnum;
    std::cout << "Number of Program Entries: " << phnum << std::endl;

    // Section header table entry size
    uint16_t shentsize = header.shentsize;
    std::cout << "Section Header Table Entry Size: " << shentsize << std::endl;

    // Number of section entries
    uint16_t shnum = header.shnum;
    std::cout << "Number of Section Entries: " << shnum << std::endl;

    // Index of the section header table entry
    uint16_t shstrndx = header.shstrndx;
    std::cout << "Index of the Section Header Table Entry: " << shstrndx << std::endl;

    auto program_headers = reader.get_program_headers();
    for (size_t i = 0; i < program_headers.size(); i++)
    {
        auto& header = program_headers[i];

        std::cout << std::endl;

        std::cout << "Program Header Number: " << std::dec << i << std::endl;
        
        std::cout << "Type: ";
        switch(header.type)
        {
        case ELF::SegmentType::LOAD:
            std::cout << "LOAD";
            break;

        case ELF::SegmentType::DYNAMIC:
            std::cout << "DYNAMIC";
            break;

        case ELF::SegmentType::INTERP:
            std::cout << "INTERP";
            break;

        case ELF::SegmentType::SHLIB:
            std::cout << "SHLIB";
            break;

        case ELF::SegmentType::NOTE:
            std::cout << "NOTE";
            break;

        case ELF::SegmentType::PHDR:
            std::cout << "PHDR";
            break;

        case ELF::SegmentType::TLS:
            std::cout << "TLS";
            break;

        case ELF::SegmentType::LOOS:
            std::cout << "LOOS";
            break;

        case ELF::SegmentType::HIOS:
            std::cout << "HIOS";
            break;

        case ELF::SegmentType::LOPROC:
            std::cout << "LOPROC";
            break;

        case ELF::SegmentType::HIPROC:
            std::cout << "HIPROC";
            break;

        case ELF::SegmentType::NONE:
        default:
            std::cout << "NULL";
            break;
        }
        std::cout << std::endl;

        std::cout << std::hex;
        std::cout << "Offset: 0x" << header.offset << std::endl;
        std::cout << "Virtual Address: 0x" << header.vaddr << std::endl;
        std::cout << "Physical Address: 0x" << header.paddr << std::endl;
        std::cout << "File Size: 0x" << header.filesz << std::endl;
        std::cout << "Memory Size: 0x" << header.memsz << std::endl;
        std::cout << "Alignment: 0x" << header.align << std::endl;
    }

    auto section_headers = reader.get_section_headers();
    for (size_t i = 0; i < section_headers.size(); i++)
    {
        auto& header = section_headers[i];

        std::cout << std::endl;

        std::cout << "Section Header Number: " << std::dec << i << std::endl;

        std::cout << "Name Position: 0x" << std::hex << header.name << std::endl;

        std::cout << "Type: ";
        switch(header.type)
        {
        case ELF::SectionType::PROGBITS:
            std::cout << "PROGBITS";
            break;

        case ELF::SectionType::SYMTAB:
            std::cout << "SYMTAB";
            break;

        case ELF::SectionType::STRTAB:
            std::cout << "STRTAB";
            break;

        case ELF::SectionType::RELA:
            std::cout << "RELA";
            break;

        case ELF::SectionType::HASH:
            std::cout << "HASH";
            break;

        case ELF::SectionType::DYNAMIC:
            std::cout << "DYNAMIC";
            break;

        case ELF::SectionType::NOTE:
            std::cout << "NOTE";
            break;

        case ELF::SectionType::NOBITS:
            std::cout << "NOBITS";
            break;

        case ELF::SectionType::REL:
            std::cout << "REL";
            break;

        case ELF::SectionType::SHLIB:
            std::cout << "SHLIB";
            break;

        case ELF::SectionType::DYNSYM:
            std::cout << "DYNSYM";
            break;

        case ELF::SectionType::INIT_ARRAY:
            std::cout << "INIT_ARRAY";
            break;

        case ELF::SectionType::FINI_ARRAY:
            std::cout << "FINI_ARRAY";
            break;

        case ELF::SectionType::PREINIT_ARRAY:
            std::cout << "PREINIT_ARRAY";
            break;

        case ELF::SectionType::GROUP:
            std::cout << "GROUP";
            break;

        case ELF::SectionType::SYMTAB_SHNDX:
            std::cout << "SYMTAB_SHNDX";
            break;

        case ELF::SectionType::NUM:
            std::cout << "NUM";
            break;

        case ELF::SectionType::NONE:
        default:
            std::cout << "NULL";
            break;
        }
        std::cout << std::endl;

        // std::cout << "Flags";

        std::cout << "Virtual Address: 0x" << std::hex << header.addr << std::endl;
        std::cout << "Offset: 0x" << header.offset << std::endl;
        std::cout << "Size: 0x" << header.size << std::endl;
        std::cout << "Link: 0x" << header.link << std::endl;
        std::cout << "Info: 0x" << header.info << std::endl;
        std::cout << "Address Alignment: 0x" << header.addralign << std::endl;
        std::cout << "Entry Size: 0x" << header.entsize << std::endl;
    }
}
