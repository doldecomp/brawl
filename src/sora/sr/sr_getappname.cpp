#ifndef MATCHING
#include <arpa/inet.h>
#endif
#include <revolution/OS/OS.h>
#include <sr/sr_getappname.h>
#include <types.h>

const char* srGetAppGamename() {
    return OSGetAppGamename();
}

// Note: The matching code assumes big-endian
u32 srGetAppInitialCode() {
#ifdef MATCHING
    return *reinterpret_cast<const u32*>(OSGetAppGamename());
#else
    u32 code;
    memcpy(&code, OSGetAppGamename(), sizeof(u32));
    return ntohl(code);
#endif
}

u32 srGetAppInitialCodeLocaleNum() {
    return 3;
}

// Note: The matching code assumes big-endian
u32 srGetAppInitialCodeLocale(u32 i) {
#ifdef MATCHING
    return *reinterpret_cast<const u32*>(&"RSBJRSBERSBP"[sizeof(u32)*i]);
#else
    u32 code;
    memcpy(&code, &"RSBJRSBERSBP"[sizeof(u32)*i], sizeof(u32));
    return ntohl(code);
#endif
}
