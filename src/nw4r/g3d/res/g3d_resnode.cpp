#include <nw4r/g3d.h>
#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

void ResNode::PatchChrAnmResult(ChrAnmResult* pResult) const {
    if (!IsValid()) {
        return;
    }

    const ResNodeData& r = ref();
    u32 flags = pResult->flags;

    if (flags & ChrAnmResult::FLAG_PATCH_SCALE) {
        if (r.flags & ResNodeData::FLAG_SCALE_ONE) {
            flags |=
                ChrAnmResult::FLAG_SCALE_ONE | ChrAnmResult::FLAG_SCALE_UNIFORM;

            pResult->s.z = 1.0f;
            pResult->s.y = 1.0f;
            pResult->s.x = 1.0f;
        } else {
            u32 uniform = flags & ~ChrAnmResult::FLAG_SCALE_UNIFORM;

            if (r.flags & ResNodeData::FLAG_SCALE_UNIFORM) {
                uniform = flags | ChrAnmResult::FLAG_SCALE_UNIFORM;
            }

            flags = uniform & ~(ChrAnmResult::FLAG_MTX_IDENT |
                                ChrAnmResult::FLAG_SCALE_ONE);

            pResult->s.x = r.scale.x;
            pResult->s.y = r.scale.y;
            pResult->s.z = r.scale.z;
        }
    }

    if (flags & ChrAnmResult::FLAG_PATCH_ROT) {
        math::VEC3 trans(pResult->rt._03, pResult->rt._13, pResult->rt._23);

        if (r.flags & ResNodeData::FLAG_ROT_ZERO) {
            math::MTX34Identity(&pResult->rt);
            flags |= ChrAnmResult::FLAG_ROT_ZERO;
        } else {
            math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
            flags &= ~(ChrAnmResult::FLAG_ROT_ZERO |
                       ChrAnmResult::FLAG_ROT_TRANS_ZERO |
                       ChrAnmResult::FLAG_MTX_IDENT);
        }

        flags |= ChrAnmResult::FLAG_ROT_RAW_FMT;

        pResult->rt._03 = trans.x;
        pResult->rt._13 = trans.y;
        pResult->rt._23 = trans.z;
    }

    if (flags & ChrAnmResult::FLAG_PATCH_TRANS) {
        if (r.flags & ResNodeData::FLAG_TRANS_ZERO) {
            flags |= ChrAnmResult::FLAG_TRANS_ZERO;

            pResult->rt._23 = 0.0f;
            pResult->rt._13 = 0.0f;
            pResult->rt._03 = 0.0f;
        } else {
            flags &= ~(ChrAnmResult::FLAG_TRANS_ZERO |
                       ChrAnmResult::FLAG_ROT_TRANS_ZERO |
                       ChrAnmResult::FLAG_MTX_IDENT);

            pResult->rt._03 = r.translate.x;
            pResult->rt._13 = r.translate.y;
            pResult->rt._23 = r.translate.z;
        }
    }

    if (flags & ChrAnmResult::FLAG_ROT_ZERO) {
        if (flags & ChrAnmResult::FLAG_TRANS_ZERO) {
            flags |= ChrAnmResult::FLAG_ROT_TRANS_ZERO;

            if (flags & ChrAnmResult::FLAG_SCALE_ONE) {
                flags |= ChrAnmResult::FLAG_MTX_IDENT;
            }
        }
    }

    pResult->flags = flags & ~(ChrAnmResult::FLAG_PATCH_SCALE |
                               ChrAnmResult::FLAG_PATCH_ROT |
                               ChrAnmResult::FLAG_PATCH_TRANS);
}

void ResNode::CalcChrAnmResult(ChrAnmResult* pResult) const {
    if (!IsValid()) {
        return;
    }

    const ResNodeData& r = ref();
    u32 flags = 0;

    if (r.flags & ResNodeData::FLAG_SCALE_ONE) {
        flags |=
            ChrAnmResult::FLAG_SCALE_ONE | ChrAnmResult::FLAG_SCALE_UNIFORM;

        pResult->s.z = 1.0f;
        pResult->s.y = 1.0f;
        pResult->s.x = 1.0f;
    } else {
        if (r.flags & ResNodeData::FLAG_SCALE_UNIFORM) {
            flags |= ChrAnmResult::FLAG_SCALE_UNIFORM;
        }

        pResult->s = static_cast<const math::VEC3&>(r.scale);
    }

    if (r.flags & ResNodeData::FLAG_ROT_ZERO) {
        PSMTXIdentity(pResult->rt);
        flags |= ChrAnmResult::FLAG_ROT_ZERO;
    } else {
        pResult->rawR = math::VEC3(r.rot);
        math::MTX34RotXYZDeg(&pResult->rt, r.rot.x, r.rot.y, r.rot.z);
    }

    if (r.flags & ResNodeData::FLAG_TRANS_ZERO) {
        flags |= ChrAnmResult::FLAG_TRANS_ZERO;
    } else {
        pResult->rt._03 = r.translate.x;
        pResult->rt._13 = r.translate.y;
        pResult->rt._23 = r.translate.z;
    }

    if (flags & ChrAnmResult::FLAG_ROT_ZERO) {
        if (flags & ChrAnmResult::FLAG_TRANS_ZERO) {
            flags |= ChrAnmResult::FLAG_ROT_TRANS_ZERO;

            if (flags & ChrAnmResult::FLAG_SCALE_ONE) {
                flags |= ChrAnmResult::FLAG_MTX_IDENT;
            }
        }
    }

    flags |= ChrAnmResult::FLAG_ROT_RAW_FMT;
    flags |= ChrAnmResult::FLAG_ANM_EXISTS;

    if (r.flags & ResNodeData::FLAG_SSC_APPLY) {
        flags |= ChrAnmResult::FLAG_SSC_APPLY;
    }

    if (r.flags & ResNodeData::FLAG_SSC_PARENT) {
        flags |= ChrAnmResult::FLAG_SSC_PARENT;
    }

    pResult->flags = flags;
}

void ResNode::SetScale(f32 x, f32 y, f32 z) {
    if (IsValid()) {
        ResNodeData& r = ref();

        if (x == y && y == z) {
            r.flags |= ResNodeData::FLAG_SCALE_UNIFORM;

            if (x == 1.0f) {
                r.flags |= ResNodeData::FLAG_SCALE_ONE;
            } else {
                r.flags &= ~ResNodeData::FLAG_SCALE_ONE;
            }
        } else {
            r.flags &= ~(ResNodeData::FLAG_SCALE_UNIFORM |
                         ResNodeData::FLAG_SCALE_ONE);
        }

        if ((r.flags & ResNodeData::FLAG_TRANS_ZERO) &&
            (r.flags & ResNodeData::FLAG_ROT_ZERO) &&
            (r.flags & ResNodeData::FLAG_SCALE_ONE)) {
            r.flags |= ResNodeData::FLAG_IDENTITY;
        } else {
            r.flags &= ~ResNodeData::FLAG_IDENTITY;
        }

        r.scale.x = x;
        r.scale.y = y;
        r.scale.z = z;
    }
}

void ResNode::SetTranslate(f32 x, f32 y, f32 z) {
    if (IsValid()) {
        ResNodeData& r = ref();

        if (x == 0.0f && y == 0.0f && z == 0.0f) {
            r.flags |= ResNodeData::FLAG_TRANS_ZERO;
        } else {
            r.flags &= ~ResNodeData::FLAG_TRANS_ZERO;
        }

        if ((r.flags & ResNodeData::FLAG_TRANS_ZERO) &&
            (r.flags & ResNodeData::FLAG_ROT_ZERO) &&
            (r.flags & ResNodeData::FLAG_SCALE_ONE)) {
            r.flags |= ResNodeData::FLAG_IDENTITY;
        } else {
            r.flags &= ~ResNodeData::FLAG_IDENTITY;
        }

        r.translate.x = x;
        r.translate.y = y;
        r.translate.z = z;
    }
}

void ResNode::SetRotate(f32 x, f32 y, f32 z) {
    if (IsValid()) {
        ResNodeData& r = ref();

        if (x == 0.0f && y == 0.0f && z == 0.0f) {
            r.flags |= ResNodeData::FLAG_ROT_ZERO;
        } else {
            r.flags &= ~ResNodeData::FLAG_ROT_ZERO;
        }

        if ((r.flags & ResNodeData::FLAG_TRANS_ZERO) &&
            (r.flags & ResNodeData::FLAG_ROT_ZERO) &&
            (r.flags & ResNodeData::FLAG_SCALE_ONE)) {
            r.flags |= ResNodeData::FLAG_IDENTITY;
        } else {
            r.flags &= ~ResNodeData::FLAG_IDENTITY;
        }

        r.rot.x = x;
        r.rot.y = y;
        r.rot.z = z;
    }
}

} // namespace g3d
} // namespace nw4r
