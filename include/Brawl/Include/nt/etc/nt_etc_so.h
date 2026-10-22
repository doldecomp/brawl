#pragma once

#include <StaticAssert.h>
#include <gf/gf_thread.h>
#include <types.h>

class nteSODone {
public:
    enum NotifType {
        Startup,
        Finish
    };

    virtual void notifyDoneSOProc(NotifType notifType, s32 errCode);
};

class nteSO : public gfThread {
    enum Action {
        NoAction,
        DoStartup,
        DoFinish
    };

    Action m_action;
    bool m_isAlive;
    nteSODone* m_actionDoneNotifier;
    u32 m_startupParam;
public:
    nteSO();
    ~nteSO();
    virtual void run();
    bool startup(nteSODone* doneNotifier, u32 startupParam);
    bool finish(nteSODone* doneNotifier);
    static void* SOAlloc(int _unused, u32 size);
    static void SOFree(int _unused, void* ptr);
    static void showError(s32 code);
};
static_assert(sizeof(nteSO) == 0x350, "Class is the wrong size!");
