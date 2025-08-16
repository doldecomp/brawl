#include <gf/gf_pad_system.h>
#include <gf/gf_pad_thread.h>
#include <revolution/OS/OSAlarm.h>
#include <revolution/OS/OSHardware.h>
#include <revolution/OS/OSThread.h>
#include <revolution/OS/OSTime.h>
#include <types.h>

void gfPadReadThread::run() {
    m_name = "gfPadReadThread";
    OSAlarm* alarm = &g_gfPadSystem->m_alarm;

    u64 period = (OS_BUS_CLOCK_SPEED / 4) / 59.941f;
    s64 tick = ((OS_BUS_CLOCK_SPEED / 4) / 1000) + OSGetTime();

    OSCreateAlarm(alarm);
    OSSetPeriodicAlarm(alarm, tick, period, gfPadSystem::_alarmCallback);

    do {
        OSSuspendThread(&m_thread);
        g_gfPadSystem->updateLow();
    } while (unk340);
    OSCancelAlarm(alarm);
}
