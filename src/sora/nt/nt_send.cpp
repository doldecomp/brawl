#include <cstring>
#include <gf/gf_heap_manager.h>
#include <mu/wifi/mu_wifi_interface.h>
#include <nt/nt_report.h>
#include <nt/nt_send.h>
#include <revolution/DWC/dwc_transport.h>
#include <revolution/OS/OSMutex.h>
#include <revolution/OS/OSTime.h>
#include <sr/sr_common.h>
#include <types.h>

NtSend* g_NtSend;

// NONMATCHING regswap in unrolled for loop
void NtSend::create() {
    g_NtSend = this;
    m_pktBuffer = static_cast<NtPacketArrPtr>(
        gfHeapManager::alloc(Heaps::Network, Capacity * sizeof(NtPacket)));
    m_pktMemory2.allocBuffer(sizeof(NtPacketData), Heaps::Network);
    m_pktMemory.allocBuffer(Capacity * sizeof(NtPacketData), Heaps::Network);
    memset(m_pktBuffer, 0, 4);
    NtPacketArrPtr pktPtr = m_pktBuffer;
    for (u32 i = 0; i < Capacity; i++) {
        (*pktPtr)[i].rawData =
            i + static_cast<NtPacketData*>(m_pktMemory.m_buf);
    }
    clearSendBuffer();
    OSInitMutex(&m_mutex);
    OSInitCond(&m_cond);
}

void NtSend::destroy() {
    m_pktMemory2.freeBuffer();
    m_pktMemory.freeBuffer();
    gfHeapManager::free(m_pktBuffer);
    m_pktBuffer = nullptr;
    g_NtSend = nullptr;
}

void NtSend::clearSendBuffer() {
    m_endIdx = 0;
    m_startIdx = 0;
}

s32 NtSend::pushback(u8 aid, const void* packetData, s32 packetSize) {
    if ((g_NtAIDBitmap & (1 << aid)) == 0)
        return 0;
    if (aid >= 4)
        return -1;
    if (packetSize > NtPacketData::MaxPacketSize)
        netReport("Too large packet data\n");
    if (((g_NtSend->m_endIdx - g_NtSend->m_startIdx) & 0x3F) >= 0x3E)
        return -1;
    (*m_pktBuffer)[m_endIdx].aid = aid;
    (*m_pktBuffer)[m_endIdx].size = packetSize;
    memcpy((*m_pktBuffer)[m_endIdx].rawData, packetData, packetSize);
    m_endIdx = (m_endIdx + 1) & 0x3F;
    return 0;
}

// TODO: Find better match than this volatile hack
void NtSend::task() volatile {
    while (m_startIdx != m_endIdx) {
        s32 i, j;
        j = m_startIdx;
        i = m_startIdx;
        NtPacketArrPtr pkts = m_pktBuffer;
        NtPacketData* pkt = (*pkts)[j].rawData;
        u32 pktSize = (*pkts)[i].size;
        u32 tick = OSGetTick();
        pkt->data[pktSize]   = tick >> 24;
        pkt->data[pktSize+1] = tick >> 16;
        pkt->data[pktSize+2] = tick >> 8;
        pkt->data[pktSize+3] = tick;
        u8 aid = (*m_pktBuffer)[m_startIdx].aid;
        if ((g_NtAIDBitmap & (1 << aid)) != 0)
            DWC_SendUnreliable(aid, pkt, pktSize+4);
        m_startIdx = (m_startIdx + 1) & 0x3F;
    }
}
