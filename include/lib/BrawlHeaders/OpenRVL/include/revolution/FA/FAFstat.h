#ifndef RVL_SDK_FA_FSTAT_H
#define RVL_SDK_FA_FSTAT_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAStat {
    int filesize;
    s16 accessDate;
    s16 modifiedTime;
    s16 modifiedDate;
    s16 createdTime;
    s16 createdDate;
    u16 unk;
    char flags;
} FAStat;

int FAFstat(const char* filepath, FAStat* st);

#ifdef __cplusplus
}
#endif
#endif