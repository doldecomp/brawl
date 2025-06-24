#include <gf/gf_heap_manager.h>
#include <gf/gf_task.h>
#include <nt/etc/nt_etc_dwc.h>
#include <revolution/DWC/dwc_init.h>
#include <revolution/DWC/dwc_error.h>
#include <revolution/DWC/dwc_main.h>
#include <revolution/DWC/dwc_nastime.h>
#include <revolution/DWC/neterrorcode.h>
#include <revolution/OS/OSMutex.h>
#include <revolution/OS/OSTime.h>
#include <sr/sr_getappname.h>

static OSMutex NteDWCMutex;

nteDWC::nteDWC() : gfTask("nteDWC", Category_Network, 14, 13, true) {
    m_loggedIn = false;
    m_initialized = false;
    m_name = nullptr;
    m_appCode = 0;
    unk60 = nullptr;
    unk64 = nullptr;
    OSInitMutex(&m_mutex);
    OSInitMutex(&NteDWCMutex);
    unk2C_b1 = false;
}

void nteDWC::notifyDoneSOProc(s32 p1, s32 p2) {
    switch (p2) {
        case 0:
            switch (p1) {
                case 0:
                    if (!DWC_Init(unk6C, m_name, m_appCode, AllocEx, FreeEx)) {
                        m_initialized = true;
                    }
                    break;
                case 1:
                    m_initialized = false;
                    break;
                default:
                    break;
            }
            break;
        case 0x80000000:
            break;
        default:
            showError(p2);
            s32 err = -NETGetStartupErrorCode(p2);
            if (unk60) {
                unk60->func0(err);
            }
            break;
    }
}

bool nteDWC::startupDWC() {
    if (m_initialized) {
        return true;
    }
    unk6C = 1;
    m_name = "smashbrosxwii";
    m_appCode = srGetAppInitialCode();
    return m_socketHandler.startup(this, 0x7530);
}

bool nteDWC::finishDWC() {
    if (m_initialized) {
        m_loggedIn = false;
        DWC_Shutdown();
    }
    return m_socketHandler.finish(this);
}

bool nteDWC::login(s32 p1, s32 p2, s32 p3, s32 p4) {
    if (!m_initialized) {
        return false;
    }
    if (DWC_GetState()) {
        return true;
    }
    DWC_InitFriendsMatch(0, p1, 0x2B1E, p3, p4, 0, 0, 0, 0);
    if (!DWC_LoginAsync(p2, 0, callbackLogin, this)) {
        return false;
    }
    m_loggedIn = true;
    return true;
}

bool nteDWC::logout() {
    if (!m_initialized) {
        return false;
    }
    if (!DWC_GetState()) {
        return true;
    }
    OSLockMutex(&m_mutex);
    m_loggedIn = false;
    DWC_ShutdownFriendsMatch();
    OSUnlockMutex(&m_mutex);
    return true;
}

bool nteDWC::isOnline() const {
    switch (DWC_GetState()) {
        case 3:
        case 4:
        case 5:
        case 6:
            return true;
        default:
            return false;
    }
}

void nteDWC::processDefault() {
    OSLockMutex(&m_mutex);
    switch (m_loggedIn) {
        case false:
            break;
        case true:
            DWC_ProcessFriendsMatch();
            s32 err2, err1;
            if (DWC_GetLastErrorEx(&err1, &err2)) {
                if (unk64) {
                    if (err1 < 0) {
                        err1 = -err1;
                    }
                    unk64->notifyDoneSOProc(err1, err2);
                }
                DWC_ClearError();
            }
            break;
        default:
            break;
    }
    OSUnlockMutex(&m_mutex);
}

s64 nteDWC::getTime() const {
    s64 ticks = 0;
    DWCDate date;
    DWCTime time;
    if (DWC_GetDateTime(&date, &time)) {
        OSCalendarTime cal;
        cal.sec = time.sec;
        cal.min = time.min;
        cal.hour = time.hour;
        cal.mday = date.mday;
        cal.month = date.month;
        cal.year = date.year;
        cal.wday = date.wday;
        cal.yday = date.yday;
        cal.msec = 0;
        cal.usec = 0;
        ticks = OSCalendarTimeToTicks(&cal);
    }
    return ticks;
}

void nteDWC::callbackLogin(s32 p1, s32 p2, void* p3) {
    (void)p2;
    nteDWC* dwc = static_cast<nteDWC*>(p3);
    if (p1) {
        dwc->m_loggedIn = false;
        s32 err1, err2;
        if (DWC_GetLastErrorEx(&err1, &err2)) {
            if (dwc->unk64) {
                if (err1 < 0) {
                    err1 = -err1;
                }
                dwc->unk64->notifyDoneSOProc(err1, err2);
            }
            DWC_ClearError();
        }
    }
}

void* nteDWC::AllocEx(int heap, size_t size, int align) {
    (void)heap;
    if (!size) {
        return nullptr;
    }
    OSLockMutex(&NteDWCMutex);
    void* ptr = gfHeapManager::alloc(Heaps::Network, size, align);
    OSUnlockMutex(&NteDWCMutex);
    return ptr;
}

void nteDWC::FreeEx(int heap, void* ptr) {
    (void)heap;
    if (ptr) {
        OSLockMutex(&NteDWCMutex);
        gfHeapManager::free(ptr);
        OSUnlockMutex(&NteDWCMutex);
    }
}

nteDWC::~nteDWC() { }
