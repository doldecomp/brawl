#ifndef METROTRK_DOLPHIN_TRK_H
#define METROTRK_DOLPHIN_TRK_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void InitMetroTRK(void);
void InitMetroTRK_BBA(void);

void EnableMetroTRKInterrupts(void);
void TRK_flush_cache(void*, size_t);

#ifdef __cplusplus
}
#endif
#endif
