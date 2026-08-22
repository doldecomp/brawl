#include <gf/gf_decomp.h>
#include <gf/gf_memory_pool.h>
#include <revolution/CX/CXCompression.h>
#include <types.h>

void gfDecomp::decomp(const CXStream* src, u32 streamLen) {
    if (!m_ready) {
        m_algo = static_cast<CompressionAlgo::Enum>(src->m_type << 4);
        m_decompSize = CXGetUncompressedSize(src);
        m_decompData = gfMemoryPool::alloc(m_heapAddr, m_decompSize, 0x20);
        switch (m_algo) {
            case CompressionAlgo::RL:
                CXInitUncompContextRL(&m_ctx, m_decompData);
                break;
            case CompressionAlgo::LZ:
                CXInitUncompContextLZ(&m_ctx, m_decompData);
                break;
            case CompressionAlgo::Huffman:
                CXInitUncompContextHuffman(&m_ctx, m_decompData);
                break;
            default:
                break;
        }
        m_ready = true;
    }
    switch (m_algo) {
        case CompressionAlgo::RL:
            CXReadUncompRL(&m_ctx, src, streamLen);
            break;
        case CompressionAlgo::LZ:
            CXReadUncompLZ(&m_ctx, src, streamLen);
            break;
        case CompressionAlgo::Huffman:
            CXReadUncompHuffman(&m_ctx, src, streamLen);
            break;
        default:
            break;
    }
}
