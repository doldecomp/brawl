#pragma once

#include <StaticAssert.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        class ScnObj {
        public:
            enum ScnObjMtxType { MTX_LOCAL, MTX_WORLD, MTX_VIEW, MTX_TYPE_MAX };
            // TODO
            virtual u32 IsDerivedFrom(int* unk1);

            virtual void G3dProc(int unk1, int unk2, int unk3);

            virtual ~ScnObj();

            char _spacer[216];

            void SetPriorityDrawOpa(int prio);

            void SetPriorityDrawXlu(int prio);

        };
    }
}
//// Size: 220
