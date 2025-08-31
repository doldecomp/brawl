#include <cmath>
#include <mt/mt_vector.h>
#include <mt/mt_vector_old.h>
#include <types.h>

Vec3f* vlRotateFix(Vec3f* v, vlRotateAxis::Enum axis, float theta) {
    float f3;
    const float sinTheta = sinf(theta);
    float f0;
    const float cosTheta = cosf(theta);
    float f2;
    float rotX;
    float rotY;
    float f1;
    float rotZ;
    switch (axis) {
        case vlRotateAxis::X: {
            f3 = v->m_y * cosTheta;
            f2 = v->m_z * sinTheta;
            f1 = v->m_y * sinTheta;
            f0 = v->m_z * cosTheta;
            rotX = v->m_x;
            rotY = f3 - f2;
            rotZ = f1 + f0;
            break;
        }
        case vlRotateAxis::Y: {
            f0 = v->m_x * sinTheta;
            f1 = v->m_z * cosTheta;
            f2 = v->m_z * sinTheta;
            f3 = v->m_x * cosTheta;
            rotX = f3 + f2;
            rotY = v->m_y;
            rotZ = f1 - f0;
            break;
        }
        case vlRotateAxis::Z: {
            f3 = v->m_x * cosTheta;
            f2 = v->m_y * sinTheta;
            f1 = v->m_x * sinTheta;
            f0 = v->m_y * cosTheta;
            rotX = f3 - f2;
            rotY = f1 + f0;
            rotZ = v->m_z;
            break;
        }
        default:
            break;
    }
    v->m_x = rotX;
    v->m_y = rotY;
    v->m_z = rotZ;
    return v;
}
