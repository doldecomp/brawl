#include <math.h>
#include <mt/mt_common.h>
#include <mt/mt_matrix.h>
#include <mt/mt_trig.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_types.h>
#include <revolution/OS/OSError.h>
#include <types.h>

static float s_unit01[] = {0.0f, 1.0f};

void Matrix::setIdentity() {
#ifdef MATCHING
    register Matrix* mtx = this;
    register float zero = 0.0f;
    register float one = 1.0f;
    register float oneZero, zeroOne;
    asm volatile {
        ps_merge00 oneZero, one, zero
        ps_merge00 zeroOne, zero, one
        psq_st     oneZero, 0x0(mtx), 0, 0
        psq_st     zero, 0x8(mtx), 0, 0
        psq_st     zeroOne, 0x10(mtx), 0, 0
        psq_st     zero, 0x18(mtx), 0, 0
        psq_st     zero, 0x20(mtx), 0, 0
        psq_st     oneZero, 0x28(mtx), 0, 0
    }
#else
    *this = Matrix(1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f);
#endif
}

void Matrix::copy(register Matrix* outMatrix) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register float row0a, row0b, row1a, row1b, row2a, row2b;
    asm {
        psq_l  row0a, 0x0(mtx), 0, 0
        psq_l  row0b, 0x8(mtx), 0, 0
        psq_l  row1a, 0x10(mtx), 0, 0
        psq_l  row1b, 0x18(mtx), 0, 0
        psq_l  row2a, 0x20(mtx), 0, 0
        psq_l  row2b, 0x28(mtx), 0, 0
        psq_st row0a, 0x0(outMatrix), 0, 0
        psq_st row0b, 0x8(outMatrix), 0, 0
        psq_st row1a, 0x10(outMatrix), 0, 0
        psq_st row1b, 0x18(outMatrix), 0, 0
        psq_st row2a, 0x20(outMatrix), 0, 0
        psq_st row2b, 0x28(outMatrix), 0, 0
    }
#else
    *outMatrix = *this;
#endif
}

void Matrix::mulVec(register const Vec3f* vec, register Vec3f* outVec) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register float zero = 0.0f;
    register float xy, z0, row0a, row1a, row2a, row0b, row2b, row1b;
    asm volatile {
        psq_l      z0, 0x8(vec), 1, 0
        psq_l      xy, 0x0(vec), 0, 0
        psq_l      row0a, 0x0(mtx), 0, 0
        ps_merge00 z0, z0, zero
        psq_l      row1a, 0x10(mtx), 0, 0
        psq_l      row2a, 0x20(mtx), 0, 0
        ps_mul     row0a, row0a, xy
        psq_l      row0b, 0x8(mtx), 0, 0
        ps_mul     row1a, row1a, xy
        ps_mul     row2a, row2a, xy
        psq_l      row1b, 0x18(mtx), 0, 0
        psq_l      row2b, 0x28(mtx), 0, 0
        ps_madd    row0a, row0b, z0, row0a
        ps_madd    row1a, row1b, z0, row1a
        ps_madd    row2a, row2b, z0, row2a
        ps_sum0    row0a, row0a, row0a, row0a
        ps_sum0    row1a, row1a, row1a, row1a
        ps_sum0    row2a, row2a, z0, row2a
        psq_st     row0a, 0x0(outVec), 1, 0
        psq_st     row1a, 0x4(outVec), 1, 0
        psq_st     row2a, 0x8(outVec), 1, 0
    }
#else
    float x = vec->m_x;
    float y = vec->m_y;
    float z = vec->m_z;
    outVec->m_x = m[0][0] * x + m[0][1] * y + m[0][2] * z;
    outVec->m_y = m[1][0] * x + m[1][1] * y + m[1][2] * z;
    outVec->m_z = m[2][0] * x + m[2][1] * y + m[2][2] * z;
#endif
}

void Matrix::mulPos(register const Vec3f* pos, register Vec3f* outVec) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register float xy, z1, row0a, row1a, row2a, row1b, row0b, row2b;
    asm {
        psq_l   xy, 0x0(pos), 0, 0
        psq_l   row0a, 0x0(mtx), 0, 0
        psq_l   row2a, 0x20(mtx), 0, 0
        psq_l   row1a, 0x10(mtx), 0, 0
        ps_mul  row0a, row0a, xy
        ps_mul  row2a, row2a, xy
        psq_l   z1, 0x8(pos), 1, 0
        ps_mul  row1a, row1a, xy
        psq_l   row0b, 0x8(mtx), 0, 0
        psq_l   row1b, 0x18(mtx), 0, 0
        psq_l   row2b, 0x28(mtx), 0, 0
        ps_madd row0a, row0b, z1, row0a
        ps_madd row1a, row1b, z1, row1a
        ps_madd row2a, row2b, z1, row2a
        ps_sum0 row0a, row0a, row0a, row0a
        ps_sum0 row1a, row1a, row1a, row1a
        ps_sum0 row2a, row2a, z1, row2a
        psq_st  row0a, 0x0(outVec), 1, 0
        psq_st  row1a, 0x4(outVec), 1, 0
        psq_st  row2a, 0x8(outVec), 1, 0
    }
#else
    float x = pos->m_x;
    float y = pos->m_y;
    float z = pos->m_z;
    outVec->m_x = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    outVec->m_y = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    outVec->m_z = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
#endif
}

void Matrix::mulPos(register const Vec3f* pos, register float* outVec) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register float xy, z1, row0a, row1a, row2a, row0b, row1b, row2b;
    asm volatile {
        psq_l   xy, 0x0(pos), 0, 0
        psq_l   z1, 0x8(pos), 1, 0
        psq_l   row0a, 0x0(mtx), 0, 0
        psq_l   row1a, 0x10(mtx), 0, 0
        psq_l   row2a, 0x20(mtx), 0, 0
        ps_mul  row0a, row0a, xy
        ps_mul  row1a, row1a, xy
        ps_mul  row2a, row2a, xy
        psq_l   row0b, 0x8(mtx), 0, 0
        psq_l   row1b, 0x18(mtx), 0, 0
        psq_l   row2b, 0x28(mtx), 0, 0
        ps_madd row0a, row0b, z1, row0a
        ps_madd row1a, row1b, z1, row1a
        ps_madd row2a, row2b, z1, row2a
        ps_sum0 row0a, row0a, row0a, row0a
        ps_sum0 row1a, row1a, row1a, row1a
        ps_sum0 row2a, row2a, z1, row2a
        psq_st  row0a, 0x0(outVec), 1, 0
        psq_st  row1a, 0x4(outVec), 1, 0
        psq_st  row2a, 0x8(outVec), 0, 0
    }
#else
    float x = pos->m_x;
    float y = pos->m_y;
    float z = pos->m_z;
    outVec[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    outVec[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    outVec[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    outVec[3] = 1.0f;
#endif
}

void Matrix::setQuat(const nw4r::math::QUAT* quat) {
    float x = quat->x;
    float y = quat->y;
    float z = quat->z;
    float w = quat->w;
    float xz = x * z;
    float yz = y * z;
    float xy = x * y;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    setIdentity();
    m[0][0] = 1.0f - 2.0f * (yy + zz);
    m[0][1] = 2.0f * (xy - wz);
    m[0][2] = 2.0f * (xz + wy);
    m[1][0] = 2.0f * (xy + wz);
    m[1][1] = 1.0f - 2.0f * (xx + zz);
    m[1][2] = 2.0f * (yz - wx);
    m[2][0] = 2.0f * (xz - wy);
    m[2][1] = 2.0f * (yz + wx);
    m[2][2] = 1.0f - 2.0f * (xx + yy);
}

void Matrix::normalize() {
    float invX = rsqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
    float invY = rsqrtf(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
    float invZ = rsqrtf(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]);
    m[0][0] *= invX;
    m[1][0] *= invX;
    m[2][0] *= invX;
    m[0][1] *= invY;
    m[1][1] *= invY;
    m[2][1] *= invY;
    m[0][2] *= invZ;
    m[1][2] *= invZ;
    m[2][2] *= invZ;
}

void Matrix::getScale(Vec3f* outScale) const {
    float x = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
    float y = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
    float z = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
    if (x < 0.0f) {
        OSReport("Warning Scale x = %f", x);
        x = 0.0f;
    }
    if (y < 0.0f) {
        OSReport("Warning Scale y = %f", y);
        y = 0.0f;
    }
    if (z < 0.0f) {
        OSReport("Warning Scale z = %f", z);
        z = 0.0f;
    }
    outScale->m_x = mtSqrtf(x);
    outScale->m_y = mtSqrtf(y);
    outScale->m_z = mtSqrtf(z);
}

void Matrix::scale(register const Vec3f* scale, register Matrix* outMatrix) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register float xy, z1, row0, row1, row2;
    asm {
        psq_l  xy, 0x0(scale), 0, 0
        psq_l  row0, 0x0(mtx), 0, 0
        psq_l  row1, 0x10(mtx), 0, 0
        psq_l  row2, 0x20(mtx), 0, 0
        ps_mul row0, row0, xy
        ps_mul row1, row1, xy
        psq_l  z1, 0x8(scale), 1, 0
        ps_mul row2, row2, xy
        psq_st row0, 0x0(outMatrix), 0, 0
        psq_l  row0, 0x8(mtx), 0, 0
        psq_st row1, 0x10(outMatrix), 0, 0
        psq_l  row1, 0x18(mtx), 0, 0
        ps_mul row0, row0, z1
        psq_st row2, 0x20(outMatrix), 0, 0
        psq_l  row2, 0x28(mtx), 0, 0
        ps_mul row1, row1, z1
        psq_st row0, 0x8(outMatrix), 0, 0
        ps_mul row2, row2, z1
        psq_st row1, 0x18(outMatrix), 0, 0
        psq_st row2, 0x28(outMatrix), 0, 0
    }
#else
    for (int i = 0; i < 3; i++) {
        outMatrix->m[i][0] = m[i][0] * scale->m_x;
        outMatrix->m[i][1] = m[i][1] * scale->m_y;
        outMatrix->m[i][2] = m[i][2] * scale->m_z;
        outMatrix->m[i][3] = m[i][3];
    }
#endif
}

void Matrix::setRotX(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    setIdentity();
    m[1][1] = c;
    m[1][2] = -s;
    m[2][1] = s;
    m[2][2] = c;
}

void Matrix::setRotY(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    setIdentity();
    m[0][0] = c;
    m[0][2] = s;
    m[2][0] = -s;
    m[2][2] = c;
}

void Matrix::setRotZ(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    setIdentity();
    m[0][0] = c;
    m[0][1] = -s;
    m[1][0] = s;
    m[1][1] = c;
}

void Matrix::rotXYZ(const Vec3f* rot) {
    Matrix mtx(true);
    mtx.setRotXYZ(rot->m_x, rot->m_y, rot->m_z);
    mul(&mtx, this);
}

void Matrix::rotX(float angle) {
    Matrix mtx(true);
    mtx.setRotX(angle);
    mul(&mtx, this);
}

void Matrix::rotY(float angle) {
    Matrix mtx(true);
    mtx.setRotY(angle);
    mul(&mtx, this);
}

void Matrix::rotZ(float angle) {
    Matrix mtx(true);
    mtx.setRotZ(angle);
    mul(&mtx, this);
}

void Matrix::setRotXYZ(float x, float y, float z) {
    float sinX, sinY, sinZ, cosX, cosY, cosZ;
    mtSinCosf(x, &sinX, &cosX);
    mtSinCosf(y, &sinY, &cosY);
    mtSinCosf(z, &sinZ, &cosZ);
    m[0][0] = cosY * cosZ;
    m[1][0] = cosY * sinZ;
    m[2][0] = -sinY;
    m[0][1] = cosZ * (sinX * sinY) - cosX * sinZ;
    m[1][1] = sinZ * (sinX * sinY) + cosX * cosZ;
    m[2][1] = sinX * cosY;
    m[0][2] = cosZ * (cosX * sinY) + sinX * sinZ;
    m[1][2] = sinZ * (cosX * sinY) - sinX * cosZ;
    m[2][2] = cosX * cosY;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}

void Matrix::getRotate(Vec3f* outRot) const {
    Matrix mtx = *this;
    mtx.normalize();
    float cosY = mtSqrtf(mtx.m[0][0] * mtx.m[0][0] + mtx.m[1][0] * mtx.m[1][0]);
    if (cosY > 0.0001f) {
        outRot->m_x = atan2f(mtx.m[2][1], mtx.m[2][2]);
        outRot->m_y = atan2f(-mtx.m[2][0], cosY);
        outRot->m_z = atan2f(mtx.m[1][0], mtx.m[0][0]);
    } else {
        outRot->m_x = atan2f(-mtx.m[1][2], mtx.m[1][1]);
        outRot->m_y = atan2f(-mtx.m[2][0], cosY);
        outRot->m_z = 0.0f;
    }
}

void Matrix::setTrans(float x, float y, float z) {
    setIdentity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

void Matrix::trans(float x, float y, float z) {
    m[0][3] += m[0][0] * x + m[0][1] * y + m[0][2] * z;
    m[1][3] += m[1][0] * x + m[1][1] * y + m[1][2] * z;
    m[2][3] += m[2][0] * x + m[2][1] * y + m[2][2] * z;
}

void Matrix::setSRT(const Vec3f& scale, const Vec3f& rot, const Vec3f& trans) {
    float sinX, sinY, sinZ, cosX, cosY, cosZ;
    mtSinCosf(rot.m_x, &sinX, &cosX);
    mtSinCosf(rot.m_y, &sinY, &cosY);
    mtSinCosf(rot.m_z, &sinZ, &cosZ);
    m[0][0] = scale.m_x * (cosY * cosZ);
    m[1][0] = scale.m_x * (cosY * sinZ);
    m[2][0] = -sinY * scale.m_x;
    m[0][1] = scale.m_y * (cosZ * (sinX * sinY) - cosX * sinZ);
    m[1][1] = scale.m_y * (sinZ * (sinX * sinY) + cosX * cosZ);
    m[2][1] = scale.m_y * (sinX * cosY);
    m[0][2] = scale.m_z * (cosZ * (cosX * sinY) + sinX * sinZ);
    m[1][2] = scale.m_z * (sinZ * (cosX * sinY) - sinX * cosZ);
    m[2][2] = scale.m_z * (cosX * cosY);
    m[0][3] = trans.m_x;
    m[1][3] = trans.m_y;
    m[2][3] = trans.m_z;
}

void Matrix::getSRT(Vec3f* outScale, Vec3f* outRot, Vec3f* outTrans) const {
    outTrans->set(m[0][3], m[1][3], m[2][3]);
    getScale(outScale);
    getRotate(outRot);
}

void Matrix::mul(register const Matrix* mulMatrix, register Matrix* outMatrix) const {
#ifdef MATCHING
    register const Matrix* mtx = this;
    register const float* unit01 = s_unit01;
    register float a00, a02, a10, a12, a20, a22, b0, b1, b2, ab0, ab1, ab2;
    asm {
        psq_l     a00, 0x0(mtx), 0, 0
        psq_l     b0, 0x0(mulMatrix), 0, 0
        psq_l     a10, 0x10(mtx), 0, 0
        psq_l     a20, 0x20(mtx), 0, 0
        ps_muls0  ab0, b0, a00
        psq_l     b1, 0x10(mulMatrix), 0, 0
        ps_muls0  ab1, b0, a10
        ps_muls0  ab2, b0, a20
        psq_l     b2, 0x20(mulMatrix), 0, 0
        ps_madds1 ab0, b1, a00, ab0
        psq_l     a02, 0x8(mtx), 0, 0
        ps_madds1 ab1, b1, a10, ab1
        ps_madds1 ab2, b1, a20, ab2
        psq_l     a12, 0x18(mtx), 0, 0
        ps_madds0 ab0, b2, a02, ab0
        psq_l     a22, 0x28(mtx), 0, 0
        ps_madds0 ab1, b2, a12, ab1
        psq_l     b0, 0x8(mulMatrix), 0, 0
        ps_madds0 ab2, b2, a22, ab2
        psq_st    ab0, 0x0(outMatrix), 0, 0
        ps_muls0  ab0, b0, a00
        psq_l     b1, 0x18(mulMatrix), 0, 0
        psq_st    ab1, 0x10(outMatrix), 0, 0
        ps_muls0  ab1, b0, a10
        ps_madds1 ab0, b1, a00, ab0
        psq_l     b2, 0x28(mulMatrix), 0, 0
        psq_st    ab2, 0x20(outMatrix), 0, 0
        ps_muls0  ab2, b0, a20
        ps_madds1 ab1, b1, a10, ab1
        ps_madds0 ab0, b2, a02, ab0
        ps_madds1 ab2, b1, a20, ab2
        psq_l     a00, 0x0(unit01), 0, 0
        ps_madds0 ab1, b2, a12, ab1
        ps_madds1 ab0, a00, a02, ab0
        ps_madds0 ab2, b2, a22, ab2
        ps_madds1 ab1, a00, a12, ab1
        psq_st    ab0, 0x8(outMatrix), 0, 0
        ps_madds1 ab2, a00, a22, ab2
        psq_st    ab1, 0x18(outMatrix), 0, 0
        psq_st    ab2, 0x28(outMatrix), 0, 0
    }
#else
    Matrix tmp(true);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tmp.m[i][j] = m[i][0] * mulMatrix->m[0][j] + m[i][1] * mulMatrix->m[1][j] +
                          m[i][2] * mulMatrix->m[2][j];
        }
        tmp.m[i][3] += m[i][3];
    }
    *outMatrix = tmp;
#endif
}

void Matrix::inverse(Matrix* outMatrix) const {
    Matrix tmp(true);
    float det = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
                m[0][2] * m[1][0] * m[2][1] - m[2][0] * m[1][1] * m[0][2] -
                m[1][0] * m[0][1] * m[2][2] - m[0][0] * m[2][1] * m[1][2];
    if ((float)fabs(det) < FLT_EPSILON) {
        outMatrix->setIdentity();
        return;
    }
    float invDet = 1.0f / det;
    const Matrix* src = this;
    if (this == outMatrix) {
        tmp = *this;
        src = &tmp;
    }
    outMatrix->m[0][0] = invDet * (src->m[1][1] * src->m[2][2] - src->m[2][1] * src->m[1][2]);
    outMatrix->m[0][1] = invDet * -(src->m[0][1] * src->m[2][2] - src->m[2][1] * src->m[0][2]);
    outMatrix->m[0][2] = invDet * (src->m[0][1] * src->m[1][2] - src->m[1][1] * src->m[0][2]);
    outMatrix->m[1][0] = invDet * -(src->m[1][0] * src->m[2][2] - src->m[2][0] * src->m[1][2]);
    outMatrix->m[1][1] = invDet * (src->m[0][0] * src->m[2][2] - src->m[2][0] * src->m[0][2]);
    outMatrix->m[1][2] = invDet * -(src->m[0][0] * src->m[1][2] - src->m[1][0] * src->m[0][2]);
    outMatrix->m[2][0] = invDet * (src->m[1][0] * src->m[2][1] - src->m[2][0] * src->m[1][1]);
    outMatrix->m[2][1] = invDet * -(src->m[0][0] * src->m[2][1] - src->m[2][0] * src->m[0][1]);
    outMatrix->m[2][2] = invDet * (src->m[0][0] * src->m[1][1] - src->m[1][0] * src->m[0][1]);
    outMatrix->m[0][3] = -outMatrix->m[0][0] * m[0][3] - outMatrix->m[0][1] * m[1][3] -
                         outMatrix->m[0][2] * m[2][3];
    outMatrix->m[1][3] = -outMatrix->m[1][0] * m[0][3] - outMatrix->m[1][1] * m[1][3] -
                         outMatrix->m[1][2] * m[2][3];
    outMatrix->m[2][3] = -outMatrix->m[2][0] * m[0][3] - outMatrix->m[2][1] * m[1][3] -
                         outMatrix->m[2][2] * m[2][3];
}

void mtMtx44Transpose(register const nw4r::math::MTX44* mtx,
                      register nw4r::math::MTX44* outMtx) {
#ifdef MATCHING
    register float a, b, c, d;
    asm {
        psq_l      a, 0x0(mtx), 0, 0
        psq_l      b, 0x10(mtx), 0, 0
        ps_merge00 c, a, b
        ps_merge11 d, a, b
        psq_l      a, 0x8(mtx), 0, 0
        psq_l      b, 0x18(mtx), 0, 0
        psq_st     c, 0x0(outMtx), 0, 0
        ps_merge00 c, a, b
        psq_st     d, 0x10(outMtx), 0, 0
        ps_merge11 d, a, b
        psq_l      a, 0x20(mtx), 0, 0
        psq_l      b, 0x30(mtx), 0, 0
        psq_st     c, 0x20(outMtx), 0, 0
        ps_merge00 c, a, b
        psq_st     d, 0x30(outMtx), 0, 0
        ps_merge11 d, a, b
        psq_l      a, 0x28(mtx), 0, 0
        psq_l      b, 0x38(mtx), 0, 0
        psq_st     c, 0x8(outMtx), 0, 0
        ps_merge00 c, a, b
        psq_st     d, 0x18(outMtx), 0, 0
        ps_merge11 d, a, b
        psq_st     c, 0x28(outMtx), 0, 0
        psq_st     d, 0x38(outMtx), 0, 0
    }
#else
    nw4r::math::MTX44 tmp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            tmp.m[j][i] = mtx->m[i][j];
    }
    *outMtx = tmp;
#endif
}
