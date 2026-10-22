#pragma once

#include <StaticAssert.h>
#include <MEM.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResAnmTexPatData {
            char _spacer2[0x2C];
            unsigned short m_animLength;
        };
        class ResAnmTexPat : public ResCommon<ResAnmTexPatData> {
        public:
            inline ResAnmTexPat() : ResCommon() {}
            inline ResAnmTexPat(void* data) : ResCommon(data) {}
        };

        class AnmObjTexPatRes : public G3dObj {
        public:
            virtual u32 IsDerivedFrom(int* unk1);

            virtual void G3dProc(int unk1, int unk2, int unk3);

            virtual ~AnmObjTexPatRes();

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

            static AnmObjTexPatRes* Construct(MEMAllocator* allocator, int* instanceSize, ResAnmTexPat anim, ResMdl mdl, bool hasCache);

            char _spacer[40];

            ResAnmTexPat m_anmTexPatFile;

            char _spacer2[4];
        };
    }
}

// Size: 52