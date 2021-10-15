#include "readelf.hpp"
#include <iostream>

int main()
{
    ELF::Reader reader("test");

    std::cout << "ALL VALUES ARE IN HEX" << std::endl;
    
    std::cout << std::hex;

    // ELF magic header.
    auto magic = reader.get_file_header_magic_number();
    std::cout << "Magic: " << 
        static_cast<int>(magic[0]) << " " << 
        static_cast<int>(magic[1]) << " " << 
        static_cast<int>(magic[2]) << " " << 
        static_cast<int>(magic[3]) << std::endl;


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
    uint64_t entry = reader.get_file_header_entry_point();
    std::cout << "Entry Point: " << entry << std::endl;

    // Start of program header
    uint64_t phoff = reader.get_file_header_start_of_program_header_table();
    std::cout << "Start of Program Header: " << phoff << std::endl;

    // Start of section header
    uint64_t shoff = reader.get_file_header_start_of_section_header_table();
    std::cout << "Start of Section Header: " << shoff << std::endl;

    // Flags
    uint32_t flags = reader.get_file_header_flags();
    std::cout << "Flags: " << flags << std::endl;
}
