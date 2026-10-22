#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resmat.h>
#include <nw4r/g3d/g3d_resnode.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResTexData; // TODO

        class ResTex : public ResCommon<ResTexData> {

            /* data */
            public:
                inline ResTex() : ResCommon() {}
                inline ResTex(void* data) : ResCommon(data) {}
        };

    } // namespace g3d
} // namespace nw4r
