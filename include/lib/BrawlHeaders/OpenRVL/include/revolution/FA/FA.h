#ifndef RVL_SDK_FA_H
#define RVL_SDK_FA_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void FAHandle;

typedef struct FAEntryInfo {
    char _0x0[0x224];
    s16 modifiedTime;
    s16 modifiedDate;
    int size;
    char _flag;
    char shortname[0xd];
    char name[0x38];
    char unk[0x1e2];
} FAEntryInfo;

#ifdef __cplusplus
}
#endif
#endif