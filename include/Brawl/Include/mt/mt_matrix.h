#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_types.h>
#include <types.h>

class Matrix : public nw4r::math::MTX34 {
public:
    inline float& operator()(int row, int col) {
        return m[row][col];
    }
    inline float operator()(int row, int col) const { // for const objects
        return m[row][col];
    }

    void setIdentity();
    void setSRT(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3);
    void rotY(float angle);
    inline void rotY(float angle, Matrix* outMatrix) {
        *outMatrix = *this;
        outMatrix->rotY(angle);

    }
    void mul(const Matrix* mulMatrix, Matrix* outMatrix) const;
    void mulPos(const Vec3f* pos, Vec3f* outVec);
    void inverse(Matrix* outMatrix) const;
    void getRotate(Vec3f* outRot);

    inline void getPosition(Vec3f* outPos) {
        outPos->m_x = this->m[0][3];
        outPos->m_y = this->m[1][3];
        outPos->m_z = this->m[2][3];
    }
    inline Vec3f getPosition() {
        Vec3f outPos;
        this->getPosition(&outPos);
        return outPos;
    }

    inline Matrix operator*(Matrix& A) {
        Matrix outMatrix;
        this->mul(&A, &outMatrix);
        return outMatrix;
    }

    inline Matrix(bool noInit = false) {
        if (!noInit) {
            this->setIdentity();
        }
    }
    inline Matrix(Matrix* matrix) {
        *this = *matrix;
    }
    inline Matrix(float f00, float f01, float f02, float f03,
                  float f10, float f11, float f12, float f13,
                  float f20, float f21, float f22, float f23) :
        MTX34(f00, f01, f02, f03, f10, f11, f12, f13, f20, f21, f22, f23) { }
};
static_assert(sizeof(Matrix) == 48, "Class is wrong size!");
