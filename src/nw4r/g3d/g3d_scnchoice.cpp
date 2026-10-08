#include <nw4r/g3d.h>

#include <algorithm>

namespace nw4r {
namespace g3d {

NW4R_G3D_RTTI_DEF(ScnChoice);

ScnChoice* ScnChoice::Construct(MEMAllocator* pAllocator, u32* pSize,
                                int capacity) {
    ScnChoice* pChoice = NULL;
    u32 size = align4(sizeof(ScnChoice) + capacity * sizeof(ScnObj*));

    if (pSize != NULL) {
        *pSize = size;
    }

    if (pAllocator != NULL) {
        u8* pBuffer = reinterpret_cast<u8*>(Alloc(pAllocator, size));

        if (pBuffer != NULL) {
            ScnObj** ppObj =
                reinterpret_cast<ScnObj**>(pBuffer + sizeof(ScnChoice));

            pChoice = new (pBuffer) ScnChoice(pAllocator, ppObj, capacity);
        }
    }

    return pChoice;
}

void ScnChoice::ValidateChoice() {
    if (mpChoice != NULL) {
        ScnObj** ppObj = std::find(Begin(), End(), mpChoice);

        if (ppObj == End()) {
            mpChoice = NULL;
        }
    }
}

bool ScnChoice::SetChoice(ScnObj* pObj) {
    mpChoice = pObj;
    ValidateChoice();

    return mpChoice != NULL;
}

bool ScnChoice::SetChoice(int idx) {
    if (idx >= 0 && idx < static_cast<int>(Size())) {
        mpChoice = Begin()[idx];
        ValidateChoice();

        return mpChoice != NULL;
    }

    return false;
}

void ScnChoice::G3dProc(u32 task, u32 param, void* pInfo) {
    if (IsG3dProcDisabled(task)) {
        return;
    }

    switch (task) {
    case G3DPROC_CALC_WORLD: {
        CheckCallback_CALC_WORLD(CALLBACK_TIMING_A, param, pInfo);

        CalcWorldMtx(static_cast<const math::MTX34*>(pInfo), &param);

        CheckCallback_CALC_WORLD(CALLBACK_TIMING_B, param, pInfo);

        ValidateChoice();

        if (mpChoice != NULL) {
            mpChoice->G3dProc(G3DPROC_CALC_WORLD, param,
                              const_cast<math::MTX34*>(GetMtxPtr(MTX_WORLD)));
        }

        CheckCallback_CALC_WORLD(CALLBACK_TIMING_C, param, pInfo);
        break;
    }

    case G3DPROC_CALC_MAT: {
        CheckCallback_CALC_MAT(CALLBACK_TIMING_A, param, pInfo);

        ValidateChoice();

        if (mpChoice != NULL) {
            mpChoice->G3dProc(G3DPROC_CALC_MAT, param, pInfo);
        }

        CheckCallback_CALC_MAT(CALLBACK_TIMING_C, param, pInfo);
        break;
    }

    case G3DPROC_CALC_VIEW: {
        CheckCallback_CALC_VIEW(CALLBACK_TIMING_A, param, pInfo);

        CalcViewMtx(static_cast<const math::MTX34*>(pInfo));

        CheckCallback_CALC_VIEW(CALLBACK_TIMING_B, param, pInfo);

        ValidateChoice();

        if (mpChoice != NULL) {
            mpChoice->G3dProc(G3DPROC_CALC_VIEW, param, pInfo);
        }

        CheckCallback_CALC_VIEW(CALLBACK_TIMING_C, param, pInfo);
        break;
    }

    case G3DPROC_GATHER_SCNOBJ: {
        IScnObjGather* pCollection = static_cast<IScnObjGather*>(pInfo);

        ValidateChoice();

        IScnObjGather::CullingStatus status =
            pCollection->Add(this, false, false);

        if (status == IScnObjGather::CULLINGSTATUS_INTERSECT) {
            mpChoice->G3dProc(G3DPROC_GATHER_SCNOBJ, param, pCollection);
        } else if (status == IScnObjGather::CULLINGSTATUS_INSIDE) {
            const math::FRUSTUM* pTemp = gpCullingFrustum;
            gpCullingFrustum = NULL;
            mpChoice->G3dProc(G3DPROC_GATHER_SCNOBJ, param, pCollection);
            gpCullingFrustum = pTemp;
        }
        break;
    }

    case G3DPROC_DRAW_OPA:
    case G3DPROC_DRAW_XLU:
    case G3DPROC_CHILD_DETACHED:
    case G3DPROC_ATTACH_PARENT:
    case G3DPROC_DETACH_PARENT: {
        DefG3dProcScnGroup(task, param, pInfo);
        break;
    }

    default: {
        ValidateChoice();

        if (mpChoice != NULL) {
            mpChoice->G3dProc(task, param, pInfo);
        }
        break;
    }
    }
}

} // namespace g3d
} // namespace nw4r
