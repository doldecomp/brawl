#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_calcworldcallback.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <nw4r/math/math_types.h>

namespace nw4r {
    namespace g3d {
        class AnmObj;

        class ScnMdlSimple : public ScnObj {
        public:
            enum AnmObjType {
                ANMOBJTYPE_CHR,
                ANMOBJTYPE_VIS,
                ANMOBJTYPE_MATCLR,
                ANMOBJTYPE_TEXPAT,
                ANMOBJTYPE_TEXSRT,
                ANMOBJTYPE_SHP,
                ANMOBJTYPE_NOT_SPECIFIED,

                ANMOBJTYPE_VTX = ANMOBJTYPE_SHP
            };

            // FIXME: placeholders for inherited members until nw4r is updated
            virtual void vfunc1();
            virtual void vfunc2();
            virtual void G3dProc(u32 task, u32 param, void* pInfo); // at 0xC
            virtual ~ScnMdlSimple();                                // at 0x10

            virtual bool SetScnObjOption(u32 option, u32 value);         // at 0x20
            virtual bool GetScnObjOption(u32 option, u32* pValue) const; // at 0x24

            // FIXME: placeholders for inherited members until nw4r is updated
            virtual void vfunc3();
            virtual void vfunc4();
            virtual void vfunc5();
            virtual bool SetAnmObj(AnmObj* pObj, AnmObjType type);  // at 0x34
            virtual bool RemoveAnmObj(AnmObj* pObj);                // at 0x38
            virtual AnmObj* RemoveAnmObj(AnmObjType type);          // at 0x3C
            virtual AnmObj* GetAnmObj(AnmObjType type);             // at 0x40
            virtual const AnmObj* GetAnmObj(AnmObjType type) const; // at 0x44

            char _spacer[12];
            ResMdl m_resMdl; // +0xE8
            char _spacer2[48];
            ICalcWorldCallBack* m_calcWorldCallBack;
            char _spacer3[2];
            short m_nodeIndex;
            char _spacer4[20];

            void EnableScnMdlCallbackTiming(u32 flags);
            void UpdateFrame();
            bool GetScnMtxPos(math::MTX34* pMtx, ScnObjMtxType type, u32 idx) const;
        };
    }
}

// Size: 312
