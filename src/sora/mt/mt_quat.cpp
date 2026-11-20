#include <math.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_types.h>
#include <types.h>

void mtQuatRotAxis(nw4r::math::QUAT* out, const Vec3f* axis, float angle) {
    float s = sinf(0.5f * angle);
    float c = cosf(0.5f * angle);
    Vec3f v;
    v.normalize(axis);
    out->x = v.m_x * s;
    out->y = v.m_y * s;
    out->z = v.m_z * s;
    out->w = c;
}

#ifdef MATCHING
asm void mtQuatMul(register const nw4r::math::QUAT* q1, register const nw4r::math::QUAT* q2,
                   register nw4r::math::QUAT* out) {
    nofralloc
    psq_l      f2, 0x0(q1), 0, 0
    psq_l      f4, 0x0(q2), 0, 0
    psq_l      f3, 0x8(q1), 0, 0
    psq_l      f5, 0x8(q2), 0, 0
    ps_muls1   f11, f4, f2
    ps_muls1   f6, f4, f3
    ps_muls1   f7, f5, f3
    ps_muls1   f10, f5, f2
    ps_muls0   f8, f5, f2
    ps_muls0   f12, f4, f3
    ps_muls0   f9, f4, f2
    ps_muls0   f13, f5, f3
    ps_add     f10, f6, f10
    ps_sub     f11, f7, f11
    ps_sub     f12, f8, f12
    ps_merge10 f4, f10, f10
    ps_add     f13, f9, f13
    ps_merge10 f5, f11, f11
    ps_sum0    f2, f10, f10, f12
    ps_sum0    f3, f11, f11, f13
    ps_sub     f4, f4, f12
    ps_sub     f5, f5, f13
    psq_st     f2, 0x0(out), 1, 0
    psq_st     f3, 0x8(out), 1, 0
    psq_st     f4, 0x4(out), 1, 0
    psq_st     f5, 0xc(out), 1, 0
    blr
}
#else
void mtQuatMul(const nw4r::math::QUAT* q1, const nw4r::math::QUAT* q2, nw4r::math::QUAT* out) {
    nw4r::math::QUAT tmp;
    tmp.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
    tmp.y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
    tmp.z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
    tmp.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
    *out = tmp;
}
#endif

void mtQuatRotVec(const nw4r::math::QUAT* q, const Vec3f* v, Vec3f* out) {
    nw4r::math::QUAT conj;
    conj.x = -q->x;
    conj.y = -q->y;
    conj.z = -q->z;
    conj.w = q->w;
    nw4r::math::QUAT vq(v->m_x, v->m_y, v->m_z, 0.0f);
    nw4r::math::QUAT res;
    mtQuatMul(q, &vq, &res);
    mtQuatMul(&res, &conj, &res);
    out->set(res.x, res.y, res.z);
}
