#include <nw4r/g3d.h>

#include <algorithm>

namespace nw4r {
namespace g3d {

NW4R_G3D_RTTI_DEF(ScnMdlExpand);

namespace {

// HYPOTHESIS: a plain (non-const) variable in the original, since it is read
// from memory every time it is used.
u32 sInvalidNodeID = 0xFFFFFFFF;

} // namespace

ScnMdlExpand* ScnMdlExpand::Construct(MEMAllocator* pAllocator, u32* pSize,
                                      int capacity, ScnMdl* pScnMdl) {
    u32 nodeIDOfs = align4(sizeof(ScnMdlExpand) + capacity * sizeof(ScnObj*));
    u32 size = align4(nodeIDOfs + capacity * sizeof(u32));

    if (pSize != NULL) {
        *pSize = size;
    }

    if (pAllocator != NULL) {
        u8* pBuffer = reinterpret_cast<u8*>(Alloc(pAllocator, size));

        if (pBuffer == NULL) {
            return NULL;
        }

        ScnObj** ppObj =
            reinterpret_cast<ScnObj**>(pBuffer + sizeof(ScnMdlExpand));
        u32* pNodeID = reinterpret_cast<u32*>(pBuffer + nodeIDOfs);

        return new (pBuffer)
            ScnMdlExpand(pAllocator, ppObj, capacity, pScnMdl, pNodeID);
    }

    return NULL;
}

ScnMdlExpand::ScnMdlExpand(MEMAllocator* pAllocator, ScnObj** ppObj,
                           u32 capacity, ScnMdl* pScnMdl, u32* pNodeID)
    : ScnGroup(pAllocator, ppObj, capacity),
      mpScnMdl(pScnMdl),
      mpNodeID(pNodeID) {

    for (u32 i = 0; i < capacity; ++i) {
        mpNodeID[i] = sInvalidNodeID;
    }

    mpScnMdl->G3dProc(G3DPROC_ATTACH_PARENT, 0, this);
}

bool ScnMdlExpand::SetNodeID(u32 idx, u32 nodeID) {
    if (nodeID < mpScnMdl->GetResMdl().GetResNodeNumEntries() &&
        idx < Size()) {
        mpNodeID[idx] = nodeID;
        return true;
    }

    return false;
}

bool ScnMdlExpand::PushBack(ScnObj* pObj, u32 nodeID) {
    if (!Insert(Size(), pObj)) {
        return false;
    }

    if (!SetNodeID(Size() - 1, nodeID)) {
        if (Size() != 0) {
            Remove(Size() - 1);
        }

        return false;
    }

    return true;
}

bool ScnMdlExpand::PushBack(ScnObj* pObj, const char* pNodeName) {
    ResNode node = mpScnMdl->GetResMdl().GetResNode(pNodeName);
    u32 nodeID = sInvalidNodeID;

    if (node.IsValid()) {
        nodeID = node.GetID();
    }

    if (!Insert(Size(), pObj)) {
        return false;
    }

    if (!SetNodeID(Size() - 1, nodeID)) {
        if (Size() != 0) {
            Remove(Size() - 1);
        }

        return false;
    }

    return true;
}

bool ScnMdlExpand::Insert(u32 idx, ScnObj* pObj) {
    u32 invalid = sInvalidNodeID;

    if (ScnGroup::Insert(idx, pObj)) {
        for (u32 i = Size() - 1; i > idx; i--) {
            mpNodeID[i] = mpNodeID[i - 1];
        }

        mpNodeID[idx] = invalid;
        return true;
    }

    return false;
}

ScnObj* ScnMdlExpand::Remove(u32 idx) {
    ScnObj* pObj = ScnGroup::Remove(idx);

    if (pObj != NULL) {
        u32 num = Size();

        for (u32 i = idx; i < num; i++) {
            mpNodeID[i] = mpNodeID[i + 1];
        }
    }

    return pObj;
}

bool ScnMdlExpand::Remove(ScnObj* pObj) {
    ScnObj** ppObj = std::find(Begin(), End(), pObj);

    if (ppObj != End()) {
        return Remove(std::distance(Begin(), ppObj)) != NULL;
    }

    return false;
}

void ScnMdlExpand::G3dProc(u32 task, u32 param, void* pInfo) {
    if (IsG3dProcDisabled(task)) {
        return;
    }

    switch (task) {
    case G3DPROC_CALC_WORLD: {
        CheckCallback_CALC_WORLD(CALLBACK_TIMING_A, param, pInfo);

        CalcWorldMtx(static_cast<const math::MTX34*>(pInfo), &param);

        CheckCallback_CALC_WORLD(CALLBACK_TIMING_B, param, pInfo);

        if (mpScnMdl != NULL) {
            mpScnMdl->G3dProc(G3DPROC_CALC_WORLD, param,
                              const_cast<math::MTX34*>(GetMtxPtr(MTX_WORLD)));
        }

        u32 num = Size();
        for (u32 i = 0; i < num; i++) {
            if (mpNodeID[i] != sInvalidNodeID) {
                ScnObj* pChild = Begin()[i];
                u32 childParam = param;
                math::MTX34 mtx;

                if (mpScnMdl == NULL ||
                    !mpScnMdl->GetScnMtxPos(&mtx, MTX_WORLD, mpNodeID[i])) {
                    childParam |= 1;
                }

                pChild->G3dProc(G3DPROC_CALC_WORLD, childParam, &mtx);
            }
        }

        CheckCallback_CALC_WORLD(CALLBACK_TIMING_C, param, pInfo);
        break;
    }

    case G3DPROC_CHILD_DETACHED: {
        if (pInfo == mpScnMdl) {
            mpScnMdl->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
            mpScnMdl = NULL;
        } else {
            DefG3dProcScnGroup(task, param, pInfo);
        }
        break;
    }

    case G3DPROC_ATTACH_PARENT:
    case G3DPROC_DETACH_PARENT: {
        DefG3dProcScnGroup(task, param, pInfo);
        break;
    }

    default: {
        if (mpScnMdl != NULL) {
            mpScnMdl->G3dProc(task, param, pInfo);
        }

        DefG3dProcScnGroup(task, param, pInfo);
        break;
    }
    }
}

ScnMdlExpand::~ScnMdlExpand() {
    if (mpScnMdl != NULL) {
        mpScnMdl->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
    }
}

} // namespace g3d
} // namespace nw4r
