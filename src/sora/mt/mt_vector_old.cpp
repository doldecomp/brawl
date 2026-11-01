#include <cmath>
#include <mt/mt_vector.h>
#include <mt/mt_vector_old.h>
#include <types.h>

Vec3f* vlRotateFix(Vec3f* v, vlRotateAxis::Enum axis, float theta) {
    float rotX, rotY, rotZ;
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);
    switch (axis) {
        case vlRotateAxis::X:
            rotX = v->m_x;
            rotY = v->m_y * cosTheta - v->m_z * sinTheta;
            rotZ = v->m_y * sinTheta + v->m_z * cosTheta;
            break;
        case vlRotateAxis::Y:
            rotX = v->m_x * cosTheta + v->m_z * sinTheta;
            rotY = v->m_y;
            rotZ = v->m_z * cosTheta - v->m_x * sinTheta;
            break;
        case vlRotateAxis::Z:
            rotX = v->m_x * cosTheta - v->m_y * sinTheta;
            rotY = v->m_x * sinTheta + v->m_y * cosTheta;
            rotZ = v->m_z;
            break;
        default:
            break;
    }
    v->m_x = rotX;
    v->m_y = rotY;
    v->m_z = rotZ;
    return v;
}
