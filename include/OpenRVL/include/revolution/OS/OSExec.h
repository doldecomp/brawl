#ifndef RVL_SDK_OS_EXEC_H
#define RVL_SDK_OS_EXEC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSExecParams {
    BOOL valid;          // at 0x0
    u32 restartCode;     // at 0x4
    u32 bootDol;         // at 0x8
    void* regionStart;   // at 0xC
    void* regionEnd;     // at 0x10
    BOOL argsUseDefault; // at 0x14
    void* argsAddr;      // at 0x18
} OSExecParams;

extern BOOL __OSInReboot;
extern u32 __OSNextPartitionType;

void __OSGetExecParams(OSExecParams* out);
void __OSSetExecParams(const OSExecParams* params, OSExecParams* addr);
void __OSLaunchMenu(void);
void __OSBootDol(u32 offset, u32 resetCode, const char** argv);
void __OSRelaunchTitle(void);
void __OSReturnToMenul(u8 type, const char* arg0, ...);
void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart,
                       void* regionEnd, BOOL argsUseDefault, s32 argc,
                       char* argv[]);
void __OSLaunchNextFirmware(void);
BOOL __OSCheckCompanyCode(u64 titleId, BOOL diskApp);
void __OSLaunchTitle(u64 titleId);
void __OSLaunchPartition(u64 titleId, u32 launchCode, char* const argv[]);
void OSLaunchPartitionl(u64 titleId, u32 launchCode, const char* arg0, ...);

#ifdef __cplusplus
}
#endif
#endif
