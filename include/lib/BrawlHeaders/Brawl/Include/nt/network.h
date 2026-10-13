#pragma once

#include <StaticAssert.h>
#include <nt/d_net_connect.h>
#include <nt/etc/nt_etc_dwc.h>
#include <DWC.h>
#include <NHTTP.h>
#include <types.h>

class NtShared {
public:
    typedef void (*ntConsumedDataCallback_t)(const u16*);
    static void ntSetConsumedDataCallback(ntConsumedDataCallback_t cb) {
        NtConsumedDataCallback = cb;
    }
private:
    static ntConsumedDataCallback_t NtConsumedDataCallback;
};
// TODO size

class ntResetCallback {
    virtual void userProc();
    virtual ~ntResetCallback();
};

class ntReturnStatusCallback {
    virtual bool returnStatus();
};

class ntShutdown : public ntReturnStatusCallback {
public:
    virtual bool returnStatus();
};

class Network {
public:
    virtual ~Network();
    void create(bool);

private:
    char _0x4[0x3C];
};
static_assert(sizeof(Network) == 0x40, "Class is wrong size!");

extern Network g_Network;
