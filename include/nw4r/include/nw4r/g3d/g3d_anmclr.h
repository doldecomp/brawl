#pragma once

#include <StaticAssert.h>
#include <MEM.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResAnmClrData {
            char _spacer2[0x1C];
            unsigned short m_animLength;
        };
        class ResAnmClr : public ResCommon<ResAnmClrData> {
        public:
            inline ResAnmClr() : ResCommon() {}
            inline ResAnmClr(void* data) : ResCommon(data) {}
        };

        class AnmObjMatClrRes : public G3dObj {
        public:
            virtual u32 IsDerivedFrom(int* unk1);

            virtual void G3dProc(int unk1, int unk2, int unk3);

            virtual ~AnmObjMatClrRes();

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

            static AnmObjMatClrRes* Construct(MEMAllocator* allocator, int* size, ResAnmClr anim, ResMdl mdl, bool hasCache);

            char _spacer[40];

            ResAnmClr m_anmMatClrFile;

            char _spacer2[4];
        };
    }
}

// Size: 52