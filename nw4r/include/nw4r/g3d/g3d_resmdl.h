#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resmat.h>
#include <nw4r/g3d/g3d_resnode.h>
#include <types.h>

namespace nw4r {
    namespace g3d {

        struct ResMdlData; // TODO

        class ResMdl : public ResCommon<ResMdlData> {

            /* data */
        public:
            inline ResMdl() : ResCommon() {}
            inline ResMdl(void* data) : ResCommon(data) {}

            ResMat GetResMat(const char* name) const;
            u32 GetResNodeNumEntries();
            ResNode GetResNode(const int nodeIndex) const;
            ResNode GetResNode(const u32 nodeIndex) const;
            ResNode GetResNode(const char* nodeName) const;
        };

    } // namespace g3d
} // namespace nw4r
