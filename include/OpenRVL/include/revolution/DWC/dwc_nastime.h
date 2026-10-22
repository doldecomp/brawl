#pragma once

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DWCTime {
    s32 sec;
    s32 min;
    s32 hour;
    s32 msec;
    s32 usec;
} DWCTime;

typedef struct DWCDate {
    s32 mday;
    s32 month;
    s32 year;
    s32 wday;
    s32 yday;
} DWCDate;

BOOL DWC_GetDateTime(DWCDate *date, DWCTime *time);

#ifdef __cplusplus
}
#endif
