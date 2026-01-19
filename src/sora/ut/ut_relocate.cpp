#include <cstring>
#include <revolution/OS.h>
#include <types.h>
#include <ut/ut_relocate.h>

// NONMATCHING regswap
utRelocate::utRelocate(u8* fileBuf, u32 fileSz) {
    m_dataStart = nullptr;
    m_relStart = nullptr;
    m_symtabStart = nullptr;
    m_importStart = nullptr;
    m_strtabStart = nullptr;
    std::memcpy(&m_hdr, fileBuf, sizeof(m_hdr));
    if (m_hdr.fileSz != fileSz) {
        OSReport("utRelocate: byte-order mismatch! Please check data format\n");
    }

    u32 fp = sizeof(m_hdr);
    if (m_hdr.dataSz) {
        m_dataStart = fileBuf + sizeof(m_hdr);
        fp = m_hdr.dataSz + sizeof(m_hdr);
    }

    if (m_hdr.nRels) {
        m_relStart = reinterpret_cast<u32*>(fileBuf + fp);
        fp += m_hdr.nRels * sizeof(m_relStart[0]);
    }

    if (m_hdr.nSymbols) {
        m_symtabStart = reinterpret_cast<DATSymbol*>(fileBuf + fp);
        fp += m_hdr.nSymbols * sizeof(m_symtabStart[0]);
    }

    if (m_hdr.nImports) {
        m_importStart = reinterpret_cast<DATImport*>(fileBuf + fp);
        fp += m_hdr.nImports * sizeof(m_importStart[0]);
    }

    if (fp < m_hdr.fileSz) {
        m_strtabStart = reinterpret_cast<char*>(fileBuf + fp);
    }

    if (!m_hdr.isAbsolute) {
        // Resolve all internal relocations
        for (u32 i = 0; i < m_hdr.nRels; i++) {
            u8* datap = m_dataStart;
            u32 offset = reinterpret_cast<u32>(datap);
            *reinterpret_cast<u32*>(&datap[m_relStart[i]]) += offset;
        }
        reinterpret_cast<DATHeader*>(fileBuf)->isAbsolute = true;
    }
}

utRelocate::~utRelocate() { }

void* utRelocate::getPublicAddress(const char* symName) const {
    const DATSymbol* sym;
    for (u32 i = 0; i < m_hdr.nSymbols; i++) {
        sym = m_symtabStart;
        if (!std::strcmp(m_strtabStart + sym[i].name, symName)) {
            return m_dataStart + sym[i].offset;
        }
    }
    return nullptr;
}

static const u32 EndMarker = 0xFFFFFFFF;

// Resolve all references to externName within this module to addr
void utRelocate::locateExtern(const char* externName, void* addr) {
    u32 nextOffset = EndMarker;
    for (u32 i = 0; i < m_hdr.nImports; i++) {
        if (!std::strcmp(externName, m_strtabStart + m_importStart[i].name)) {
            nextOffset = m_importStart[i].offset;
            break;
        }
    }
    if (nextOffset == EndMarker) {
        return;
    } else {
        while (nextOffset != EndMarker && nextOffset < m_hdr.dataSz) {
            void** ref = reinterpret_cast<void**>(m_dataStart + nextOffset);
            nextOffset = reinterpret_cast<u32>(*ref);
            *ref = addr;
        }
    }
}

// NONMATCHING regswaps
// Resolve all undefined references in this utRelocate against
// the symbols defined in other
void utRelocate::resolveReference(const utRelocate* other) {
    for (s32 i = 0; i < m_hdr.nImports; i++) {
        const char* importName = getImportName(i, m_hdr.nImports);
        if (importName) {
            void* addr = reinterpret_cast<void*>(other->getPublicAddress(importName));
            if (!addr) {
                OSReport("utRelocate: not found symbol! ->[%s] \n", importName);
            }
            locateExtern(importName, addr);
        }
    }
}
