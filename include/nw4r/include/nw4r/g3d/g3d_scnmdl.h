#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_resmat.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>

namespace nw4r {
    namespace g3d {

        // TODO ScnMdlSimple and all subsequent classes
        class ScnMdl : public ScnMdlSimple {
        private:
            char _spacer[80];

        public:
            class CopiedMatAccess {
            private:
                ScnMdl* m_scnMdl;
                u32 m_MatID;
                char spacer[0x28];

            public:
                CopiedMatAccess(ScnMdl* scnMdl, u32 matID);
                ResMatTevColor GetResMatTevColor(bool sync);
            };

            class CopiedVisAccess {
            public:
                CopiedVisAccess(ScnMdl* pScnMdl, u32 id);

                bool IsVisible() const;
                bool SetVisibility(bool visible);

            private:
                ScnMdl* mpScnMdl; // at 0x0
                u32 mNodeID;      // at 0x4
                u8* mpVis;        // at 0x8
            };

            // TODO
            virtual u32 IsDerivedFrom(int* unk1);
            virtual void G3dProc(int unk1, int unk2, int unk3);
            virtual ~ScnMdl();

            static ScnMdl* Construct(void* memAllocator, int x, int y, void* scnModel);
            static void Pushback(void* thing, void* thing2, const char* str); // PushBack/[nw4r3g3d12ScnMdlExpandFPQ34nw4r3g3]/(g3d_scnmdlexpand.o)
        };
    }
}

// Size: 392
