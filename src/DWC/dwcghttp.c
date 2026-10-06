#include <DWC/dwc_ghttp.h>
#include <string.h>

extern void DWC_Printf(u32 level, const char* format, ...);
extern BOOL DWCi_IsError(void);
extern void DWC_Free(int kind, void* allocation, int size);
extern void fn_8037EA50(void);
extern void fn_8037EAA0(void);
extern void fn_8037EEDC(void);
extern const char lbl_80489310[];
extern const char lbl_80489320[];
extern DWCGHTTPParamEntry* lbl_805A0F68;
extern s32 lbl_805A0F6C;

BOOL DWC_InitGHTTP(void) {
    DWC_Printf(4, lbl_80489310);
    fn_8037EA50();
    ++lbl_805A0F6C;
    return 1;
}

BOOL DWC_ShutdownGHTTP(void) {
    DWC_Printf(4, lbl_80489320);
    if (lbl_805A0F6C > 0) {
        fn_8037EAA0();
        --lbl_805A0F6C;
        if (lbl_805A0F6C == 0) {
            DWCGHTTPParamEntry* entry = lbl_805A0F68;
            while (entry != NULL) {
                DWCGHTTPParamEntry* next = entry->next;
                if (entry->buffer != NULL) DWC_Free(6, entry->buffer, 0);
                DWC_Free(6, entry, 0);
                entry = next;
            }
            lbl_805A0F68 = NULL;
        }
    }
    return 1;
}

BOOL DWC_ProcessGHTTP(void) {
    BOOL error = DWCi_IsError();
    if (!error) fn_8037EEDC();
    return error == 0;
}

void GHTTPProgressCallback(s32 request, s32 state, const char* buffer, u32 bufferSize,
                           u32 received, u32 total, DWCGHTTPParamEntry* entry) {
    if (entry->progress != NULL) entry->progress(state, buffer, bufferSize, received, total, entry->parameter);
}

void DWCi_RemoveDWCGHTTPParamEntry(DWCGHTTPParamEntry* entry) {
    DWCGHTTPParamEntry* current = lbl_805A0F68;
    DWCGHTTPParamEntry* previous;
    if (current == NULL) return;
    if (current == entry) {
        DWCGHTTPParamEntry* next = current->next;
        DWC_Free(6, current, 0);
        lbl_805A0F68 = next;
        return;
    }
    do {
        previous = current;
        current = previous->next;
        if (current == NULL) return;
    } while (current != entry);
    previous->next = current->next;
    DWC_Free(6, current, 0);
}

extern void* DWC_Alloc(int kind, u32 size);
extern void DWCi_SetError(s32 error, s32 code);
extern void* fn_8037EFE8(void);
extern s32 fn_8037ED14(const char* url, void* post, BOOL blocking,
                      BOOL (*completed)(s32, s32, void*, u32, DWCGHTTPParamEntry*), DWCGHTTPParamEntry* entry);
extern s32 fn_8037EAFC(const char* url, const char* headers, void* buffer, s32 bufferSize,
                      void* post, BOOL throttle, BOOL blocking,
                      void (*progress)(s32, s32, const char*, u32, u32, u32, DWCGHTTPParamEntry*),
                      BOOL (*completed)(s32, s32, void*, u32, DWCGHTTPParamEntry*), DWCGHTTPParamEntry* entry);
extern void fn_8037EFB0(s32 request, s32 time);
extern void fn_8037EF20(s32 request);
extern const char lbl_80489334[];
extern const char lbl_80489358[];
extern const char lbl_8059F070[];
extern const char lbl_8048936C[];
extern const char lbl_80489380[];
extern const char lbl_80489394[];
extern const char lbl_804893A8[];
extern const char lbl_804893BC[];

BOOL GHTTPCompletedCallback(s32 request, s32 result, void* buffer, u32 length, DWCGHTTPParamEntry* entry) {
    DWCCompletedCallback completed = entry->completed;
    BOOL clear = entry->bufferClear;
    DWC_Printf(4, lbl_80489334, result);
    if (completed == NULL) {
        DWC_Printf(4, lbl_80489358);
    } else if (result == 0) {
        completed(buffer, length, 0, entry->parameter);
    } else {
        if ((s32)length > 0) {
            char* copy = (char*)DWC_Alloc(6, length + 1);
            memcpy(copy, buffer, length);
            copy[length] = 0;
            DWC_Printf(4, lbl_8059F070, buffer);
            DWC_Free(6, copy, 0);
        }
        DWCi_HandleGHTTPError(result);
        completed(NULL, 0, result, entry->parameter);
    }
    if (result != 0 || clear == 1) {
        if (entry->buffer == NULL) clear = 1;
        else DWC_Free(6, entry->buffer, 0);
    }
    DWCi_RemoveDWCGHTTPParamEntry(entry);
    return clear != 0;
}

void DWC_GHTTPNewPost(void** post) {
    DWC_Printf(4, lbl_8048936C);
    *post = fn_8037EFE8();
    if (post == NULL) {
        DWCi_HandleGHTTPError(-6);
        DWC_Printf(4, lbl_80489380);
    }
}

static DWCGHTTPParamEntry* createEntry(DWCCompletedCallback completed, DWCProgressCallback progress,
                                      BOOL bufferClear, void* parameter) {
    DWCGHTTPParamEntry* entry = (DWCGHTTPParamEntry*)DWC_Alloc(6, sizeof(DWCGHTTPParamEntry));
    if (entry == NULL) return NULL;
    entry->parameter = parameter;
    entry->completed = completed;
    entry->progress = progress;
    entry->bufferClear = bufferClear;
    entry->buffer = NULL;
    entry->next = lbl_805A0F68;
    lbl_805A0F68 = entry;
    return entry;
}

s32 DWC_PostGHTTPData(const char* url, void** post, DWCCompletedCallback completed, void* parameter) {
    DWCGHTTPParamEntry* entry;
    s32 request;
    DWC_Printf(4, lbl_80489394);
    if (DWCi_IsError()) return -1;
    entry = createEntry(completed, NULL, 1, parameter);
    if (entry == NULL) {
        DWCi_HandleGHTTPError(-6);
        DWC_Printf(4, lbl_80489380);
        completed(NULL, 0, -6, parameter);
        return -6;
    }
    request = fn_8037ED14(url, *post, 0, GHTTPCompletedCallback, entry);
    if (request < 0) {
        DWCi_HandleGHTTPError(request);
        completed(NULL, 0, request, parameter);
        DWCi_RemoveDWCGHTTPParamEntry(entry);
    }
    entry->request = request;
    fn_8037EFB0(request, 1);
    return request;
}

s32 DWC_GetGHTTPDataEx(const char* url, s32 bufferSize, BOOL bufferClear,
                       DWCProgressCallback progress, DWCCompletedCallback completed, void* parameter) {
    DWCGHTTPParamEntry* entry;
    void* buffer = NULL;
    s32 request;
    DWC_Printf(4, lbl_804893A8);
    if (DWCi_IsError()) return -1;
    entry = createEntry(completed, progress, bufferClear, parameter);
    if (entry == NULL) {
        DWCi_HandleGHTTPError(-6);
        DWC_Printf(4, lbl_80489380);
        completed(NULL, 0, -6, parameter);
        return -6;
    }
    if (bufferSize > 0) {
        buffer = DWC_Alloc(6, bufferSize);
        if (buffer == NULL) {
            DWCi_HandleGHTTPError(-6);
            DWC_Printf(4, lbl_80489380);
            completed(NULL, 0, -6, parameter);
            DWCi_RemoveDWCGHTTPParamEntry(entry);
            return -6;
        }
        entry->buffer = buffer;
    }
    request = fn_8037EAFC(url, NULL, buffer, bufferSize, NULL, 0, 0,
                          progress == NULL ? NULL : GHTTPProgressCallback,
                          GHTTPCompletedCallback, entry);
    if (request < 0) {
        DWCi_HandleGHTTPError(request);
        completed(NULL, 0, request, parameter);
        if (entry->buffer != NULL) DWC_Free(6, entry->buffer, 0);
        DWCi_RemoveDWCGHTTPParamEntry(entry);
    }
    entry->request = request;
    fn_8037EFB0(request, 1);
    return request;
}

void DWC_CancelGHTTPRequest(s32 request) {
    DWCGHTTPParamEntry* entry;
    fn_8037EF20(request);
    for (entry = lbl_805A0F68; entry != NULL && entry->request != request; entry = entry->next) { }
    if (entry != NULL) {
        if (entry->buffer != NULL) DWC_Free(6, entry->buffer, 0);
        DWCi_RemoveDWCGHTTPParamEntry(entry);
    }
}

s32 DWCi_HandleGHTTPError(s32 result) {
    s32 error = 7;
    s32 code = -98000;
    if (result == 0) return 0;
    DWC_Printf(2, lbl_804893BC, result);
    switch (result) {
    case 1: case 20: error = 9; code = -98001; break;
    case 2: case -6: code = -98840; break;
    case 3: code = -98850; break;
    case 4: code = -98030; break;
    case 5: code = -98050; break;
    case 6: case 11: case 12: code = -98020; break;
    case 7: code = -98860; break;
    case 8: case 9: case 10: code = -98870; break;
    case 13: case 14: code = -98880; break;
    case 15: code = -98890; break;
    case 16: code = -98900; break;
    case 17: code = -98910; break;
    case -8: code = -98800; break;
    case -7: code = -98810; break;
    case -5: case -4: case -3: code = -98820; break;
    case -2: code = -98830; break;
    }
    DWCi_SetError(error, code);
    return result;
}
