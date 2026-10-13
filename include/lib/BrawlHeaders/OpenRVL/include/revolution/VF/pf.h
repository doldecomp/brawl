#ifndef RVL_SDK_VF_PF_H
#define RVL_SDK_VF_PF_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PF_RESULT_OK = 0,
    PF_RESULT_INVALID = 10,
} PFResult;

typedef struct PF_ENT_ITER {
    char _0x0[0x8];
    u32 _0x8;
    char _0xC[0x2c];
    void* unk;
    char _0x3c[0x31];
} PF_ENT_ITER;

typedef struct PF_DIR_ENT {
    char _0x0[0x228];
    u32 _0x228;
    void* cache;
    char _0x230[4];
    u32 _0x234;
    int sector;
    short offset;
} PF_DIR_ENT;

#ifdef __cplusplus
}
#endif
#endif
