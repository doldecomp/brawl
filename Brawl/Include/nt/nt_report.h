#pragma once

#include <StaticAssert.h>
#include <gf/gf_heap_manager.h>
#include <revolution/OS/OSMutex.h>
#include <sr/sr_common.h>
#include <types.h>

// TODO: determine the header these belong to
extern s32 gUnk805a03d8; // TODO: network status code?
extern s32 g_NtMatchingStatus;

struct NtBlock {
    float unk0;
    float unk4;

    NtBlock() : unk0(0.0f), unk4(0.0f) { }
};
static_assert(sizeof(NtBlock) == 0x8, "Class is the wrong size!");

struct NtBuffer {
    NtBuffer() : m_size(0), unk8(0), unkC(false), m_buf(nullptr) { }

    virtual ~NtBuffer() {
        freeBuffer();
    }

    virtual void allocBuffer(u32 size, Heaps::HeapType heapType) {
        m_buf = gfHeapManager::alloc(heapType, size);
        m_size = size;
        unk8 = 0;
    }

    virtual void freeBuffer() {
        if (!unkC && m_buf)
            gfHeapManager::free(m_buf);
        m_buf = nullptr;
        m_size = 0;
        unk8 = 0;
    }

    u32 m_size;
    s32 unk8;
    bool unkC;
    void* m_buf;
};
static_assert(sizeof(NtBuffer) == 0x14, "Class is the wrong size!");

struct NtBase {
    NtBase() : unk4(0) { }
    virtual ~NtBase() { }
    static bool isMatchStatusOnline();

    s32 unk4;
};

class NtReport : public NtBase {
    struct UnkArr1 {
        u8 unk0[0xD];
    };

    struct UnkArr2 {
        u8 unk0[0xB];
    };

    struct UnkArr3 {
        u8 unk0[0x29];
    };

    struct UnkArrContainer {
        UnkArr1 unk1C;
        s32 unk2C;
        UnkArr2 unk30;
        s32 unk3C;
        UnkArr3 unk40;
        s32 unk6C;

        UnkArrContainer() : unk2C(0), unk3C(0), unk6C(0) {
            memset(&unk1C, 0x30, sizeof(unk1C));
            unk1C.unk0[sizeof(unk1C) - 1] = 0;

            memset(&unk30, 0x20, sizeof(unk30));
            unk30.unk0[sizeof(unk30) - 1] = 0;

            memset(&unk40, 0x20, sizeof(unk40));
            unk40.unk0[24] = 0;
        }
    };

    u8 unk8[0xC];
    s32 unk14;
    s32 unk18;
    UnkArrContainer unk1C;
    u8 unk70[0x40];
    s32 unkB0;
    u8 unkB4[0x8];
    s32 unkBC;
    bool unkC0;
    s16 unkC2;
    s16 unkC4;
    NtBuffer unkC8;
    NtBuffer unkDC;
    NtBuffer unkF0;
    u8 unk104[0x4];
    bool unk108;
    s32 unk10C;
public:
    // NONMATCHING regswaps and slight instruction ordering issue
    // in nt_report.cpp's static initializer
    NtReport() : unkB0(0), unkC0(false), unkC4(0), unk108(false) { }
    virtual ~NtReport() { }
    void report(const char* fmt, ...);
    void createWork();
    void destroyWork();

    static OSMutex s_ReportMutex;
};
static_assert(sizeof(NtReport) == 0x110, "Class is the wrong size!");

void flushLogToSDCard();
