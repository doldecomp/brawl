#include <gf/gf_decomp.h>
#include <gf/gf_memory_pool.h>
#include <revolution/CX/CXCompression.h>
#include <types.h>

void gfDecomp::decomp(const CXStream* src, void* dest) {
    if (!m_ready) {
        m_algo = static_cast<CompressionAlgo::Enum>(src->m_type << 4);
        m_uncompSize = CXGetUncompressedSize(src);
        unk8 = gfMemoryPool::alloc(m_heapAddr, m_uncompSize, 0x20);
        switch (m_algo) {
            case CompressionAlgo::RL:
                CXInitUncompContextRL(&m_ctx, unk8);
                break;
            case CompressionAlgo::LZ:
                CXInitUncompContextLZ(&m_ctx, unk8);
                break;
            case CompressionAlgo::Huffman:
                CXInitUncompContextHuffman(&m_ctx, unk8);
                break;
            default:
                break;
        }
        m_ready = true;
    }
    switch (m_algo) {
        case CompressionAlgo::RL:
            CXReadUncompRL(&m_ctx, src, dest);
            break;
        case CompressionAlgo::LZ:
            CXReadUncompLZ(&m_ctx, src, dest);
            break;
        case CompressionAlgo::Huffman:
            CXReadUncompHuffman(&m_ctx, src, dest);
            break;
        default:
            break;
    }
}
