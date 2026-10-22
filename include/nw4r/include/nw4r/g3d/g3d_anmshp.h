#pragma once

#include <StaticAssert.h>
#include <MEM.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResAnmShpData {
            char _spacer2[0x20];
            unsigned short m_animLength;
        };
        class ResAnmShp : public ResCommon<ResAnmShpData> {
        public:
            inline ResAnmShp() : ResCommon() {}
            inline ResAnmShp(void* data) : ResCommon(data) {}
        };

        class AnmObjShpRes : public G3dObj {
        public:
            virtual u32 IsDerivedFrom(int* unk1);

            virtual void G3dProc(int unk1, int unk2, int unk3);

            virtual ~AnmObjShpRes();

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

            virtual void SetWeight(float unk1, int* unk2); // TODO
            virtual float GetWeight(int unk1);             // TODO

            static AnmObjShpRes* Construct(MEMAllocator* allocator, int* instanceSize, ResAnmShp anim, ResMdl mdl, bool hasCache);

            char _spacer[40];

            ResAnmShp m_anmShpFile;

            char _spacer3[8];
        };
        static_assert(sizeof(AnmObjShpRes) == 56, "Class is wrong size!");
    }
}

// Size: 56