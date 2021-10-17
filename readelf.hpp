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

namespace ELF
{
    namespace details {
        struct FileHeader;
        struct ProgramHeader;
        struct SectionHeader;
    }

    // ------------------------------------------------------------------------------------------------

    enum class Endianness
    {
        Little,
        Big
    };

    // ------------------------------------------------------------------------------------------------

    // Identifies the target operating system ABI.
    enum class ABIType
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

    struct FileHeaderInfo
    {
        std::array<uint8_t, 4> magic;
        uint32_t bits;
        Endianness endian;
        ABIType abi;
        ObjectFileType object_file_type;
        InstructionSetArchitectureType instruction_set_architecture_type;
        uint64_t entry_point;
        uint64_t start_of_program_header_table;
        uint64_t start_of_section_header_table;
        uint32_t flags;
        uint16_t size;
        uint16_t program_header_size;
        uint16_t number_of_program_entries;
        uint16_t section_header_size;
        uint16_t number_of_section_entries;
        uint16_t index_of_section_header;
    };

    struct ProgramHeaderInfo
    {
        SegmentType type;
        uint32_t flags; // 0x1 -> Execute, 0x2 -> Write, 0x4 -> Read.
        uint64_t offset;
        uint64_t virtual_address;
        uint64_t physical_address;
        uint64_t file_size;
        uint64_t memory_size;
        uint64_t alignment;
    };

    class Reader
    {
    public:
        Reader(const std::string& filename);
        ~Reader();

        const FileHeaderInfo get_file_header() const;
        const std::vector<ProgramHeaderInfo> get_program_headers() const;

    private:
        void read_file_header(const std::vector<uint8_t>& buffer);
        void read_program_headers(const std::vector<uint8_t>& buffer);

    private:
        using PtrFileHeader = std::unique_ptr<details::FileHeader>;
        PtrFileHeader file_header;

        using PtrProgramHeader = std::unique_ptr<details::ProgramHeader>;
        std::vector<PtrProgramHeader> program_headers;
    };
}


#endif // READELF_HPP
