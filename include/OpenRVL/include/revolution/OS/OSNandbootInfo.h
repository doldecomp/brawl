#ifndef RVL_SDK_OS_NANDBOOT_INFO_H
#define RVL_SDK_OS_NANDBOOT_INFO_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSNandbootInfoHeader {
    u32 CheckSum;    // at 0x0
    u32 ArgOffset;   // at 0x4
    u8 reserved[2];  // at 0x8
    u8 LastAppType;  // at 0xA
    u8 ReturnType;   // at 0xB
    u32 ArgValue;    // at 0xC
    u8 padding[8];   // at 0x10
    u64 LastTitleId; // at 0x18
} OSNandbootInfoHeader;

typedef struct OSNandbootInfo {
    u32 CheckSum;     // at 0x0
    u32 ArgOffset;    // at 0x4
    u8 reserved[2];   // at 0x8
    u8 LastAppType;   // at 0xA
    u8 ReturnType;    // at 0xB
    u32 ArgValue;     // at 0xC
    u8 padding[8];    // at 0x10
    u64 LastTitleId;  // at 0x18
    u8 args[0x1000];  // at 0x20
} OSNandbootInfo;

BOOL __OSCreateNandbootInfo(void);
BOOL __OSWriteNandbootInfo(OSNandbootInfo* info);
BOOL __OSGetNandbootInfoHeader(OSNandbootInfoHeader* header);
u64 OSGetLastTitleId(void);

#ifdef __cplusplus
}
#endif
#endif
