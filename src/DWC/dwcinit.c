#include <types.h>
#include <string.h>
#include <revolution/DWC/dwc_memfunc.h>

extern void OSRegisterVersion(const char* version);
extern void fn_80352040(int mode);
extern void fn_8034F020(BOOL initialized);
extern void fn_8034F684(void);
extern void fn_80350BBC(void);
extern void* gethostbyname(const char* name);
extern void fn_8035DFCC(void* (*alloc)(u32), void (*free)(void*),
                      void* (*realloc)(void*, u32), void* (*memalign)(int, u32));
extern void* DWCi_GsMalloc(u32 size);
extern void DWCi_GsFree(void* allocation);
extern void* DWCi_GsRealloc(void* allocation, u32 size);
extern void* DWCi_GsMemalign(int alignment, u32 size);
extern const char lbl_80489148[];
extern const char lbl_80489190[];
extern const char lbl_8059F060[];
extern char lbl_80535BE0[];
extern char lbl_804909D0[];
extern u32 lbl_805A0F50;

s32 DWC_Init(int mode, const char* gameName, u32 gamecode, DWCAlloc alloc, DWCFree free) {
    OSRegisterVersion(lbl_80489148);
    DWCi_SetMemFunc(alloc, free);
    fn_80352040(mode);
    lbl_805A0F50 = gamecode;
    fn_8035DFCC(DWCi_GsMalloc, DWCi_GsFree, DWCi_GsRealloc, DWCi_GsMemalign);
    strcpy(lbl_80535BE0, gameName);
    if (mode == 0) strcpy(lbl_804909D0, lbl_80489190);
    fn_8034F020(1);
    fn_8034F684();
    return 0;
}

void DWC_Shutdown(void) {
    fn_8035DFCC(DWCi_GsMalloc, DWCi_GsFree, DWCi_GsRealloc, DWCi_GsMemalign);
    gethostbyname(lbl_8059F060);
    fn_80350BBC();
    fn_8034F020(0);
}

u32 DWCi_GetGamecode(void) { return lbl_805A0F50; }
