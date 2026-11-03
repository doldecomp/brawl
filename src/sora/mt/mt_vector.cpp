#include <math.h>
#include <mt/mt_common.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_types.h>
#include <types.h>

#define PI 3.1415927f
#define TWO_PI 6.2831855f

static inline float select(register float value, register float geZero, register float ltZero) {
#ifdef MATCHING
    asm {
        fsel ltZero, value, geZero, ltZero
    }
    return ltZero;
#else
    return value >= 0.0f ? geZero : ltZero;
#endif
}

static inline float absf(float x) {
    double absX = fabs(x);
    return absX;
}

static inline bool isZero(float x) {
    bool zero = false;
    if (absf(x) < 0.00001f)
        zero = true;
    return zero;
}

void Vec2f::normalize() {
    float invLength = rsqrtf(lengthSq());
    m_x = m_x * invLength;
    m_y = m_y * invLength;
}

void Vec2f::normalize(const Vec2f* input) {
    float invLength = rsqrtf(input->lengthSq());
    m_x = input->m_x * invLength;
    m_y = input->m_y * invLength;
}

void Vec2f::rot(Vec2f* out, float rot) const {
    bool zero = false;
    if (isZero(m_x) && isZero(m_y))
        zero = true;
    if (zero == true) {
        *out = Vec2f(0.0f, 0.0f);
    } else if (isZero(rot) == true) {
        *out = *this;
    } else {
        nw4r::math::QUAT q;
        Vec3f axis(0.0f, 0.0f, 1.0f);
        Vec3f v(m_x, m_y, 0.0f);
        Vec3f res;
        if (absf(rot) > PI) {
            while (rot > PI)
                rot -= TWO_PI;
            while (rot < -PI)
                rot += TWO_PI;
        }
        mtQuatRotAxis(&q, &axis, rot);
        mtQuatRotVec(&q, &v, &res);
        out->m_x = res.m_x;
        out->m_y = res.m_y;
    }
}

float Vec2f::angle(const Vec2f* v) const {
    float result;
    float lenSq = lengthSq() * v->lengthSq();
    if (lenSq == 0.0f) {
        result = 0.0f;
    } else {
        float dot = m_x * v->m_x + m_y * v->m_y;
        float cos = dot * rsqrtf(lenSq);
        cos = select(cos - -1.0f, cos, -1.0f);
        cos = select(cos - 1.0f, 1.0f, cos);
        result = acosf(cos);
    }
    return result;
}

void Vec3f::normalize() {
    float invLength = rsqrtf(lengthSq());
    m_x = m_x * invLength;
    m_y = m_y * invLength;
    m_z = m_z * invLength;
}

void Vec3f::normalize(const Vec3f* input) {
    float invLength = rsqrtf(input->lengthSq());
    Vec3fScale(this, input, invLength);
}

void Vec3f::rot(const Vec3f* axis, float rot, Vec3f* out) const {
    nw4r::math::QUAT q;
    mtQuatRotAxis(&q, axis, rot);
    mtQuatRotVec(&q, this, out);
}

float Vec3f::angle(const Vec3f* v) const {
    float result;
    float lenSq = lengthSq() * v->lengthSq();
    if (lenSq == 0.0f) {
        result = 0.0f;
    } else {
        float dot = m_x * v->m_x + m_y * v->m_y + m_z * v->m_z;
        float cos = dot * rsqrtf(lenSq);
        cos = select(cos - -1.0f, cos, -1.0f);
        cos = select(cos - 1.0f, 1.0f, cos);
        result = acosf(cos);
    }
    return result;
}

void Vec3f::slerp(const Vec3f* v, Vec3f* out, float t) const {
    float dot = m_x * v->m_x + m_y * v->m_y + m_z * v->m_z;
    if (absf(dot) > 0.9997f) {
        *out = *this * (1.0f - t) + *v * t;
    } else {
        float theta = acosf(absf(dot));
        float s0 = sinf((1.0f - t) * theta);
        float s1 = sinf(t * theta);
        if (dot < 0.0f)
            s0 = -s0;
        *out = (*this * s0 + *v * s1) / sinf(theta);
    }
}
