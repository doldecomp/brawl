#pragma once

#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <types.h>

Vec3f nwSMGetGlobalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId);
Vec3f nwSMGetGlobalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId, const Vec3f* pos);
Vec3f nwSMGetLocalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId);
Vec3f nwSMGetGlobalRotation(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId);
void nwSMSetVisibility(nw4r::g3d::ScnMdlSimple* scnMdl, bool vis);
void nwSMSetNodeVisibility(nw4r::g3d::ScnMdl* scnMdl, u32 nodeId, bool vis);
void nwSMSetNodeVisibility(nw4r::g3d::ScnMdl* scnMdl, s32 numIds, const u32* nodeIds, bool vis);
