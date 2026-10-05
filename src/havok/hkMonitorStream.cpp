#include <havok/hkMonitorStream.h>

hkMonitorStream hkMonitorStream::s_instance;

void hkMonitorStream::init() {
    hkMonitorStream& s = s_instance;
    s.m_start = 0;
    s.m_isBufferAllocatedOnHeap = false;
    s.unk8 = 0;
    s.unk4 = 0;
    s.unkC = 0;
}

void hkMonitorStream::quit() {
    bool owns = m_start != 0 && m_isBufferAllocatedOnHeap;
    if (owns) {
        hkMemory::getInstance().deallocate(m_start);
    }
}
