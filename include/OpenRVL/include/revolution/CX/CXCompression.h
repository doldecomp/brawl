#ifndef RVL_SDK_CX_COMPRESSION_H
#define RVL_SDK_CX_COMPRESSION_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CXStream {
    u8 m_type : 4; // compression type
    u8 pad : 4;
    u32 m_size : 24; // 24-bit uncompressed size, in little-endian
    u32 m_size32; // TODO: 32-bit uncompressed size, in little-endian?
    u8 m_data[0x1]; // UBFIX: this is a C99 flexible array member
} CXStream;
// TODO size

typedef struct CXUncompContext {
    u8 unk0[0x30];
} CXUncompContext;
// TODO size

void CXInitUncompContextRL(CXUncompContext* ctx, void* dest);
void CXInitUncompContextLZ(CXUncompContext* ctx, void* dest);
void CXInitUncompContextHuffman(CXUncompContext* ctx, void* dest);

s32 CXReadUncompRL(CXUncompContext* ctx, const CXStream* src, u32 len);
s32 CXReadUncompLZ(CXUncompContext* ctx, const CXStream* src, u32 len);
s32 CXReadUncompHuffman(CXUncompContext* ctx, const CXStream* src, u32 len);

void CXUncompressLZ(void* data, void* destination);
u32 CXGetUncompressedSize(const void* data);

#ifdef __cplusplus
}
#endif
#endif
