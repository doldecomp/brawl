#pragma once

#include <StaticAssert.h>

namespace nw4r {
    namespace g3d {
        class G3dObj {
        public:
            void Destroy();
            G3dObj* DetachFromParent();

            virtual u32 IsDerivedFrom(int* unk1);
            virtual void G3dProc(int unk1, int unk2, int unk3);
            virtual ~G3dObj();
        };
    }
}