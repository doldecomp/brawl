#include <types.h>
#include <stdarg.h>

extern void OSReport(const char* format, ...);
extern void OSVReport(const char* format, va_list arguments);
extern u32 lbl_805A0F60;
extern const char lbl_804891A8[0x168];
extern const char lbl_8059F068[];

void DWC_SetReportLevel(u32 level) { lbl_805A0F60 = level; }

void DWC_Printf(u32 level, const char* format, ...) {
    va_list arguments;
    if ((level & lbl_805A0F60) == 0) return;
    switch (level) {
    case 0x1: OSReport(lbl_804891A8 + 0x0); break;
    case 0x2: OSReport(lbl_804891A8 + 0x10); break;
    case 0x4: OSReport(lbl_804891A8 + 0x20); break;
    case 0x8: OSReport(lbl_804891A8 + 0x30); break;
    case 0x10: OSReport(lbl_804891A8 + 0x40); break;
    case 0x20: OSReport(lbl_804891A8 + 0x50); break;
    case 0x40: OSReport(lbl_804891A8 + 0x60); break;
    case 0x80: OSReport(lbl_804891A8 + 0x70); break;
    case 0x100: OSReport(lbl_804891A8 + 0x80); break;
    case 0x200: OSReport(lbl_804891A8 + 0x90); break;
    case 0x400: OSReport(lbl_804891A8 + 0xA0); break;
    case 0x8000: OSReport(lbl_804891A8 + 0xB0); break;
    case 0x10000: OSReport(lbl_804891A8 + 0xC0); break;
    case 0x20000: OSReport(lbl_804891A8 + 0xD0); break;
    case 0x40000: OSReport(lbl_804891A8 + 0xE0); break;
    case 0x1000000: OSReport(lbl_804891A8 + 0xF4); break;
    case 0x2000000: OSReport(lbl_804891A8 + 0x104); break;
    case 0x4000000: OSReport(lbl_804891A8 + 0x114); break;
    case 0x8000000: OSReport(lbl_804891A8 + 0x124); break;
    case 0x10000000: OSReport(lbl_804891A8 + 0x134); break;
    case 0x80000000: OSReport(lbl_804891A8 + 0x144); break;
    default: OSReport(lbl_804891A8 + 0x154); break;
    }
    if (level != 0xFFFFFFFF && (level & 0x200000) != 0) OSReport(lbl_8059F068);
    va_start(arguments, format);
    OSVReport(format, arguments);
    va_end(arguments);
}
