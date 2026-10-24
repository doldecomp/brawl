#ifndef RVL_SDK_OS_PLAY_TIME_H
#define RVL_SDK_OS_PLAY_TIME_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct ESTicketView;

typedef enum {
    OSPLAYTIME_PERMANENT = 0,
    OSPLAYTIME_LIMITED = 1,
    OSPLAYTIME_LIMITED_LAUNCH = 4,
    OSPLAYTIME_OTHER = 9,
} __OSPlayTimeType;

BOOL OSPlayTimeIsLimited(void);
BOOL __OSWriteExpiredFlag(void);
s32 __OSGetPlayTime(struct ESTicketView* ticket, __OSPlayTimeType* type,
                    u32* playTime);
void __OSInitPlayTime(void);

#ifdef __cplusplus
}
#endif
#endif
