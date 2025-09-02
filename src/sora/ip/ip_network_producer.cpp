#include <ip/ip_network_producer.h>
#include <nt/network.h>
#include <sr/sr_common.h>
#include <types.h>

static ipNetworkProducer* g_ipNetworkProducer;

ipNetworkProducer* ipNetworkProducer::getInstance() {
    if (!g_ipNetworkProducer) {
        g_ipNetworkProducer = new (Heaps::SystemFW) ipNetworkProducer;
    }
    return g_ipNetworkProducer;
}

// NONMATCHING regswaps
void ipNetworkProducer::networkInCallback(const u16* p1) {
    if (!g_ipNetworkProducer) {
        g_ipNetworkProducer = new (Heaps::SystemFW) ipNetworkProducer(true);
    }
    ipNetworkProducer* ip = g_ipNetworkProducer;
    u8* r7 = reinterpret_cast<u8*>(ip);
    u8 r6 = 0;
    if (ip->unk0) {
        r6 = r7[ip->unk0] + 1;
    }
    if (r6 >= 1) {
        r6 = 0;
    }

    r7[ip->unk0 + 1] = r6;
    UnkIpNetworkMsg* r5 = &ip->unk2 + r6;
    for (s32 i = 0; i < 8; i++) {
        r5->unk0[i] = p1[i];
    }

    ip->unk0++;
}

UnkIpNetworkMsg* ipNetworkProducer::front() {
    return &unk2 + unk1;
}

void ipNetworkProducer::pop() {
    unk0--;
}

void ipNetworkProducer::clear() {
    unk0 = 0;
    unk1 = 0xFF;
}
