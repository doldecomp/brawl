#include <mt/mt_matrix.h>
#include <mt/mt_trig.h>
#include <mt/mt_vector.h>
#include <math.h>
#include <revolution/OS/OSError.h>
#include <types.h>

struct Quatf {
    float x, y, z, w;
};

static f32 Unit01[2] = { 0.0f, 1.0f };

extern "C" {
void fn_8003DEE0(Vec3f* out, const Vec3f* in);
void fn_8003E6DC(const Matrix* mtx, Vec3f* scale);
void fn_8003ECA0(Matrix* mtx, float x, float y, float z);
void fn_8003F9A8(const Quatf* a, const Quatf* b, Quatf* out);
}

#pragma scheduling off
void Matrix::setIdentity() {
    register Matrix* self = this;
    register f32 zero = 0.0f;
    register f32 one = 1.0f;
    register f32 rowA, rowB;
    asm {
        ps_merge00 rowA, one, zero
        ps_merge00 rowB, zero, one
        psq_st rowA, 0(self), 0, 0
        psq_st zero, 8(self), 0, 0
        psq_st rowB, 16(self), 0, 0
        psq_st zero, 24(self), 0, 0
        psq_st zero, 32(self), 0, 0
        psq_st rowA, 40(self), 0, 0
    }
}
#pragma scheduling reset

extern "C" asm void fn_8003E388(const Matrix* src, Matrix* dst) {
    nofralloc
    psq_l f0, 0x0(r3), 0, 0
    psq_l f1, 0x8(r3), 0, 0
    psq_l f2, 0x10(r3), 0, 0
    psq_l f3, 0x18(r3), 0, 0
    psq_l f4, 0x20(r3), 0, 0
    psq_l f5, 0x28(r3), 0, 0
    psq_st f0, 0x0(r4), 0, 0
    psq_st f1, 0x8(r4), 0, 0
    psq_st f2, 0x10(r4), 0, 0
    psq_st f3, 0x18(r4), 0, 0
    psq_st f4, 0x20(r4), 0, 0
    psq_st f5, 0x28(r4), 0, 0
    blr
}

// rotate-only transform of a vector (no translation)
#pragma scheduling off
extern "C" void fn_8003E3BC(register const Matrix* mtx, register const Vec3f* src, register Vec3f* dst) {
    register f32 zero = 0.0f;
    register f32 vxy, vz, a0, a1, a2, c0, c1;
    asm {
        psq_l vz, 0x8(src), 1, 0
        psq_l vxy, 0x0(src), 0, 0
        psq_l a0, 0x0(mtx), 0, 0
        ps_merge00 vz, vz, zero
        psq_l a1, 0x10(mtx), 0, 0
        psq_l a2, 0x20(mtx), 0, 0
        ps_mul a0, a0, vxy
        psq_l c0, 0x8(mtx), 0, 0
        ps_mul a1, a1, vxy
        ps_mul a2, a2, vxy
        psq_l c1, 0x18(mtx), 0, 0
        psq_l vxy, 0x28(mtx), 0, 0
        ps_madd a0, c0, vz, a0
        ps_madd a1, c1, vz, a1
        ps_madd a2, vxy, vz, a2
        ps_sum0 a0, a0, a0, a0
        ps_sum0 a1, a1, a1, a1
        ps_sum0 a2, a2, vz, a2
        psq_st a0, 0x0(dst), 1, 0
        psq_st a1, 0x4(dst), 1, 0
        psq_st a2, 0x8(dst), 1, 0
    }
}
#pragma scheduling reset

asm void Matrix::mulPos(const Vec3f* pos, Vec3f* out) {
    nofralloc
    psq_l f0, 0x0(r4), 0, 0
    psq_l f2, 0x0(r3), 0, 0
    psq_l f4, 0x20(r3), 0, 0
    psq_l f3, 0x10(r3), 0, 0
    ps_mul f2, f2, f0
    ps_mul f4, f4, f0
    psq_l f1, 0x8(r4), 1, 0
    ps_mul f3, f3, f0
    psq_l f5, 0x8(r3), 0, 0
    psq_l f0, 0x18(r3), 0, 0
    psq_l f6, 0x28(r3), 0, 0
    ps_madd f2, f5, f1, f2
    ps_madd f3, f0, f1, f3
    ps_madd f4, f6, f1, f4
    ps_sum0 f2, f2, f2, f2
    ps_sum0 f3, f3, f3, f3
    ps_sum0 f4, f4, f1, f4
    psq_st f2, 0x0(r5), 1, 0
    psq_st f3, 0x4(r5), 1, 0
    psq_st f4, 0x8(r5), 1, 0
    blr
}

extern "C" asm void fn_8003E46C(const Matrix* mtx, const Vec3f* src, Vec3f* dst) {
    nofralloc
    psq_l f0, 0x0(r4), 0, 0
    psq_l f1, 0x8(r4), 1, 0
    psq_l f2, 0x0(r3), 0, 0
    psq_l f3, 0x10(r3), 0, 0
    psq_l f4, 0x20(r3), 0, 0
    ps_mul f2, f2, f0
    ps_mul f3, f3, f0
    ps_mul f4, f4, f0
    psq_l f0, 0x8(r3), 0, 0
    psq_l f5, 0x18(r3), 0, 0
    psq_l f6, 0x28(r3), 0, 0
    ps_madd f2, f0, f1, f2
    ps_madd f3, f5, f1, f3
    ps_madd f4, f6, f1, f4
    ps_sum0 f2, f2, f2, f2
    ps_sum0 f3, f3, f3, f3
    ps_sum0 f4, f4, f1, f4
    psq_st f2, 0x0(r5), 1, 0
    psq_st f3, 0x4(r5), 1, 0
    psq_st f4, 0x8(r5), 0, 0
    blr
}

// quaternion -> rotation matrix
extern "C" void fn_8003E4C0(Matrix* mtx, const Quatf* q) {
    float x = q->x;
    float y = q->y;
    float z = q->z;
    float w = q->w;
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    float yy = y * y;
    float zz = z * z;
    mtx->setIdentity();
    mtx->m[0][0] = 1.0f - 2.0f * (yy + zz);
    mtx->m[0][1] = 2.0f * (xy - wz);
    mtx->m[0][2] = 2.0f * (xz + wy);
    mtx->m[1][0] = 2.0f * (xy + wz);
    mtx->m[1][1] = 1.0f - 2.0f * (xx + zz);
    mtx->m[1][2] = 2.0f * (yz - wx);
    mtx->m[2][0] = 2.0f * (xz - wy);
    mtx->m[2][1] = 2.0f * (yz + wx);
    mtx->m[2][2] = 1.0f - 2.0f * (xx + yy);
}

// normalize the three basis vectors (columns)
extern "C" void fn_8003E5B4(Matrix* mtx) {
    float s0 = rsqrtf(mtx->m[2][0] * mtx->m[2][0] + (mtx->m[0][0] * mtx->m[0][0] + mtx->m[1][0] * mtx->m[1][0]));
    float s1 = rsqrtf(mtx->m[2][1] * mtx->m[2][1] + (mtx->m[0][1] * mtx->m[0][1] + mtx->m[1][1] * mtx->m[1][1]));
    float s2 = rsqrtf(mtx->m[2][2] * mtx->m[2][2] + (mtx->m[0][2] * mtx->m[0][2] + mtx->m[1][2] * mtx->m[1][2]));
    mtx->m[0][0] = mtx->m[0][0] * s0;
    mtx->m[1][0] = mtx->m[1][0] * s0;
    mtx->m[2][0] = mtx->m[2][0] * s0;
    mtx->m[0][1] = mtx->m[0][1] * s1;
    mtx->m[1][1] = mtx->m[1][1] * s1;
    mtx->m[2][1] = mtx->m[2][1] * s1;
    mtx->m[0][2] = mtx->m[0][2] * s2;
    mtx->m[1][2] = mtx->m[1][2] * s2;
    mtx->m[2][2] = mtx->m[2][2] * s2;
}

// extract per-axis scale
extern "C" void fn_8003E6DC(const Matrix* mtx, Vec3f* scale) {
    float sx = mtx->m[2][0] * mtx->m[2][0] + (mtx->m[0][0] * mtx->m[0][0] + mtx->m[1][0] * mtx->m[1][0]);
    float sy = mtx->m[2][1] * mtx->m[2][1] + (mtx->m[0][1] * mtx->m[0][1] + mtx->m[1][1] * mtx->m[1][1]);
    float sz = mtx->m[2][2] * mtx->m[2][2] + (mtx->m[0][2] * mtx->m[0][2] + mtx->m[1][2] * mtx->m[1][2]);
    if (sx < 0.0f) {
        OSReport("Warning Scale x = %f", sx);
        sx = 0.0f;
    }
    if (sy < 0.0f) {
        OSReport("Warning Scale y = %f", sy);
        sy = 0.0f;
    }
    if (sz < 0.0f) {
        OSReport("Warning Scale z = %f", sz);
        sz = 0.0f;
    }
    scale->m_x = mtSqrtf(sx);
    scale->m_y = mtSqrtf(sy);
    scale->m_z = mtSqrtf(sz);
}

// scale the rows of the matrix by a vector
extern "C" asm void fn_8003E828(const Matrix* mtx, const Vec3f* scale, Matrix* out) {
    nofralloc
    psq_l f0, 0x0(r4), 0, 0
    psq_l f2, 0x0(r3), 0, 0
    psq_l f3, 0x10(r3), 0, 0
    psq_l f4, 0x20(r3), 0, 0
    ps_mul f2, f2, f0
    ps_mul f3, f3, f0
    psq_l f1, 0x8(r4), 1, 0
    ps_mul f4, f4, f0
    psq_st f2, 0x0(r5), 0, 0
    psq_l f2, 0x8(r3), 0, 0
    psq_st f3, 0x10(r5), 0, 0
    psq_l f3, 0x18(r3), 0, 0
    ps_mul f2, f2, f1
    psq_st f4, 0x20(r5), 0, 0
    psq_l f4, 0x28(r3), 0, 0
    ps_mul f3, f3, f1
    psq_st f2, 0x8(r5), 0, 0
    ps_mul f4, f4, f1
    psq_st f3, 0x18(r5), 0, 0
    psq_st f4, 0x28(r5), 0, 0
    blr
}

extern "C" void fn_8003E87C(Matrix* mtx, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    mtx->setIdentity();
    mtx->m[1][1] = c;
    mtx->m[1][2] = -s;
    mtx->m[2][1] = s;
    mtx->m[2][2] = c;
}

extern "C" void fn_8003E918(Matrix* mtx, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    mtx->setIdentity();
    mtx->m[0][0] = c;
    mtx->m[0][2] = s;
    mtx->m[2][0] = -s;
    mtx->m[2][2] = c;
}

extern "C" void fn_8003E9B4(Matrix* mtx, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    mtx->setIdentity();
    mtx->m[0][0] = c;
    mtx->m[0][1] = -s;
    mtx->m[1][0] = s;
    mtx->m[1][1] = c;
}

extern "C" void fn_8003EA50(Matrix* mtx, const Vec3f* angles) {
    Matrix rot(true);
    fn_8003ECA0(&rot, angles->m_x, angles->m_y, angles->m_z);
    mtx->mul(&rot, mtx);
}

extern "C" void fn_8003EA9C(Matrix* mtx, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    Matrix rot;
    rot.m[1][1] = c;
    rot.m[1][2] = -s;
    rot.m[2][1] = s;
    rot.m[2][2] = c;
    mtx->mul(&rot, mtx);
}

void Matrix::rotY(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    Matrix rot;
    rot.m[0][0] = c;
    rot.m[0][2] = s;
    rot.m[2][0] = -s;
    rot.m[2][2] = c;
    this->mul(&rot, this);
}

extern "C" void fn_8003EBF4(Matrix* mtx, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    Matrix rot;
    rot.m[0][0] = c;
    rot.m[0][1] = -s;
    rot.m[1][0] = s;
    rot.m[1][1] = c;
    mtx->mul(&rot, mtx);
}

// euler angles -> rotation matrix
extern "C" void fn_8003ECA0(Matrix* mtx, float x, float y, float z) {
    float sx, cx, sy, cy, sz, cz;
    mtSinCosf(x, &sx, &cx);
    mtSinCosf(y, &sy, &cy);
    mtSinCosf(z, &sz, &cz);
    mtx->m[0][0] = cy * cz;
    mtx->m[1][0] = cy * sz;
    mtx->m[2][0] = -sy;
    mtx->m[0][1] = cz * (sx * sy) - cx * sz;
    mtx->m[1][1] = sz * (sx * sy) + cx * cz;
    mtx->m[2][1] = sx * cy;
    mtx->m[0][2] = cz * (cx * sy) + sx * sz;
    mtx->m[1][2] = sz * (cx * sy) - sx * cz;
    mtx->m[2][2] = cx * cy;
    mtx->m[0][3] = 0.0f;
    mtx->m[1][3] = 0.0f;
    mtx->m[2][3] = 0.0f;
}

void Matrix::getRotate(Vec3f* outRot) {
    Matrix tmp(this);
    fn_8003E5B4(&tmp);
    float len = mtSqrtf(tmp.m[0][0] * tmp.m[0][0] + tmp.m[1][0] * tmp.m[1][0]);
    if (len > 0.0001f) {
        outRot->m_x = atan2(tmp.m[2][1], tmp.m[2][2]);
        outRot->m_y = atan2(-tmp.m[2][0], len);
        outRot->m_z = atan2(tmp.m[1][0], tmp.m[0][0]);
    } else {
        outRot->m_x = atan2(-tmp.m[1][2], tmp.m[1][1]);
        outRot->m_y = atan2(-tmp.m[2][0], len);
        outRot->m_z = 0.0f;
    }
}

#pragma scheduling off
extern "C" void fn_8003F03C(Matrix* mtx, float x, float y, float z) {
    mtx->setIdentity();
    mtx->m[0][3] = x;
    mtx->m[1][3] = y;
    mtx->m[2][3] = z;
}
#pragma scheduling reset

extern "C" void fn_8003F074(Matrix* mtx, float x, float y, float z) {
    mtx->m[0][3] = mtx->m[0][3] + (mtx->m[0][2] * z + (mtx->m[0][0] * x + mtx->m[0][1] * y));
    mtx->m[1][3] = mtx->m[1][3] + (mtx->m[1][2] * z + (mtx->m[1][0] * x + mtx->m[1][1] * y));
    mtx->m[2][3] = mtx->m[2][3] + (mtx->m[2][2] * z + (mtx->m[2][0] * x + mtx->m[2][1] * y));
}

void Matrix::setSRT(const Vec3f& scale, const Vec3f& rot, const Vec3f& trans) {
    float sx, cx, sy, cy, sz, cz;
    mtSinCosf(rot.m_x, &sx, &cx);
    mtSinCosf(rot.m_y, &sy, &cy);
    mtSinCosf(rot.m_z, &sz, &cz);
    m[0][0] = scale.m_x * (cy * cz);
    m[1][0] = scale.m_x * (cy * sz);
    m[2][0] = -sy * scale.m_x;
    m[0][1] = scale.m_y * (cz * (sx * sy) - cx * sz);
    m[1][1] = scale.m_y * (sz * (sx * sy) + cx * cz);
    m[2][1] = scale.m_y * (sx * cy);
    m[0][2] = scale.m_z * (cz * (cx * sy) + sx * sz);
    m[1][2] = scale.m_z * (sz * (cx * sy) - sx * cz);
    m[2][2] = scale.m_z * (cx * cy);
    m[0][3] = trans.m_x;
    m[1][3] = trans.m_y;
    m[2][3] = trans.m_z;
}

// decompose into scale, rotation, translation
extern "C" void fn_8003F2AC(const Matrix* mtx, Vec3f* scale, Vec3f* rot, Vec3f* trans) {
    trans->m_x = mtx->m[0][3];
    trans->m_y = mtx->m[1][3];
    trans->m_z = mtx->m[2][3];
    fn_8003E6DC(mtx, scale);
    Matrix tmp((Matrix*)mtx);
    fn_8003E5B4(&tmp);
    float len = mtSqrtf(tmp.m[0][0] * tmp.m[0][0] + tmp.m[1][0] * tmp.m[1][0]);
    if (len > 0.0001f) {
        rot->m_x = atan2(tmp.m[2][1], tmp.m[2][2]);
        rot->m_y = atan2(-tmp.m[2][0], len);
        rot->m_z = atan2(tmp.m[1][0], tmp.m[0][0]);
    } else {
        rot->m_x = atan2(-tmp.m[1][2], tmp.m[1][1]);
        rot->m_y = atan2(-tmp.m[2][0], len);
        rot->m_z = 0.0f;
    }
}

asm void Matrix::mul(const Matrix* mulMatrix, Matrix* outMatrix) const {
    nofralloc
    psq_l f0, 0x0(r3), 0, 0
    la r6, Unit01(r13)
    psq_l f6, 0x0(r4), 0, 0
    psq_l f2, 0x10(r3), 0, 0
    psq_l f4, 0x20(r3), 0, 0
    ps_muls0 f9, f6, f0
    psq_l f7, 0x10(r4), 0, 0
    ps_muls0 f10, f6, f2
    ps_muls0 f11, f6, f4
    psq_l f8, 0x20(r4), 0, 0
    ps_madds1 f9, f7, f0, f9
    psq_l f1, 0x8(r3), 0, 0
    ps_madds1 f10, f7, f2, f10
    ps_madds1 f11, f7, f4, f11
    psq_l f3, 0x18(r3), 0, 0
    ps_madds0 f9, f8, f1, f9
    psq_l f5, 0x28(r3), 0, 0
    ps_madds0 f10, f8, f3, f10
    psq_l f6, 0x8(r4), 0, 0
    ps_madds0 f11, f8, f5, f11
    psq_st f9, 0x0(r5), 0, 0
    ps_muls0 f9, f6, f0
    psq_l f7, 0x18(r4), 0, 0
    psq_st f10, 0x10(r5), 0, 0
    ps_muls0 f10, f6, f2
    ps_madds1 f9, f7, f0, f9
    psq_l f8, 0x28(r4), 0, 0
    psq_st f11, 0x20(r5), 0, 0
    ps_muls0 f11, f6, f4
    ps_madds1 f10, f7, f2, f10
    ps_madds0 f9, f8, f1, f9
    ps_madds1 f11, f7, f4, f11
    psq_l f0, 0x0(r6), 0, 0
    ps_madds0 f10, f8, f3, f10
    ps_madds1 f9, f0, f1, f9
    ps_madds0 f11, f8, f5, f11
    ps_madds1 f10, f0, f3, f10
    psq_st f9, 0x8(r5), 0, 0
    ps_madds1 f11, f0, f5, f11
    psq_st f10, 0x18(r5), 0, 0
    psq_st f11, 0x28(r5), 0, 0
    blr
}

void Matrix::inverse(Matrix* out) const {
    float det = m[2][2] * (m[0][0] * m[1][1]) + m[2][0] * (m[0][1] * m[1][2]) + m[2][1] * (m[0][2] * m[1][0])
              - m[0][2] * (m[2][0] * m[1][1]) - m[2][2] * (m[1][0] * m[0][1]) - m[1][2] * (m[0][0] * m[2][1]);
    if (fabsf(det) < 1.1920929e-7f) {
        out->setIdentity();
        return;
    }
    float invDet = 1.0f / det;
    Matrix tmp(true);
    const Matrix* src = this;
    if (this == out) {
        tmp = *this;
        src = &tmp;
    }
    out->m[0][0] = invDet * (src->m[1][1] * src->m[2][2] - src->m[2][1] * src->m[1][2]);
    out->m[0][1] = invDet * -(src->m[0][1] * src->m[2][2] - src->m[2][1] * src->m[0][2]);
    out->m[0][2] = invDet * (src->m[0][1] * src->m[1][2] - src->m[1][1] * src->m[0][2]);
    out->m[1][0] = invDet * -(src->m[1][0] * src->m[2][2] - src->m[2][0] * src->m[1][2]);
    out->m[1][1] = invDet * (src->m[0][0] * src->m[2][2] - src->m[2][0] * src->m[0][2]);
    out->m[1][2] = invDet * -(src->m[0][0] * src->m[1][2] - src->m[1][0] * src->m[0][2]);
    out->m[2][0] = invDet * (src->m[1][0] * src->m[2][1] - src->m[2][0] * src->m[1][1]);
    out->m[2][1] = invDet * -(src->m[0][0] * src->m[2][1] - src->m[2][0] * src->m[0][1]);
    out->m[2][2] = invDet * (src->m[0][0] * src->m[1][1] - src->m[1][0] * src->m[0][1]);
    out->m[0][3] = -out->m[0][0] * m[0][3] - out->m[0][1] * m[1][3] - out->m[0][2] * m[2][3];
    out->m[1][3] = -out->m[1][0] * m[0][3] - out->m[1][1] * m[1][3] - out->m[1][2] * m[2][3];
    out->m[2][3] = -out->m[2][0] * m[0][3] - out->m[2][1] * m[1][3] - out->m[2][2] * m[2][3];
}

extern "C" asm void fn_8003F898(const float* src, float* dst) {
    nofralloc
    psq_l f0, 0x0(r3), 0, 0
    psq_l f1, 0x10(r3), 0, 0
    ps_merge00 f2, f0, f1
    ps_merge11 f3, f0, f1
    psq_l f0, 0x8(r3), 0, 0
    psq_l f1, 0x18(r3), 0, 0
    psq_st f2, 0x0(r4), 0, 0
    ps_merge00 f2, f0, f1
    psq_st f3, 0x10(r4), 0, 0
    ps_merge11 f3, f0, f1
    psq_l f0, 0x20(r3), 0, 0
    psq_l f1, 0x30(r3), 0, 0
    psq_st f2, 0x20(r4), 0, 0
    ps_merge00 f2, f0, f1
    psq_st f3, 0x30(r4), 0, 0
    ps_merge11 f3, f0, f1
    psq_l f0, 0x28(r3), 0, 0
    psq_l f1, 0x38(r3), 0, 0
    psq_st f2, 0x8(r4), 0, 0
    ps_merge00 f2, f0, f1
    psq_st f3, 0x18(r4), 0, 0
    ps_merge11 f3, f0, f1
    psq_st f2, 0x28(r4), 0, 0
    psq_st f3, 0x38(r4), 0, 0
    blr
}

// quaternion from axis and angle
extern "C" void fn_8003F8FC(Quatf* out, float angle, const Vec3f* axis) {
    float s = sin(0.5f * angle);
    float c = cos(0.5f * angle);
    Vec3f n;
    fn_8003DEE0(&n, axis);
    out->x = n.m_x * s;
    out->y = n.m_y * s;
    out->w = c;
    out->z = n.m_z * s;
}

extern "C" asm void fn_8003F9A8(const Quatf* a, const Quatf* b, Quatf* out) {
    nofralloc
    psq_l f2, 0x0(r3), 0, 0
    psq_l f4, 0x0(r4), 0, 0
    psq_l f3, 0x8(r3), 0, 0
    psq_l f5, 0x8(r4), 0, 0
    ps_muls1 f11, f4, f2
    ps_muls1 f6, f4, f3
    ps_muls1 f7, f5, f3
    ps_muls1 f10, f5, f2
    ps_muls0 f8, f5, f2
    ps_muls0 f12, f4, f3
    ps_muls0 f9, f4, f2
    ps_muls0 f13, f5, f3
    ps_add f10, f6, f10
    ps_sub f11, f7, f11
    ps_sub f12, f8, f12
    ps_merge10 f4, f10, f10
    ps_add f13, f9, f13
    ps_merge10 f5, f11, f11
    ps_sum0 f2, f10, f10, f12
    ps_sum0 f3, f11, f11, f13
    ps_sub f4, f4, f12
    ps_sub f5, f5, f13
    psq_st f2, 0x0(r5), 1, 0
    psq_st f3, 0x8(r5), 1, 0
    psq_st f4, 0x4(r5), 1, 0
    psq_st f5, 0xc(r5), 1, 0
    blr
}

// rotate a vector by a quaternion
extern "C" void fn_8003FA14(const Quatf* q, const Vec3f* v, Vec3f* out) {
    Quatf conj;
    conj.x = -q->x;
    conj.y = -q->y;
    conj.z = -q->z;
    conj.w = q->w;
    Quatf vq;
    vq.x = v->m_x;
    vq.y = v->m_y;
    vq.z = v->m_z;
    vq.w = 0.0f;
    Quatf tmp;
    fn_8003F9A8(q, &vq, &tmp);
    fn_8003F9A8(&tmp, &conj, &tmp);
    out->m_x = tmp.x;
    out->m_y = tmp.y;
    out->m_z = tmp.z;
}
