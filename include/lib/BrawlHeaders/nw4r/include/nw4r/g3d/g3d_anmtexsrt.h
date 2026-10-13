#pragma once

#include <StaticAssert.h>
#include <MEM.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResAnmTexSrtData {
            char _spacer2[0x1C];
            unsigned short m_animLength;
        };
        class ResAnmTexSrt : public ResCommon<ResAnmTexSrtData> {
        public:
            inline ResAnmTexSrt() : ResCommon() {}
            inline ResAnmTexSrt(void* data) : ResCommon(data) {}
        };

        class AnmObjTexSrtRes : public G3dObj {
        public:
            virtual u32 IsDerivedFrom(int* unk1);

            virtual void G3dProc(int unk1, int unk2, int unk3);

            virtual ~AnmObjTexSrtRes();

            virtual int* GetTypeObj();

            virtual int GetTypeName();

            virtual void SetFrame(float frame);

            virtual float GetFrame();

            virtual void UpdateFrame();

            virtual void SetUpdateRate(float updateRate);

            virtual float GetUpdateRate();

            virtual int Bind(ResMdl mdl);

            virtual void Release();

            virtual int* GetResult(int* unk1, int unk2);

            virtual int Attach(int unk1, int* unk2); // TODO
            virtual int* Detach(int unk1);           // TODO
            virtual void DetachAll();

            static AnmObjTexSrtRes* Construct(MEMAllocator* allocator, int* instanceSize, ResAnmTexSrt anim, ResMdl mdl, bool hasCache);

            char _spacer[40];

            ResAnmTexSrt m_anmTexSrtFile;

            char _spacer2[4];
        };
    }
}

// Size: 52