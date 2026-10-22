#pragma once

#include <StaticAssert.h>
#include <memory.h>
#include <types.h>
#include <snd/snd_id.h>
#include <snd/snd_3d_generator.h>

namespace StSeUtil {
    // TODO: Find more descriptive name
    struct UnkStruct {
        SndID id;
        float unk4; // pan?
        float unk8;
        float unkC;
    };

    // TODO: Find more descriptive name
    struct UnkStruct2 {
        UnkStruct* unk0;
        size_t unk4; // length of both unk0 and unk8
        // Maps index of the SeSeq's UnkStruct3 array with the same SndID
        // as this type's UnkStruct array
        size_t* unk8;
    };

    // TODO: Find more descriptive name
    struct UnkStruct3 {
        SndID id;
        s32 unk4;
        s32 unk8; // 2 LSBits form a logical bitfield
        UnkStruct* unkC;
    };

    class SeSeq {
    public:
        virtual ~SeSeq() = 0;

    public:
        UnkStruct2* unk4;               // 0x04
        size_t unk8;                    // 0x08
        UnkStruct3* unkC;               // 0x0C
        size_t unk10;                   // 0x10
        snd3DGenerator* m_sndGenerator; // 0x14
        s32 unk18;
        float unk1C;

    public:
        SeSeq(UnkStruct2* unk, size_t unk2, UnkStruct3* unk3, size_t unk4);
        void playFrame(s32 unk, float frame);
        void playFrame(s32 unk2, float frame, float unk1);
        void registId(SndID* ids, size_t n); // n is limited to be < unk10
        void registSeq(int unk1, UnkStruct* ID, size_t unk2, Heaps::HeapType heapType);
        void mapping();
    };
    static_assert(sizeof(SeSeq) == 0x20, "Class is wrong size!");

    template<size_t M, size_t N>
    struct SeSeqInstance : public SeSeq {
        SeSeqInstance() : SeSeq(unk20, M, unk50, N) { }
        virtual ~SeSeqInstance() { }
        UnkStruct2 unk20[M];
        UnkStruct3 unk50[N];
    };
}
