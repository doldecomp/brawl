#include <cstring>
#include <gf/gf_thread.h>
#include <nt/etc/nt_etc_dwc.h>
#include <nt/etc/nt_etc_so.h>
#include <revolution/OS/OSHardware.h>
#include <revolution/OS/OSThread.h>
#include <revolution/SO/SOBasic.h>
#include <sr/sr_common.h>

nteSO::nteSO() {
    m_actionDoneNotifier = nullptr;
    m_isAlive = true;
    m_action = NoAction;
}

nteSO::~nteSO() {
    m_isAlive = false;
    int _ret, isTerminated;
    while (!(isTerminated = OSIsThreadTerminated(&m_thread) == true)) {
        _ret = OSResumeThread(&m_thread);
        OSSleepTicks((s64)((OS_BUS_CLOCK_SPEED / 4) / 1000) * 10);
    }
}

void nteSO::run() {
    while (m_isAlive) {
        if (m_action == DoStartup) {
            SOInitInfo initInfo;
            memset(&initInfo, 0, sizeof(SOInitInfo));
            initInfo.allocator = nteSO::SOAlloc;
            initInfo.dealloc = nteSO::SOFree;
            int code = SOInit(&initInfo);
            if (code == -7)
                code = 0;
            if (code == 0) {
                code = SOStartupEx(m_startupParam);
                if (code == -7)
                    code = 0;
            }
            if (m_actionDoneNotifier)
                m_actionDoneNotifier->notifyDoneSOProc(nteSODone::Startup, code);
        } else if (m_action == DoFinish) {
            SOCleanup();
            s32 code = SOFinish();
            if (code == -7)
                code = 0;
            if (m_actionDoneNotifier)
                m_actionDoneNotifier->notifyDoneSOProc(nteSODone::Finish, code);
        }
        m_action = NoAction;
        s32 ret = OSSuspendThread(&m_thread);
    }
}

bool nteSO::startup(nteSODone* doneNotifier, u32 startupParam) {
    if (m_action != NoAction)
        return false;
    if (!doneNotifier)
        return false;
    m_startupParam = startupParam;
    m_action = DoStartup;
    m_actionDoneNotifier = doneNotifier;
    s32 _ret = OSResumeThread(&m_thread);
    return true;
}

bool nteSO::finish(nteSODone* doneNotifier) {
    if (m_action != NoAction)
        return false;
    if (!doneNotifier)
        return false;
    m_action = DoFinish;
    m_actionDoneNotifier = doneNotifier;
    s32 _ret = OSResumeThread(&m_thread);
    return true;
}

void* nteSO::SOAlloc(int _unused, u32 size) {
    return nteDWC::AllocEx(0, size, 0x20);
}

void nteSO::SOFree(int _unused, void* ptr) {
    nteDWC::FreeEx(0, ptr, 0);
}

void nteSO::showError(s32 code) { }
