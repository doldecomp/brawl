#pragma once

#include <StaticAssert.h>

namespace nw4r {
    namespace g3d {

        class ICalcWorldCallBack {

        public:
            virtual ~ICalcWorldCallBack();
            virtual void ExecCallbackA(int* unk1, int unk2, int* unk3); // TODO
            virtual void ExecCallbackB(int* unk1, int unk2, int* unk3); // TODO
            virtual void ExecCallbackC();                               // TODO
        };

    } // namespace g3d
} // namespace nw4r