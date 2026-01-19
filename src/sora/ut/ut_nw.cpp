#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <types.h>
#include <ut/ut_nw.h>

Vec3f nwSMGetGlobalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId, const Vec3f* pos) {
    Vec3f res;
    Matrix mtx(true);
    scnMdl->GetScnMtxPos(&mtx, nw4r::g3d::ScnObj::MTX_WORLD, nodeId);
    if (0.0f != pos->m_x || 0.0f != pos->m_y || 0.0f != pos->m_z) {
        mtx.mulPos(pos, &res);
    } else {
        float z = mtx.m[2][3];
        float y = mtx.m[1][3];
        float x = mtx.m[0][3];
        res.m_x = x;
        res.m_y = y;
        res.m_z = z;
    }
    return res;
}

Vec3f nwSMGetGlobalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId) {
    Vec3f res;
    Matrix mtx(true);
    scnMdl->GetScnMtxPos(&mtx, nw4r::g3d::ScnObj::MTX_WORLD, nodeId);
    float z = mtx.m[2][3];
    float y = mtx.m[1][3];
    float x = mtx.m[0][3];
    res.m_x = x;
    res.m_y = y;
    res.m_z = z;
    return res;
}

Vec3f nwSMGetLocalPosition(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId) {
    Vec3f res;
    Matrix mtx(true);
    scnMdl->GetScnMtxPos(&mtx, nw4r::g3d::ScnObj::MTX_LOCAL, nodeId);
    float z = mtx.m[2][3];
    float y = mtx.m[1][3];
    float x = mtx.m[0][3];
    res.m_x = x;
    res.m_y = y;
    res.m_z = z;
    return res;
}

Vec3f nwSMGetGlobalRotation(const nw4r::g3d::ScnMdlSimple* scnMdl, u32 nodeId) {
    Vec3f res;
    Matrix mtx(true);
    scnMdl->GetScnMtxPos(&mtx, nw4r::g3d::ScnObj::MTX_WORLD, nodeId);
    mtx.getRotate(&res);
    res.m_x = 57.29578f * res.m_x;
    res.m_y = 57.29578f * res.m_y;
    res.m_z = 57.29578f * res.m_z;
    return res;
}

void nwSMSetVisibility(nw4r::g3d::ScnMdlSimple* scnMdl, bool vis) {
    if (vis) {
        scnMdl->SetScnObjOption(0x10001, 0);
    } else {
        scnMdl->SetScnObjOption(0x10001, 1);
    }
}

void nwSMSetNodeVisibility(nw4r::g3d::ScnMdl* scnMdl, u32 nodeId, bool vis) {
    nw4r::g3d::ScnMdl::CopiedVisAccess cva(scnMdl, nodeId);
    cva.SetVisibility(vis);
}

void nwSMSetNodeVisibility(nw4r::g3d::ScnMdl* scnMdl, s32 numIds, const u32* nodeIds, bool vis) {
    for (s32 i = 0; i < numIds; i++) {
        nw4r::g3d::ScnMdl::CopiedVisAccess cva(scnMdl, nodeIds[i]);
        cva.SetVisibility(vis);
    }
}
