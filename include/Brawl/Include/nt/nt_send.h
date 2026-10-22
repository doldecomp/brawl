#pragma once

#include <StaticAssert.h>
#include <nt/nt_report.h>
#include <revolution/OS/OSMutex.h>
#include <types.h>

struct NtPacketData {
    static const s32 MaxPacketSize = 0x37E;
    static const s32 TickFieldSize = 0x4;
    static const s32 PadAlign = 0x2;
    u8 data[MaxPacketSize + TickFieldSize + PadAlign];
};
static_assert(sizeof(NtPacketData) == 0x384, "Class is the wrong size!");

struct NtPacket {
    u8 aid;
    u32 size;
    NtPacketData* rawData;
};
static_assert(sizeof(NtPacket) == 0xC, "Class is the wrong size!");

class NtSend {
    static const u32 Capacity = 0x40;
    typedef NtPacket (*NtPacketArrPtr)[Capacity];

    OSMutex m_mutex;
    OSCond m_cond;
    NtPacketArrPtr m_pktBuffer; // Circular queue of packets to be sent
    NtBuffer m_pktMemory; // Backing memory for m_pktBuffer
    s32 m_startIdx;
    s32 m_endIdx;
    NtBuffer m_pktMemory2; // NOTE: unused?
public:
    void create();
    void destroy();
    void clearSendBuffer();
    s32 pushback(u8 aid, const void* packetData, s32 packetSize);
    void task() volatile;
};
static_assert(sizeof(NtSend) == 0x54, "Class is the wrong size!");

extern NtSend* g_NtSend;

// TODO move
extern u32 g_NtAIDBitmap;
