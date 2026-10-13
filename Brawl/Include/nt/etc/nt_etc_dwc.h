#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <nt/etc/nt_etc_so.h>
#include <revolution/OS/OSMutex.h>
#include <types.h>

class nteDWC : public gfTask, public nteSODone {
    // TODO: ID this class
    struct Unk60Class {
        virtual void func0(s32 p1);
    };

    OSMutex m_mutex;
    u32 m_loggedIn;
    Unk60Class* unk60;
    nteSODone* unk64; // TODO: confirm type
    bool m_initialized;
    u32 unk6C; // TODO: it's an index into a URL table
    nteSO m_socketHandler;
    const char* m_name;
    u32 m_appCode;

public:
    nteDWC();
    virtual void processDefault();
    virtual ~nteDWC();
    virtual void notifyDoneSOProc(nteSODone::NotifType nType, s32 code);

    bool startupDWC();
    bool finishDWC();
    bool login(s32 p1, s32 p2, s32 p3, s32 p4);
    bool logout();
    bool isOnline() const;
    s64 getTime() const;

    static void* AllocEx(int heap, size_t size, int align);
    static void FreeEx(int heap, void*, int unused = 0);
    static void callbackLogin(s32 p1, s32 p2, void* p3);
};
static_assert(sizeof(nteDWC) == 0x3C8, "Class is wrong size!");
