/*
 * MIT License
 *
 * Copyright (c) 2021 Eviatar
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef READELF_HPP
#define READELF_HPP
#pragma once

#include <string>
#include <array>
#include <memory>
#include <vector>
#include <type_traits>
#include <climits>
#include <cstdint>

// ------------------------------------------------------------------------------------------------

namespace ELF
{
    namespace details {
        static constexpr size_t SysBits = (CHAR_BIT * sizeof(void*));

        template<typename T32, typename T64>
        using BitsBasedType = 
            typename std::conditional<SysBits == 32, T32, T64>::type;

        class EmptyClass {};
        using ZeroAllocType = EmptyClass[0]; // sizeof(ZeroAllocType) = 0.
    }

    // ------------------------------------------------------------------------------------------------

    enum class Endianness
        : uint8_t
    {
        Little = 1,
        Big    = 2
    };

    // ------------------------------------------------------------------------------------------------

    // Identifies the target operating system ABI.
    enum class ABIType
        : uint8_t
    {
        SystemV                      = 0x00U,
        HP_UX                        = 0x01U,
        NetBSD                       = 0x02U,
        Linux                        = 0x03U,
        GNU_Hurd                     = 0x04U,
        Solaris                      = 0x06U,
        AIX                          = 0x07U,
        IRIX                         = 0x08U,
        FreeBSD                      = 0x09U,
        Tru64                        = 0x0AU,
        Novell_Modesto               = 0x0BU,
        OpenBSD                      = 0x0CU,
        OpenVMS                      = 0x0DU,
        NonStop_Kernel               = 0x0EU,
        AROS                         = 0x0FU,
        FenixOS                      = 0x10U,
        CloudABI                     = 0x11U,
        Stratus_Technologies_OpenVOS = 0x12U
    };

    // ------------------------------------------------------------------------------------------------

    // Identifies object file type.
    enum class ObjectFileType
        : uint16_t
    {
        NONE   = 0x00U,
        REL    = 0x01U,
        EXEC   = 0x02U,
        DYN    = 0x03U,
        CORE   = 0x04U,
        LOOS   = 0xFE00U,
        HIOS   = 0xFEFFU,
        LOPROC = 0xFF00U,
        HIPROC = 0xFFFFU
    };

    // ------------------------------------------------------------------------------------------------

    // ISA Types
    enum class InstructionSetArchitectureType
        : uint16_t
    {
        No_Specific                                    = 0x00U,
        AT_And_T_WE_32100                              = 0x01U,
        SPARC                                          = 0x02U,
        X86                                            = 0x03U,
        M68k                                           = 0x04U,
        M88k                                           = 0x05U,
        Intel_MCU                                      = 0x06U,
        Intel_80860                                    = 0x07U,
        MIPS                                           = 0x08U,
        IBM_System                                     = 0x09U,
        MIPS_RS3000_Little_Endian                      = 0x0AU,
        // 0X0B - 0X0D reserved
        Hewlett_Packard_PA_RISC                        = 0x0EU,
        // 0x0F reserved
        Intel_80960                                    = 0x13U,
        PowerPC                                        = 0x14U,
        PowerPC_64bit                                  = 0x15U,
        S390                                           = 0x16U,
        IBM_SPU_SPC                                    = 0x17U,
        // 0x18 - 0x23 reserved
        NEC_V800                                       = 0x24U,
        Fujitsu_FR20                                   = 0x25U,
        TRW_RH32                                       = 0x26U,
        Motorola_RCE                                   = 0x27U,
        ARM                                            = 0x28U,
        Digital_Alpha                                  = 0x29U,
        SuperH                                         = 0x2AU,
        SPARC_Ver9                                     = 0x2BU,
        Siemens_TriCore_Embedded_Processor             = 0x2CU,
        Argonaut_RISC_Core                             = 0x2DU,
        Hitachi_H8_300                                 = 0x2EU,
        Hitachi_H8_300H                                = 0x2FU,
        Hitachi_H8S                                    = 0x30U,
        Hitachi_H8_500                                 = 0x31U,
        IA_64                                          = 0x32U,
        Stanford_MIPS_X                                = 0x33U,
        Motorola_ColdFire                              = 0x34U,
        Motorola_M68HC12                               = 0x35U,
        Fujitsu_MMA_Multimedia_Accelerator             = 0x36U,
        Siemens_PCP                                    = 0x37U,
        Sony_nCPU_Embedded_RISC_Processor              = 0x38U,
        Denso_NDR1_Microprocessor                      = 0x39U,
        Motorola_StarCore_Processor                    = 0x3AU,
        Toyota_ME16_Processor                          = 0x3BU,
        STMicroelectronics_ST100_Processor             = 0x3CU,
        Advanced_Logic_TinyJ_Embedded_Processor_Family = 0x3DU,
        AMD_X86_64                                     = 0x3EU,
        TMS320C6000_Family                             = 0x8CU,
        MCST_Elbrus_e2k                                = 0xAFU,
        ARM_64bit                                      = 0xB7U,
        RISC_V                                         = 0xF3U,
        Berkeley_Packet_Filter                         = 0xF7U,
        WDC_65C816                                     = 0x101U
    };

    // ------------------------------------------------------------------------------------------------

    // Identifies the type of the segment
    enum class SegmentType
        : uint32_t
    {
        NONE    = 0x00000000U,
        LOAD    = 0x00000001U,
        DYNAMIC = 0x00000002U,
        INTERP  = 0x00000003U,
        NOTE    = 0x00000004U,
        SHLIB   = 0x00000005U,
        PHDR    = 0x00000006U,
        TLS     = 0x00000007U,
        LOOS    = 0x60000000U,
        HIOS    = 0x6FFFFFFFU,
        LOPROC  = 0x70000000U,
        HIPROC  = 0x7FFFFFFFU
    };

    // ------------------------------------------------------------------------------------------------

    // Identifies the type of the section header.
    enum class SectionType
        : uint32_t
    {
        NONE          = 0x00U,
        PROGBITS      = 0x01U,
        SYMTAB        = 0x02U,
        STRTAB        = 0x03U,
        RELA          = 0x04U,
        HASH          = 0x05U,
        DYNAMIC       = 0x06U,
        NOTE          = 0x07U,
        NOBITS        = 0x08U,
        REL           = 0x09U,
        SHLIB         = 0x0AU,
        DYNSYM        = 0x0BU,
        INIT_ARRAY    = 0x0EU,
        FINI_ARRAY    = 0x0FU,
        PREINIT_ARRAY = 0x10U,
        GROUP         = 0x11U,
        SYMTAB_SHNDX  = 0x12U,
        NUM           = 0x13U
    };

    // 	Identifies the attributes of the section.
    enum class SectionAttribute
        : details::BitsBasedType<uint32_t, uint64_t>
    {
        WRITE            = 0x1U,
        ALLOC            = 0x2U,
        EXECINSTR        = 0x4U,
        MERGE            = 0x10U,
        STRINGS          = 0x20U,
        INFO_LINK        = 0x40U,
        LINK_ORDER       = 0x80U,
        OS_NONCONFORMING = 0x100U,
        GROUP            = 0x200U,
        TLS              = 0x400U,
        MASKOS           = 0x0FF00000U,
        MASKPROC         = 0xF0000000U,
        ORDERED          = 0x4000000U,
        EXCLUDE          = 0x8000000U
    };

    // ------------------------------------------------------------------------------------------------

    struct FileHeader
    {          
        uint8_t                                    magic[4];          
        uint8_t                                    bits; // class
        Endianness                                 endian;
        uint8_t                                    version1;
        ABIType                                    osabi;
        uint8_t                                    abiver;
        uint8_t                                    unused[7];
        ObjectFileType                             type;
        InstructionSetArchitectureType             machine;
        uint32_t                                   version2;
        details::BitsBasedType<uint32_t, uint64_t> entry;
        details::BitsBasedType<uint32_t, uint64_t> phoff;
        details::BitsBasedType<uint32_t, uint64_t> shoff;
        uint32_t                                   flags;
        uint16_t                                   ehsize;
        uint16_t                                   phentsize;
        uint16_t                                   phnum;
        uint16_t                                   shentsize;
        uint16_t                                   shnum;
        uint16_t                                   shstrndx;
    };

    struct ProgramHeader
    {
        SegmentType                                              type;
        details::BitsBasedType<details::ZeroAllocType, uint32_t> flags64; // flags for 64bit
        details::BitsBasedType<uint32_t, uint64_t>               offset;
        details::BitsBasedType<uint32_t, uint64_t>               vaddr;
        details::BitsBasedType<uint32_t, uint64_t>               paddr;
        details::BitsBasedType<uint32_t, uint64_t>               filesz;
        details::BitsBasedType<uint32_t, uint64_t>               memsz;
        details::BitsBasedType<uint32_t, details::ZeroAllocType> flags32; // flags for 32bit
        details::BitsBasedType<uint32_t, uint64_t>               align;
    };

    struct SectionHeader
    {
        uint32_t                                   name;
        SectionType                                type;
        SectionAttribute                           flags;
        details::BitsBasedType<uint32_t, uint64_t> addr;
        details::BitsBasedType<uint32_t, uint64_t> offset;
        details::BitsBasedType<uint32_t, uint64_t> size;
        uint32_t                                   link;
        uint32_t                                   info;
        details::BitsBasedType<uint32_t, uint64_t> addralign;
        details::BitsBasedType<uint32_t, uint64_t> entsize;
    };

    // ------------------------------------------------------------------------------------------------

    class Reader
    {
    public:
        Reader(const std::string& filename);
        ~Reader();

        inline const FileHeader& get_file_header() const { return file_header; }
        inline const std::vector<ProgramHeader> &get_program_headers() const { return program_headers; }
        inline const std::vector<SectionHeader>& get_section_headers() const { return section_headers; }

    private:
        void read_file_header(const std::vector<uint8_t>& buffer);
        void read_program_headers(const std::vector<uint8_t>& buffer);
        void read_section_headers(const std::vector<uint8_t>& buffer);

    private:
        FileHeader file_header;
        std::vector<ProgramHeader> program_headers;
        std::vector<SectionHeader> section_headers;
    };
}


#endif // READELF_HPP
