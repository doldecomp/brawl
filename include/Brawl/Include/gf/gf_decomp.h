#pragma once

#include <StaticAssert.h>
#include <revolution/CX/CXCompression.h>
#include <types.h>

namespace CompressionAlgo {
    enum Enum {
        LZ = 0x10,
        Huffman = 0x20,
        RL = 0x30
    };
}

class gfDecomp {
public:
    bool m_ready;
    CompressionAlgo::Enum m_algo;
    void* m_decompData;
    u32 m_decompSize;
    void* m_heapAddr; // +0x10
    CXUncompContext m_ctx;

    u8 unk18[0x1F0];

    gfDecomp(void* heapAddr) :
        m_ready(false),
        m_decompData(nullptr),
        m_decompSize(0),
        m_heapAddr(heapAddr) { }
    void decomp(const CXStream* src, u32 streamLen);
};
// TODO size
