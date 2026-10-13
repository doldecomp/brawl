#pragma once

#include <nt/network.h>
#include <types.h>

// TODO
struct UnkIpNetworkMsg {
    u16 unk0[8];
};

// This class has a 2-byte header followed by some record, likely encoding
// controller inputs
// byte 0: size
// byte 1: "front" index
// TODO: relationship to ipPadStatus and/or ipPadButton?
class ipNetworkProducer {
    u8 unk0;
    u8 unk1;
    UnkIpNetworkMsg unk2;

public:
    // Note: The 2nd constructor is a hack to satisfy 3 requirements for a
    // full match:
    // 1. getInstance does not inline ntSetConsumedDataCallback
    // 2. ntSetConsumedDataCallback is emitted after getInstance
    // 3. networkInCallback inlines ntSetConsumedDataCallback
    ipNetworkProducer() {
        void (*f)(NtShared::ntConsumedDataCallback_t) = NtShared::ntSetConsumedDataCallback;
        f(networkInCallback);
        clear();
    }

    ipNetworkProducer(bool hack) {
        NtShared::ntSetConsumedDataCallback(networkInCallback);
        clear();
    }

    static ipNetworkProducer* getInstance();
    static void networkInCallback(const u16*);
    UnkIpNetworkMsg* front();
    void pop();
    void clear();
};
// TODO size
