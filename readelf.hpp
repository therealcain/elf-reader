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

namespace ELF
{
    namespace details {
        struct FileHeader;
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
        No_Specific                                    = 0x0U,
        AT_And_T_WE_32100                              = 0x01U,
        SPARC                                          = 0x02U,
        X86                                            = 0x03,
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
        NEC_V800                                       = 0x024U,
        Fujitsu_FR20                                   = 0x025U,
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
        TMS320C6000_Family                             = 0x8C,
        MCST_Elbrus_e2k                                = 0xAFU,
        ARM_64bit                                      = 0xB7U,
        RISC_V                                         = 0xF3U,
        Berkeley_Packet_Filter                         = 0xF7U,
        WDC_65C816                                     = 0x101U
    };

    // ------------------------------------------------------------------------------------------------

    class Reader
    {
    public:
        Reader(const std::string& filename);
        ~Reader();

        // File Header
        std::array<uint8_t, 4> get_file_header_magic_number() const;
        uint8_t get_file_header_32_or_64_bit() const;
        Endianness get_file_header_endianness() const;
        ABIType get_file_header_abi() const;
        ObjectFileType get_file_header_object_file_type() const;
        InstructionSetArchitectureType get_file_header_isa_type() const;
        uint64_t get_file_header_entry_point() const;
        uint64_t get_file_header_start_of_program_header_table() const;
        uint64_t get_file_header_start_of_section_header_table() const;
        uint32_t get_file_header_flags() const;

    private:
        std::unique_ptr<details::FileHeader> file_header;
    };
}


#endif // READELF_HPP
