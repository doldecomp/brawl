#include <cstring>
#include <mu/wifi/mu_wifi_interface.h>
#include <nt/d_net_connect.h>
#include <nt/nt_match.h>
#include <revolution/SO/SOBasic.h>
#include <types.h>

static void* _Alloc(int p1, u32 p2) {
    return DWCAllocType::ntAlloc(p1, p2, 32);
}

static void _Free(int p1, void* p2) {
    DWCAllocType::ntFree(p1, p2);
}

s32 dNetConnect_Start() {
    netReport("SOInit() ");
    SOInitInfo info;
    std::memset(&info, 0, sizeof(SOInitInfo));
    info.allocator = _Alloc;
    info.dealloc = _Free;
    int err = SOInit(&info);
    if (err) {
        netReport0("failed (%d)\n", err);
        return err;
    }
    netReport0("success\n");
    netReport("SOStartup() ");
    err = SOStartupEx(180000);
    if (err) {
        netReport0("failed (%d)\n", err);
        return err;
    }
    netReport0("success\n");
    return err;
}

void dNetConnect_Finish() {
    SOCleanup();
    SOFinish();
}
