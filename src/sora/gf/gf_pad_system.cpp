#include <cstring>
#include <cmath>
#include <nw4r/math/math_arithmetic.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_homemenu.h>
#include <gf/gf_pad_queue.h>
#include <gf/gf_pad_status.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_rumble.h>
#include <revolution/OS/OSAlarm.h>
#include <revolution/OS/OSInterrupt.h>
#include <revolution/OS/OSThread.h>
#include <sr/sr_common.h>
#include <types.h>

// gfThread / gfPadReadThread are redefined locally here because the versions in
// BrawlHeaders do not provide the constructor used by gfPadSystem (priority 14, stack 0x1200).
class gfRunnable {
public:
    virtual void run() = 0;
};

class gfThread : public gfRunnable {
protected:
    u8 unk4[0x4];
    OSThread m_thread;
    u32 m_stackSize;
    void* m_stackLow;
    void* m_stackHi;
    const char* m_name;
    u32 m_priority;
    u8 unk334[0x4];
    u16 m_flags;
    gfRunnable* m_startRoutine;

public:
    gfThread(u32 priority, u32 stackSize, Heaps::HeapType heap) {
        createThread(this, priority, stackSize, heap);
    }
    virtual void run() { }
    ~gfThread();
    void createThread(gfRunnable* startRoutine, u32 priority, u32 stackSize, Heaps::HeapType heap);
    static void* startThread(void* arg);
};

class gfPadReadThread : public gfThread {
    bool unk340;

public:
    gfPadReadThread() : gfThread(0xE, 0x1200, Heaps::SystemFW) {
        unk340 = true;
    }
    virtual void run();
    void resume() {
        OSResumeThread(&m_thread);
    }
};

struct PadStatusRaw {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 err;
    u8 pad;
};

struct KpadStatusRaw {
    u32 hold;
    u32 trig;
    u32 release;
    f32 accX;
    f32 accY;
    f32 accZ;
    f32 accValue;
    f32 accSpeed;
    f32 posX;
    f32 posY;
    f32 velX;
    f32 velY;
    f32 speed;
    f32 horiX;
    f32 horiY;
    f32 horiVelX;
    f32 horiVelY;
    f32 horiSpeed;
    f32 dist;
    f32 distVel;
    f32 distSpeed;
    f32 accVertX;
    f32 accVertY;
    u8 devType;
    s8 wpadErr;
    s8 dpdValid;
    u8 dataFormat;
    union {
        struct {
            f32 stickX;
            f32 stickY;
            f32 accX;
            f32 accY;
            f32 accZ;
            f32 accValue;
            f32 accSpeed;
        } fs;
        struct {
            u32 hold;
            u32 trig;
            u32 release;
            f32 lstickX;
            f32 lstickY;
            f32 rstickX;
            f32 rstickY;
            f32 ltrigger;
            f32 rtrigger;
        } cl;
    };
};

class Network;
extern Network g_Network;


extern "C" {
void* fn_8002C78C(gfRumble*);
void* fn_8002BAB0(void*);
void fn_8002BB1C(gfRumble*, gfPadSystem*, int);
void fn_801E74C8(int);
void fn_80215E68();
void fn_80218D64();
void fn_80218D60(void* (*)(u32), u8 (*)(void*));
void fn_80227E54();
void fn_8022555C(int, int);
void fn_80225570(int, float, float);
int fn_8021C938(int);
void fn_8021C9AC(int, int, int);
void fn_8021A118(int, void (*)(int));
void fn_80215FC4(PadStatusRaw*);
void fn_80215C54(u32);
int fn_80227728(int, KpadStatusRaw*, int);
double fn_80400B44(float, float);
void fn_802162A4(int, int);
void fn_8021A558(int, int);
void fn_80228138(int);
void fn_80228154(int);
void fn_80146B80(Network*);
void fn_80219F60(int);
int fn_80218D54();
void fn_80218D5C(void (*)(int));
int fn_80218D58();
int fn_802250C8(int, int, int, int, void (*)(int, int));
int fn_80224D18(int, int, int, int, void (*)(int, int));
}

gfPadSystem* g_gfPadSystem;

// WPAD allocator callbacks
extern "C" void* fn_80028808(u32 size) {
    return gfHeapManager::alloc(Heaps::WiiPad, size, 0x20);
}

extern "C" u8 fn_80028818(void* ptr) {
    gfHeapManager::free(ptr);
    return 1;
}

// gfPadStatus::init() split in three parts; the Wii pad code interleaves other work in between.
static inline void padInitBegin(gfPadStatus* p) {
    p->m_buttonsPressedThisFrame2.bits = 0;
}

static inline void padInitBody(gfPadStatus* p) {
    p->m_buttonsReleasedThisFrame.bits = 0;
    p->m_buttonsPressedThisFrame.bits = 0;
    p->m_buttonsHeld.bits = 0;
    p->m_buttonsCurrentFrame2.bits = 0;
    p->m_buttonsCurrentFrame.bits = 0;
    p->m_stickY = 0;
    p->m_stickX = 0;
    p->m_subStickY = 0;
    p->m_subStickX = 0;
    p->m_rTriggerAnalog = 0;
    p->m_lTriggerAnalog = 0;
    p->_0x37 = 0;
    p->_0x36 = 0;
    p->_0x24 = 0.0f;
    p->_0x20 = 0.0f;
    p->_0x1c = 0.0f;
    p->_0x18 = 0.0f;
    p->_0x2c = 0.0f;
    p->_0x28 = 0.0f;
}

static inline void padInitError(gfPadStatus* p) {
    p->m_error = gfPadError::NO_CONTROLLER;
}

static inline void padInitType(gfPadStatus* p) {
    p->m_controllerType = gfPadType::GCC;
}

static inline void padInit(gfPadStatus* p) {
    padInitBegin(p);
    padInitBody(p);
    padInitError(p);
    padInitType(p);
}

void gfPadStatus::init() {
    padInit(this);
}

#define CLAMP_STICK(f)                             if (f >= 0) {                                      int t = f - 15;                                t = t > 0 ? t : 0;                             f = t < 127 ? t : 127;                     } else {                                           int t = f + 15;                                t = t > -128 ? t : -128;                       f = t < 0 ? t : 0;                         }

void gfPadStatus::clamp() {
    CLAMP_STICK(m_stickX)
    CLAMP_STICK(m_stickY)
    CLAMP_STICK(m_subStickX)
    CLAMP_STICK(m_subStickY)
}

void gfPadStatus::update(gfPadStatus* src) {
    float srcA = src->_0x18;
    u32 cur = src->m_buttonsCurrentFrame2.bits;
    float oldA = _0x18;
    u32 prev = m_buttonsCurrentFrame2.bits;
    char u = src->_0x37;
    char r = src->m_rTriggerAnalog;
    char l = src->m_lTriggerAnalog;
    char cy = src->m_subStickY;
    char cx = src->m_subStickX;
    char sy = src->m_stickY;
    char sx = src->m_stickX;
    m_buttonsHeld.bits = prev;
    m_buttonsCurrentFrame.bits = cur;
    m_buttonsCurrentFrame2.bits = cur;
    m_buttonsPressedThisFrame.bits = cur & (cur ^ prev);
    m_buttonsReleasedThisFrame.bits = prev & (cur ^ prev);
    m_buttonsPressedThisFrame2.bits = cur & (cur ^ prev);
    m_stickX = sx;
    m_stickY = sy;
    m_subStickX = cx;
    m_subStickY = cy;
    m_lTriggerAnalog = l;
    m_rTriggerAnalog = r;
    _0x36 = u;
    if (oldA * srcA < 0.0f) {
        _0x18 = oldA + 0.2f * (srcA - oldA);
    } else {
        _0x18 = srcA;
    }
    if (_0x1c * src->_0x1c < 0.0f) {
        _0x1c = _0x1c + 0.2f * (src->_0x1c - _0x1c);
    } else {
        _0x1c = src->_0x1c;
    }
    _0x20 = src->_0x20;
    _0x24 = src->_0x24;
    _0x28 = src->_0x28;
    _0x2c = src->_0x2c;
    m_error = src->m_error;
    m_controllerType = src->m_controllerType;
}

struct HomeMenuView {
    char _0x0[0x9C];
    int m_0x9c;
    char _0xa0[0x11];
    u8 m_b1_0 : 3;
    u8 m_flag : 1;
    u8 m_b1_4 : 4;
};

static inline bool isHomeMenuActive(HomeMenuView* menu) {
    return menu->m_flag || menu->m_0x9c != 0;
}

typedef void (*ConnectCallback)(int);
static ConnectCallback s_connectCallback;
static u16 s_wiiRetryTimer[4];
static u8 s_wiiRetryCount[4];

extern "C" void fn_80028B74(int chan) {
    if (s_connectCallback) {
        s_connectCallback(chan);
    }
    HomeMenuView* menu = (HomeMenuView*)g_gfHomeMenu;
    if (menu && isHomeMenuActive(menu)) {
        fn_80228154(chan);
    } else {
        fn_80228138(0);
        fn_80228138(1);
        fn_80228138(2);
        fn_80228138(3);
    }
}

void gfPadSystem::_alarmCallback(OSAlarm* alarm, OSContext* ctx) {
    g_gfPadSystem->m_frameCounter++;
    gfPadReadThread* thread = g_gfPadSystem->m_controllerThread;
    if (thread) {
        thread->resume();
    }
    if (&g_Network) {
        fn_80146B80(&g_Network);
    }
}

gfPadSystem* gfPadSystem::create() {
    if (g_gfPadSystem == nullptr) {
        g_gfPadSystem = new (Heaps::SystemFW) gfPadSystem;
    }
    return g_gfPadSystem;
}

gfPadSystem::gfPadSystem() {
    m_frameCounter = 0;
    m_flags34.f7 = 0;
    m_flags34.f6 = 0;
    m_flags34.f5 = 0;
    m_flags34.f4 = 0;
    m_flags34.f3 = 1;
    m_flags34.f2 = 0;
    m_flags34.f1 = 0;
    m_flags34.f0 = 0;
    m_flags35.f7 = 0;
    m_flags35.f6 = 1;
    m_debugPadMask = 0xFFFF;
    m_sysExcludedPadMask = 0;
    m_gamePadMask = 0xFFFF;
    m_0x3e = 0;
    m_padQueue = nullptr;
    m_0x944 = 0;
    m_repeatDelay = 60;
    m_repeatBits = 3;
    m_motorMask = 0;
    m_0xb4c[0] = 0;
    m_0xb4c[1] = 0;
    m_gfRumble = nullptr;
    m_gameData = 0;
    m_0xb70 = 0;

    fn_801E74C8(0xB);
    fn_80215E68();
    fn_80218D64();
    fn_80218D60(fn_80028808, fn_80028818);
    fn_80227E54();
    fn_8022555C(0, 0x7F);
    for (int i = 0; i <= 3; i++) {
        fn_80225570(i, 0.1f, 0.85f);
    }
    if (fn_8021C938(0)) {
        fn_8021C9AC(0, 0, 0);
    }
    if (fn_8021C938(1)) {
        fn_8021C9AC(1, 0, 0);
    }
    if (fn_8021C938(2)) {
        fn_8021C9AC(2, 0, 0);
    }
    if (fn_8021C938(3)) {
        fn_8021C9AC(3, 0, 0);
    }
    for (int i = 0; i < 4; i++) {
        fn_8021A118(0, fn_80028B74);
    }

    padInit(&m_sysPadMerged);
    padInit(&m_debugPadMerged);
    padInit(&m_gamePadMerged);
    for (int i = 0; i < 4; i++) {
        padInit(&m_sysPads[i]);
        padInit(&m_gamePads[i]);
    }
    for (int i = 4; i < 8; i++) {
        padInit(&m_sysPads[i]);
        m_sysPads[i].m_controllerType = gfPadType::WIIMOTE;
        padInit(&m_gamePads[i]);
        m_gamePads[i].m_controllerType = gfPadType::WIIMOTE;
    }
    for (int i = 0; i < 8; i++) {
        padInit(&m_debugPads[i]);
    }
    for (int i = 0; i < 8; i++) {
        padInit(&m_gamePads[i]);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 32; j++) {
            m_repeatCount[i][j] = 0;
            m_unkCount[i][j] = 0;
        }
    }
    m_padQueue = new (Heaps::SystemFW) gfPadStatusQueue;
    m_controllerThread = new (Heaps::SystemFW) gfPadReadThread;
    g_gfPadSystem = this;
    m_controllerThread->resume();
}

void gfPadSystem::createRumbleSystem() {
    if (m_gfRumble == nullptr) {
        void* mem = operator new(0x100, Heaps::SystemFW);
        if (mem) {
            mem = fn_8002BAB0(mem);
        }
        m_gfRumble = (gfRumble*)mem;
        fn_8002BB1C(m_gfRumble, this, 3);
    }
}

void gfPadSystem::consumeFrameCounter(int frames) {
    BOOL intr = OSDisableInterrupts();
    m_frameCounter -= frames;
    OSRestoreInterrupts(intr);
}

void gfPadSystem::clearPadQueue() {
    if (m_padQueue) {
        m_padQueue->clear();
    }
}

void gfPadSystem::updateLow() {
    BOOL intr = OSDisableInterrupts();
    gfPadStatus* pads = m_sysPads;
    updateLowGC(pads);
    HomeMenuView* menu = (HomeMenuView*)g_gfHomeMenu;
    if (menu && isHomeMenuActive(menu)) {
        for (u32 i = 0; i < 8; i++) {
            gfPadError::PadError err = pads[i].m_error;
            gfPadType::PadType type = pads[i].m_controllerType;
            memset(&pads[i], 0, sizeof(gfPadStatus));
            pads[i].m_error = err;
            pads[i].m_controllerType = type;
        }
    } else {
        updateLowWii(pads + 4);
    }
    m_padQueue->push(pads);
    memcpy(m_sysPads, pads, sizeof(m_sysPads));
    OSRestoreInterrupts(intr);
}

void gfPadSystem::updateLowGC(gfPadStatus* dest) {
    PadStatusRaw status[4];
    fn_80215FC4(status);
    u32 mask = m_0x944;
    u32 resetMask = 0;
    for (int i = 0; i < 4; i++) {
        switch (status[i].err) {
        case 0:
        case -3:
            mask |= 0x80000000 >> i;
            break;
        case -1:
            resetMask |= 0x80000000 >> i;
            break;
        }
    }
    m_0x944 = mask;
    if (resetMask) {
        fn_80215C54(resetMask);
    }
    PadStatusRaw* st = status;
    for (int i = 0; i < 4; i++) {
        padInit(dest);
        if (st->err == 0) {
            dest->m_buttonsCurrentFrame.bits = st->button;
            dest->m_buttonsCurrentFrame2.bits = st->button;
            dest->m_stickX = st->stickX;
            dest->m_stickY = st->stickY;
            dest->m_subStickX = st->substickX;
            dest->m_subStickY = st->substickY;
            dest->m_lTriggerAnalog = st->triggerL;
            dest->m_rTriggerAnalog = st->triggerR;
            dest->_0x36 = st->analogB;
            dest->m_error = (gfPadError::PadError)st->err;
            dest->m_controllerType = gfPadType::GCC;
        } else {
            dest->m_error = (gfPadError::PadError)st->err;
            dest->m_controllerType = gfPadType::GCC;
        }
        dest++;
        st++;
    }
}

struct PadMapEntry {
    u32 out;
    u16 in;
    u16 pad;
};

// 14 entries (wiimote), 15 entries (nunchuk), 15 entries (classic), 3 unused
static PadMapEntry s_padMap[47] = {
    { 0x00000001, 0x0008, 0 }, { 0x00000002, 0x0004, 0 }, { 0x00000004, 0x0001, 0 }, { 0x00000008, 0x0002, 0 },
    { 0x00000100, 0x0100, 0 }, { 0x00000200, 0x0200, 0 }, { 0x00010000, 0x0200, 0 }, { 0x00020000, 0x0100, 0 },
    { 0x00000040, 0x0400, 0 }, { 0x00000010, 0x2000, 0 }, { 0x00001000, 0x0010, 0 }, { 0x00080000, 0x1000, 0 },
    { 0x00200000, 0x0800, 0 }, { 0x00400000, 0x0400, 0 },
    { 0x00000001, 0x0001, 0 }, { 0x00000002, 0x0002, 0 }, { 0x00000004, 0x0004, 0 }, { 0x00000008, 0x0008, 0 },
    { 0x00000100, 0x0800, 0 }, { 0x00000200, 0x0400, 0 }, { 0x00040000, 0x4000, 0 }, { 0x00000010, 0x2000, 0 },
    { 0x00000400, 0x4000, 0 }, { 0x00001000, 0x0010, 0 }, { 0x00080000, 0x1000, 0 }, { 0x00010000, 0x0200, 0 },
    { 0x00020000, 0x0100, 0 }, { 0x00200000, 0x0800, 0 }, { 0x00400000, 0x0400, 0 },
    { 0x00000001, 0x0002, 0 }, { 0x00000002, 0x8000, 0 }, { 0x00000004, 0x4000, 0 }, { 0x00000008, 0x0001, 0 },
    { 0x00000100, 0x0010, 0 }, { 0x00000200, 0x0040, 0 }, { 0x00000040, 0x2000, 0 }, { 0x00000020, 0x0200, 0 },
    { 0x00000400, 0x0008, 0 }, { 0x00000800, 0x0020, 0 }, { 0x00008000, 0x0004, 0 }, { 0x00004000, 0x0080, 0 },
    { 0x00001000, 0x0400, 0 }, { 0x00100000, 0x0400, 0 }, { 0x00080000, 0x1000, 0 },
    { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
};
static PadMapEntry s_nunchukZ = { 0x00800000, 0x0010, 0 };
static float s_stickPow = 1.2f;
static float s_stickScale = 100.0f;

static inline u32 mapButtons(u32 buttons, PadMapEntry* table, int count) {
    u32 out = 0;
    PadMapEntry* p = table;
    for (int i = 0; i < count; i++) {
        if (buttons & p->in) {
            out |= p->out;
        }
        p++;
    }
    return out;
}

void gfPadSystem::updateLowWii(gfPadStatus* dest) {
    PadMapEntry* map = s_padMap;
    PadMapEntry* zEntry = &s_nunchukZ;
    KpadStatusRaw* status = (KpadStatusRaw*)__alloca(sizeof(KpadStatusRaw) * 8);
    for (u16 i = 0; i < 4; i++) {
        gfPadStatus* pad = &dest[i];
        int n = fn_80227728(i, status, 8);
        u16* timer = &s_wiiRetryTimer[i];
        u8* count = &s_wiiRetryCount[i];
        if (n <= 0) {
            padInitBegin(pad);
            s8 retry = *count;
            padInitBody(pad);
            padInitError(pad);
            if (retry > 0) {
                pad->m_error = gfPadError::NONE;
                *count = retry - 1;
            } else {
                pad->m_controllerType = gfPadType::WIIMOTE;
                pad->m_error = gfPadError::NO_CONTROLLER;
            }
            continue;
        }
        s8 err = status[0].wpadErr;
        *count = 5;
        u8 devType = status[0].devType;
        if (err != 0) {
            padInitBegin(pad);
            padInitBody(pad);
            padInitError(pad);
            *timer = 30;
            padInitType(pad);
            if (err == -1) {
                pad->m_error = gfPadError::NO_CONTROLLER;
            } else {
                pad->m_error = gfPadError::NONE;
            }
            pad->m_controllerType = gfPadType::WIIMOTE;
            continue;
        }
        u16 t = *timer;
        pad->m_error = gfPadError::NONE;
        if (t != 0) {
            padInitBegin(pad);
            padInitBody(pad);
            pad->m_controllerType = gfPadType::WIIMOTE;
            *timer = t - 1;
            pad->m_error = gfPadError::NONE;
            continue;
        }
        if (status[0].trig == 0x8000 || status[0].cl.trig == 0x800) {
            m_flags34.f2 = 1;
        }
        switch (devType) {
        case 0:
        case 0xFB: {
            u32 buttons = mapButtons(status[0].hold, &map[0], 14);
            u32 prev = pad->m_buttonsCurrentFrame2.bits;
            u32 diff = buttons ^ prev;
            pad->m_buttonsHeld.bits = prev;
            pad->m_buttonsCurrentFrame.bits = buttons;
            pad->m_buttonsCurrentFrame2.bits = buttons;
            pad->m_buttonsPressedThisFrame.bits = buttons & diff;
            pad->m_buttonsReleasedThisFrame.bits = prev & diff;
            pad->m_buttonsPressedThisFrame2.bits = buttons & diff;
            pad->m_stickX = 0;
            pad->m_stickY = 0;
            pad->m_subStickX = 0;
            pad->m_subStickY = 0;
            pad->m_lTriggerAnalog = 0;
            pad->m_rTriggerAnalog = 0;
            pad->_0x18 = status[0].accX;
            pad->_0x1c = status[0].accY;
            pad->_0x20 = status[0].accValue;
            pad->_0x24 = status[0].accSpeed;
            pad->_0x28 = status[0].accVertX;
            pad->_0x2c = status[0].accVertY;
            pad->m_controllerType = gfPadType::WIIMOTE;
            break;
        }
        case 1: {
            u32 buttons = mapButtons(status[0].hold, &map[14], 15);
            u32 prev = pad->m_buttonsCurrentFrame2.bits;
            u32 diff = buttons ^ prev;
            pad->m_buttonsHeld.bits = prev;
            pad->m_buttonsCurrentFrame.bits = buttons;
            pad->m_buttonsCurrentFrame2.bits = buttons;
            pad->m_buttonsPressedThisFrame.bits = buttons & diff;
            pad->m_buttonsReleasedThisFrame.bits = prev & diff;
            pad->m_buttonsPressedThisFrame2.bits = buttons & diff;
            float v = 127.0f * status[0].fs.stickX / s_stickScale;
            float sx = 1.0f;
            if (v < 0.0f) {
                sx = -1.0f;
            }
            v = nw4r::math::FSelect(v - -1.0f, v, -1.0f);
            v = nw4r::math::FSelect(v - 1.0f, 1.0f, v);
            sx = sx * (float)fn_80400B44((float)fabs(v), s_stickPow);
            pad->m_stickX = (int)(sx * s_stickScale);
            v = 127.0f * status[0].fs.stickY / s_stickScale;
            float sy = 1.0f;
            if (v < 0.0f) {
                sy = -1.0f;
            }
            v = nw4r::math::FSelect(v - -1.0f, v, -1.0f);
            v = nw4r::math::FSelect(v - 1.0f, 1.0f, v);
            sy = sy * (float)fn_80400B44((float)fabs(v), s_stickPow);
            pad->m_stickY = (int)(sy * s_stickScale);
            pad->m_subStickX = 0;
            pad->m_subStickY = 0;
            pad->_0x18 = status[0].accX;
            pad->_0x1c = status[0].accY;
            pad->_0x20 = status[0].accValue;
            pad->_0x24 = status[0].accSpeed;
            pad->_0x28 = status[0].accVertX;
            pad->_0x2c = status[0].accVertY;
            pad->m_controllerType = gfPadType::NUNCHUK;
            break;
        }
        case 2: {
            u32 buttons = 0;
            if (status[0].hold & zEntry->in) {
                buttons = zEntry->out;
            }
            PadMapEntry* p = &map[29];
            for (int j = 0; j < 15; j++) {
                if (status[0].cl.hold & p->in) {
                    buttons |= p->out;
                }
                p++;
            }
            if (buttons & 0xC000) {
                buttons |= 0x10;
            }
            u32 prev = pad->m_buttonsCurrentFrame2.bits;
            u32 diff = buttons ^ prev;
            pad->m_buttonsHeld.bits = prev;
            pad->m_buttonsCurrentFrame.bits = buttons;
            pad->m_buttonsCurrentFrame2.bits = buttons;
            pad->m_buttonsPressedThisFrame.bits = buttons & diff;
            pad->m_buttonsReleasedThisFrame.bits = prev & diff;
            pad->m_buttonsPressedThisFrame2.bits = buttons & diff;
            pad->m_stickX = (int)(status[0].cl.lstickX * 100.0f);
            pad->m_stickY = (int)(status[0].cl.lstickY * 100.0f);
            pad->m_subStickX = (int)(status[0].cl.rstickX * 100.0f);
            pad->m_subStickY = (int)(status[0].cl.rstickY * 100.0f);
            pad->m_lTriggerAnalog = (int)(255.0f * status[0].cl.ltrigger);
            pad->m_rTriggerAnalog = (int)(255.0f * status[0].cl.rtrigger);
            pad->_0x18 = status[0].accX;
            pad->_0x1c = status[0].accY;
            pad->_0x20 = status[0].accValue;
            pad->_0x24 = status[0].accSpeed;
            pad->_0x28 = status[0].accVertX;
            pad->_0x2c = status[0].accVertY;
            pad->m_controllerType = gfPadType::WII_CLASSIC;
            break;
        }
        case 0xFC:
        case 0xFD:
        case 0xFF:
            pad->m_error = gfPadError::NO_CONTROLLER;
            break;
        }
    }
}

static inline u32 convButtons(u32 b) {
    u32 r = b & ~0xF00;
    r |= (-((b >> 8) & 1) & 0x400);
    r |= (-((b >> 9) & 1) & 0x100);
    r |= (-((b >> 10) & 1) & 0x800);
    r |= (-((b >> 11) & 1) & 0x200);
    return r;
}

void gfPadStatus::convSysStatusToMenuStatus(gfPadStatus* dest) {
    if (m_controllerType == gfPadType::WII_CLASSIC) {
        *dest = *this;
        u32 cur = convButtons(m_buttonsCurrentFrame.bits);
        u32 held = convButtons(m_buttonsHeld.bits);
        u32 pressed = convButtons(m_buttonsPressedThisFrame.bits);
        u32 released = convButtons(m_buttonsReleasedThisFrame.bits);
        u32 pressed2 = convButtons(m_buttonsPressedThisFrame2.bits);
        dest->m_buttonsCurrentFrame.bits = cur;
        dest->m_buttonsCurrentFrame2.bits = cur;
        dest->m_buttonsHeld.bits = held;
        dest->m_buttonsPressedThisFrame.bits = pressed;
        dest->m_buttonsReleasedThisFrame.bits = released;
        dest->m_buttonsPressedThisFrame2.bits = pressed2;
    } else {
        *dest = *this;
    }
}

void gfPadSystem::updateSystem() {
    m_flags34.f1 = m_flags34.f2;
    m_flags34.f2 = 0;
    BOOL intr = OSDisableInterrupts();
    gfPadStatus* sys = m_sysPads;
    gfPadStatus* dbg = m_debugPads;
    for (u32 i = 0; i < 8; i++) {
        dbg->update(sys);
        dbg++;
        sys++;
    }
    OSRestoreInterrupts(intr);
    for (u32 i = 0; i < 8; i++) {
        m_debugPads[i].convSysStatusToMenuStatus(&m_menuPads[i]);
    }

    int t = m_repeatDelay > 1 ? m_repeatDelay : 1;
    m_repeatDelay = (u8)t < 100 ? t : 100;
    t = m_repeatBits > 1 ? m_repeatBits : 1;
    m_repeatBits = (u8)t < 7 ? t : 7;
    for (int i = 0; i < 8; i++) {
        gfPadStatus* pad = &m_debugPads[i];
        u8* row = m_repeatCount[i];
        u8 mask = (1 << m_repeatBits) - 1;
        for (int j = 0; j < 32; j++) {
            if (pad->m_buttonsCurrentFrame2.bits & (1 << j)) {
                row[j]++;
            } else {
                row[j] = 0;
            }
            if (row[j] >= m_repeatDelay) {
                int diff = row[j] - m_repeatDelay;
                if (mask == (mask & diff)) {
                    pad->m_buttonsPressedThisFrame2.bits |= (1 << j);
                }
                if (diff >= 0x80) {
                    row[j] -= 0x80;
                }
            }
        }
    }
    merge(m_debugPads, 8, (u16)~m_sysExcludedPadMask, &m_sysPadMerged);
    merge(m_debugPads, 8, m_debugPadMask, &m_debugPadMerged);
    merge(m_menuPads, 8, 0xFF, &m_menuPadMerged);
    for (int i = 0; i < 8; i++) {
        if (m_padMotorMasks[i] != 0 && m_padMotorMasks[i] != 0xFFFF) {
            m_padMotorMasks[i]--;
            if (m_padMotorMasks[i] == 0 && m_flags35.f6) {
                if (i < 4) {
                    fn_802162A4(i, 0);
                } else {
                    fn_8021A558(i - 4, 0);
                }
                m_padMotorMasks[i] = 0;
            }
        }
    }
    m_unkCounter = 0;
}

void gfPadSystem::updateGame() {
    if (m_gfRumble) {
        fn_8002C78C(m_gfRumble);
    }
    gfPadStatus blank;
    padInit(&blank);
    if (m_flags34.f3) {
        gfPadStatus queued[8];
        if (m_padQueue->pop(queued)) {
            for (u32 i = 0; i < 8; i++) {
                if ((1 << i) & m_0x3e) {
                    m_gamePads[i].update(&blank);
                } else {
                    m_gamePads[i].update(&queued[i]);
                }
            }
            m_flags34.f7 = 1;
        } else {
            for (u32 i = 0; i < 8; i++) {
                if ((1 << i) & m_0x3e) {
                    m_gamePads[i].update(&blank);
                } else {
                    m_gamePads[i].m_buttonsReleasedThisFrame.bits = 0;
                    m_gamePads[i].m_buttonsPressedThisFrame.bits = 0;
                    m_gamePads[i].m_buttonsHeld.bits = m_gamePads[i].m_buttonsCurrentFrame2.bits;
                }
            }
            m_flags34.f7 = 1;
        }
    } else {
        for (u32 i = 0; i < 8; i++) {
            if ((1 << i) & m_0x3e) {
                m_gamePads[i].update(&blank);
            } else {
                m_gamePads[i].update(&m_sysPads[i]);
            }
        }
        m_flags34.f7 = 1;
        if (m_unkCounter != 0) {
            m_flags34.f7 = 0;
        }
    }
    if (m_flags34.f0) {
        for (int i = 0; i < 8; i++) {
            m_gamePads[i].m_buttonsCurrentFrame.bits &= ~0x10;
            m_gamePads[i].m_buttonsCurrentFrame2.bits &= ~0x10;
        }
    }
    merge(m_gamePads, 8, m_gamePadMask, &m_gamePadMerged);
    if (m_0x3e & 0x100) {
        m_gamePadMerged = blank;
    }
    m_unkCounter++;
}

void gfPadSystem::maskMotor(u16 mask) {
    u32 m = m_motorMask & (u8)mask;
    if (m) {
        for (int i = 0; i < 8; i++) {
            if ((m & (1 << i)) && m_flags35.f6) {
                if (i < 4) {
                    fn_802162A4(i, 0);
                } else {
                    fn_8021A558(i - 4, 0);
                }
                m_padMotorMasks[i] = 0;
            }
        }
    }
    m_motorMask = mask & 0xFF;
}

void gfPadSystem::startMotor(int padNum) {
    if (m_flags35.f6) {
        if (!(m_motorMask & (1 << padNum))) {
            if (padNum < 4) {
                fn_802162A4(padNum, 1);
            } else if (m_gamePads[padNum].m_controllerType != gfPadType::WII_CLASSIC) {
                fn_8021A558(padNum - 4, 1);
            }
            m_padMotorMasks[padNum] = 0xFFFF;
        }
    }
}

void gfPadSystem::startMotor(int padNum, u16 mask) {
    if (m_flags35.f6) {
        if (!(m_motorMask & (1 << padNum))) {
            if (padNum < 4) {
                fn_802162A4(padNum, 1);
            } else if (m_gamePads[padNum].m_controllerType != gfPadType::WII_CLASSIC) {
                fn_8021A558(padNum - 4, 1);
            }
            m_padMotorMasks[padNum] = mask;
        }
    }
}

void gfPadSystem::stopMotor(int padNum) {
    if (m_flags35.f6) {
        if (padNum < 4) {
            fn_802162A4(padNum, 0);
        } else {
            fn_8021A558(padNum - 4, 0);
        }
        m_padMotorMasks[padNum] = 0;
    }
}

void gfPadSystem::stopMotorH(int padNum) {
    if (m_flags35.f6) {
        if (padNum < 4) {
            fn_802162A4(padNum, 2);
        } else {
            fn_8021A558(padNum - 4, 0);
        }
        m_padMotorMasks[padNum] = 0;
    }
}

void gfPadSystem::stopMotorAllForce() {
    for (int i = 0; i < 4; i++) {
        fn_802162A4(i, 0);
    }
    for (int i = 0; i < 4; i++) {
        fn_8021A558(i, 0);
    }
}

void gfPadSystem::pauseNotify() {
    for (int i = 0; i < 4; i++) {
        fn_802162A4(i, 0);
    }
    for (int i = 0; i < 4; i++) {
        fn_8021A558(i, 0);
    }
}

struct PadQueueView {
    u16 front;
    u16 back;
};

u32 gfPadSystem::getGamePadQueueCount() {
    PadQueueView* q = (PadQueueView*)m_padQueue;
    s32 diff = q->back - q->front;
    if (diff < 0) {
        diff += 4;
    }
    return (u16)diff;
}

void gfPadSystem::setConnectCallback(int cb) {
    s_connectCallback = (ConnectCallback)cb;
}

int gfPadSystem::getGamePadStatus(int padNum, gfPadStatus* dest) {
    if (padNum == GF_PAD_SYSTEM_GET_ALL_PADS) {
        *dest = m_gamePadMerged;
    } else if ((1 << padNum) & m_sysExcludedPadMask) {
        padInit(dest);
        dest->m_error = gfPadError::NONE;
    } else {
        *dest = m_gamePads[padNum];
    }
    return 1;
}

int gfPadSystem::getSysPadStatus(int padNum, gfPadStatus* dest) {
    if (padNum == GF_PAD_SYSTEM_GET_ALL_PADS) {
        *dest = m_sysPadMerged;
    } else if ((1 << padNum) & m_sysExcludedPadMask) {
        padInit(dest);
    } else {
        *dest = m_debugPads[padNum];
    }
    return 1;
}

int gfPadSystem::getDebugPadStatus(int padNum, gfPadStatus* dest) {
    if (padNum == GF_PAD_SYSTEM_GET_ALL_PADS) {
        *dest = m_debugPadMerged;
    } else if ((1 << padNum) & m_debugPadMask) {
        *dest = m_debugPads[padNum];
    } else {
        padInit(dest);
    }
    return 1;
}

static inline s8 absS8(s8 v) {
    return v < 0 ? -v : v;
}

void gfPadSystem::merge(gfPadStatus* src, int numPads, u32 mask, gfPadStatus* dest) {
    u8 count = 0;
    u32 cur = 0;
    u32 pressed = 0;
    u32 released = 0;
    u32 held = 0;
    u32 repeat = 0;
    u8 stickX = 0;
    u8 stickY = 0;
    u8 subX = 0;
    u8 subY = 0;
    u8 lTrig = 0;
    u8 rTrig = 0;
    u8 b36 = 0;
    u8 b37 = 0;
    for (u32 i = 0; i < numPads; src++, i++) {
        if (((mask >> i) & 1) && src->m_error == gfPadError::NONE) {
            cur |= src->m_buttonsCurrentFrame2.bits;
            pressed |= src->m_buttonsPressedThisFrame.bits;
            released |= src->m_buttonsReleasedThisFrame.bits;
            held |= src->m_buttonsHeld.bits;
            repeat |= src->m_buttonsPressedThisFrame2.bits;
            u8 a1 = src->m_stickX;
            if (absS8(stickX) < absS8(a1)) {
                stickX = a1;
            }
            u8 a2 = src->m_stickY;
            if (absS8(stickY) < absS8(a2)) {
                stickY = a2;
            }
            u8 a3 = src->m_subStickX;
            if (absS8(subX) < absS8(a3)) {
                subX = a3;
            }
            u8 a4 = src->m_subStickY;
            if (absS8(subY) < absS8(a4)) {
                subY = a4;
            }
            u8 t = src->m_lTriggerAnalog;
            lTrig = lTrig > t ? lTrig : t;
            t = src->m_rTriggerAnalog;
            rTrig = rTrig > t ? rTrig : t;
            t = src->_0x36;
            b36 = b36 > t ? b36 : t;
            t = src->_0x37;
            b37 = b37 > t ? b37 : t;
            count++;
        }
    }
    dest->m_buttonsCurrentFrame2.bits = cur;
    dest->m_buttonsCurrentFrame.bits = cur;
    dest->m_buttonsHeld.bits = held;
    dest->m_buttonsPressedThisFrame.bits = pressed;
    dest->m_buttonsReleasedThisFrame.bits = released;
    dest->m_buttonsPressedThisFrame2.bits = repeat;
    dest->m_stickX = stickX;
    dest->m_stickY = stickY;
    dest->m_subStickX = subX;
    dest->m_subStickY = subY;
    dest->m_lTriggerAnalog = lTrig;
    dest->m_rTriggerAnalog = rTrig;
    dest->_0x36 = b36;
    dest->_0x37 = b37;
    if (count) {
        dest->m_error = gfPadError::NONE;
    } else {
        dest->m_error = gfPadError::NOT_READY;
    }
}

void gfPadSystem::merge(gfPadStatus* src, int numPads, gfPadStatus* dest) {
    merge(src, numPads, 0xFFFF, dest);
}

void gfPadSystem::disconectWiiControler() {
    int j = 0;
    for (u32 i = 4; i < 8; i++) {
        if (m_debugPads[i].m_error == gfPadError::NONE) {
            fn_80219F60(j);
        }
        j++;
    }
}

void gfPadSystem::wpadSimpleSyncCallback(int result) {
    if (result == 1) {
        g_gfPadSystem->m_flags34.f6 = 1;
    }
}

extern "C" bool fn_8002B504() {
    return fn_80218D54() == 1;
}

bool gfPadSystem::startSimpleSync() {
    m_flags34.f6 = 0;
    fn_80218D5C(wpadSimpleSyncCallback);
    return fn_80218D58() == 1;
}

bool gfPadSystem::readGameDataRequest(int a, int b, int c, int d) {
    m_flags35.f7 = 0;
    return fn_802250C8(a, b, c, d, wpadGameDataCallback) == 0;
}

bool gfPadSystem::writeGameDataRequest(int a, int b, int c, int d) {
    m_flags35.f7 = 0;
    return fn_80224D18(a, b, c, d, wpadGameDataCallback) == 0;
}

void gfPadSystem::wpadGameDataCallback(int chan, int data) {
    gfPadSystem* sys = g_gfPadSystem;
    sys->m_gameData = data;
    sys->m_flags35.f7 = 1;
}

void gfPadSystem::clearPadEdgeRepert() {
    for (int i = 0; i < 8; i++) {
        m_sysPads[i].m_buttonsPressedThisFrame2.bits = 0;
        m_sysPads[i].m_buttonsReleasedThisFrame.bits = 0;
        m_sysPads[i].m_buttonsPressedThisFrame.bits = 0;
        m_debugPads[i].m_buttonsPressedThisFrame2.bits = 0;
        m_debugPads[i].m_buttonsReleasedThisFrame.bits = 0;
        m_debugPads[i].m_buttonsPressedThisFrame.bits = 0;
        m_menuPads[i].m_buttonsPressedThisFrame2.bits = 0;
        m_menuPads[i].m_buttonsReleasedThisFrame.bits = 0;
        m_menuPads[i].m_buttonsPressedThisFrame.bits = 0;
    }
    m_sysPadMerged.m_buttonsPressedThisFrame2.bits = 0;
    m_sysPadMerged.m_buttonsReleasedThisFrame.bits = 0;
    m_sysPadMerged.m_buttonsPressedThisFrame.bits = 0;
    m_menuPadMerged.m_buttonsPressedThisFrame2.bits = 0;
    m_menuPadMerged.m_buttonsReleasedThisFrame.bits = 0;
    m_menuPadMerged.m_buttonsPressedThisFrame.bits = 0;
    m_debugPadMerged.m_buttonsPressedThisFrame2.bits = 0;
    m_debugPadMerged.m_buttonsReleasedThisFrame.bits = 0;
    m_debugPadMerged.m_buttonsPressedThisFrame.bits = 0;
}
