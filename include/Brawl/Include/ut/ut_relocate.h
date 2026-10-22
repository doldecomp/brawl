#pragma once

#include <types.h>

/**
 * 32-byte file header for certain .dat files, such as /toy/seal/ty_seal_data.dat
 */
struct DATHeader {
    u32 fileSz;      // bytes
    u32 dataSz;      // bytes
    u32 nRels;       // 32-bit words
    u32 nSymbols;    // DATSymbols
    u32 nImports;    // DATImports
    u32 unk14;
    u32 isAbsolute; // if false, apply relocations to the data section and set to true
    u32 unk1C;
};

struct DATSymbol {
    u32 offset; // offset into data section
    u32 name;   // offset into strtab section
};

/**
 * A record representing the location of an reference to a symbol that
 * is undefined in this utRelocate module, but can be resolved against another
 * utRelocate that defines the symbol via utRelocate::resolveReference.
 *
 * The locations of the references are compactly encoded into the .dat file.
 * DATImport::offset gives the first offset into the data section in which a reference is found;
 * the word at that offset gives another offset where the next reference is found.
 * Thus, locateExtern grabs the next offset as it performs each relocation, stopping when
 * it reaches the sentinel value, 0xFFFFFFFF.
 */
struct DATImport {
    u32 offset; // offset into data section
    u32 name;   // offset into strtab section
};

/**
 * A relocatable .dat file that has been loaded into main memory.
 *
 * A .dat file contains:
 *
 * 1. A 32-byte header, described in DATHeader
 * 2. A main payload, called the "data" section here
 * 3. A rel table containing offsets into the data section where a defined symbol is used
 * 4. A symbol table, with entries defining the name of a symbol and its offset in the data section
 * 5. An import table containing offsets into the data section where an undefined symbol is used
 * 6. A string table containing the names of all of the symbols used by the module.
 */
class utRelocate {
    DATHeader m_hdr;
    u8* m_dataStart;
    const u32* m_relStart;
    const DATSymbol* m_symtabStart;
    const DATImport* m_importStart;
    const char* m_strtabStart;

    // Resolve all internal relocations
    void relocate(u8* fileBuf) {
        if (!m_hdr.isAbsolute) {
            for (u32 i = 0; i < m_hdr.nRels; i++) {
                u32 base = reinterpret_cast<u32>(m_dataStart);
                *reinterpret_cast<u32*>(&m_dataStart[m_relStart[i]]) += base;
            }
            reinterpret_cast<DATHeader*>(fileBuf)->isAbsolute = true;
        }
    }
public:
    const char* getImportName(s32 i, u32 nImports) const {
        if (i < 0 || nImports <= i)
            return 0;
        return m_strtabStart + m_importStart[i].name;
    }

    utRelocate(u8* fileBuf, u32 fileSz);
    ~utRelocate();
    void* getPublicAddress(const char* name) const;
    void resolveReference(const utRelocate* p1);
    void locateExtern(const char* externName, void* addr);
};
