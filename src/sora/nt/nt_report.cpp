#include <revolution/OS/OSMutex.h>
#include <nt/nt_report.h>

static NtReport g_NtReport;
OSMutex NtReport::s_ReportMutex;
static NtBlock g_NtBlockArray[4];
static NtBuffer g_NtBuffer;

bool NtBase::isMatchStatusOnline() {
    return g_NtMatchingStatus >= 5 && gUnk805a03d8 <= 10;
}

void flushLogToSDCard() { }

void NtReport::report(const char* fmt, ...) { }

void NtReport::createWork() {
    unk14 = 0;
    unk18 = 0;
    unkB0 = 0;
    unk10C = 0;
    unkBC = 0;
    unkC2 = 0;
    OSInitMutex(&s_ReportMutex);
}

void NtReport::destroyWork() { }
