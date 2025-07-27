#include <gf/gf_monitor.h>
#include <gf/gf_thread.h>
#include <revolution/GX/GXMisc.h>
#include <revolution/OS/OSHardware.h>
#include <revolution/OS/OSThread.h>
#include <revolution/OS/OSTime.h>
#include <types.h>

void gfMonitorThread::run() {
    while (true) {
        u64 x = (OS_BUS_CLOCK_SPEED / 4) / 1000;
        OSSleepTicks(x * 16);
        if (!unk340) {
            break;
        }
        if (unk350_b7) {
            s64 time = OSGetTime();
            if (unk350_b6) {
                time = OSGetTime();
                u32 x = (OS_BUS_CLOCK_SPEED / 4) / 1000;
                u32 elapsed = (u32)time - (u32)m_lastDrawTime;
                if (elapsed / x > 100) {
                    GXReadDrawSync();
                    GXAbortFrame();
                    GXSetDrawDone();
                    m_lastDrawTime = time;
                }
            }
        }
    }
}
