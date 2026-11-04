#pragma once

#include <StaticAssert.h>
#include <math.h>
#include <mt/mt_common.h>
#include <types.h>

class Vec2f {
public:
    float m_x;
    float m_y;

    Vec2f() { }
    Vec2f(float x, float y) : m_x(x), m_y(y) { }

    friend Vec2f operator+(const Vec2f& lhs, const Vec2f& rhs) {
        Vec2f res;
        res.m_x = lhs.m_x + rhs.m_x;
        res.m_y = lhs.m_y + rhs.m_y;
        return res;
    }

    friend Vec2f operator-(const Vec2f& lhs, const Vec2f& rhs) {
        Vec2f res;
        res.m_x = lhs.m_x - rhs.m_x;
        res.m_y = lhs.m_y - rhs.m_y;
        return res;
    }

    friend Vec2f operator*(const Vec2f& lhs, const float c) {
        Vec2f res;
        res.m_x = lhs.m_x * c;
        res.m_y = lhs.m_y * c;
        return res;
    }

    friend Vec2f operator/(const Vec2f& lhs, float c) {
        return lhs * (1 / c);
    }

    Vec2f& operator+=(const Vec2f& v) {
        *this = *this + v;
        return *this;
    }

    Vec2f& operator-=(const Vec2f& v) {
        *this = *this - v;
        return *this;
    }

    Vec2f& operator*=(const float c) {
        *this = *this * c;
        return *this;
    }

    float lengthSq() const {
        return m_x * m_x + m_y * m_y;
    }

    float length() {
        float lengthSquared = this->lengthSq();
        if (1.17549e-38 < fabsf(lengthSquared)) {
            return rsqrtf(lengthSquared)*lengthSquared;
        }
        else {
            return 0.0;
        }

    }

    float distance(Vec2f* v) {
        Vec2f disp = *this - *v;
        return disp.length();
    }
    
    void normalize();
    void normalize(const Vec2f* input);

    void rot(Vec2f* out, float rot) const;
    float angle(const Vec2f* v) const;

    static void copy(Vec2f& dest, const Vec2f& src) {
#ifdef MATCHING
        __memcpy(&dest, &src, sizeof(Vec2f));
#else
        dest.m_x = src.m_x;
        dest.m_y = src.m_y;
#endif
    }
};
static_assert(sizeof(Vec2f) == 8, "Class is wrong size!");

class Vec3f {
public:
    union {
        struct {
            float m_x;
            float m_y;
            float m_z;
        };
        struct {
            float m_roll;
            float m_pitch;
            float m_yaw;
        };
    };

    Vec3f() { }
    Vec3f(float x, float y, float z) : m_x(x), m_y(y), m_z(z) { }

    Vec3f& operator=(const Vec3f& orig) {
        m_x = orig.m_x;
        m_y = orig.m_y;
        m_z = orig.m_z;
        return *this;
    }

    Vec2f* xy() const {
        return (Vec2f*)this;
    }

    Vec3f operator-(const Vec3f& v);

#ifdef MATCHING
    friend void Vec3fAdd(register Vec3f* pOut, register const Vec3f* lhs,
                     register const Vec3f* rhs) {
        register f32 fr0, fr1, fr2, fr3;

        // clang-format off
        asm {
            psq_l  fr0, Vec3f.m_x(lhs),   0, 0
            psq_l  fr1, Vec3f.m_x(rhs),   0, 0
            psq_l  fr2, Vec3f.m_z(lhs),   1, 0
            psq_l  fr3, Vec3f.m_z(rhs),   1, 0
            ps_add fr0, fr0, fr1
            ps_add fr2, fr2, fr3
            psq_st fr0, Vec3f.m_x(pOut), 0, 0
            psq_st fr2, Vec3f.m_z(pOut), 1, 0
        }
        // clang-format on
    }

    friend void Vec3fScale(register Vec3f* pOut, register const Vec3f* v,
                       register f32 c) {
        register f32 fr0, fr1, fr2, fr3;

        // clang-format off
        asm {
            psq_l    fr0, Vec3f.m_x(v),    0, 0
            psq_l    fr1, Vec3f.m_z(v),    1, 0
            ps_muls0 fr2, fr0, c
            ps_muls0 fr3, fr1, c
            psq_st   fr2, Vec3f.m_x(pOut), 0, 0
            psq_st   fr3, Vec3f.m_z(pOut), 1, 0
        }
        // clang-format on
    }

    friend void Vec3fSub(register Vec3f* pOut, register const Vec3f* lhs,
                     register const Vec3f* rhs) {
        register f32 fr3, fr2, fr1, fr0;

        // clang-format off
        asm {
            psq_l  fr0, Vec3f.m_x(lhs),   0, 0
            psq_l  fr1, Vec3f.m_x(rhs),   0, 0
            psq_l  fr2, Vec3f.m_z(lhs),   1, 0
            psq_l  fr3, Vec3f.m_z(rhs),   1, 0
            ps_sub fr0, fr0, fr1
            ps_sub fr1, fr2, fr3
            psq_st fr0, Vec3f.m_x(pOut), 0, 0
            psq_st fr1, Vec3f.m_z(pOut), 1, 0
        }
        // clang-format on
    }
#else
    friend void Vec3fAdd(Vec3f* pOut, const Vec3f* lhs, const Vec3f* rhs) {
        pOut->m_x = lhs->m_x + rhs->m_x;
        pOut->m_y = lhs->m_y + rhs->m_y;
        pOut->m_z = lhs->m_z + rhs->m_z;
    }

    friend void Vec3fScale(Vec3f* pOut, const Vec3f* v, f32 c) {
        pOut->m_x = v->m_x * c;
        pOut->m_y = v->m_y * c;
        pOut->m_z = v->m_z * c;
    }

    friend void Vec3fSub(Vec3f* pOut, const Vec3f* lhs, const Vec3f* rhs) {
        pOut->m_x = lhs->m_x - rhs->m_x;
        pOut->m_y = lhs->m_y - rhs->m_y;
        pOut->m_z = lhs->m_z - rhs->m_z;
    }
#endif

    Vec3f operator+(const Vec3f& v) const {
        Vec3f res;
        Vec3fAdd(&res, this, &v);
        return res;
    }

    Vec3f operator*(const float c) const {
        Vec3f res;
        Vec3fScale(&res, this, c);
        return res;
    }

    Vec3f operator/(const float c) const {
        Vec3f res;
        Vec3fScale(&res, this, 1 / c);
        return res;
    }

    Vec3f& operator+=(const Vec3f& v) {
        *this = *this + v;
        return *this;
    }

    Vec3f& operator-=(const Vec3f& v) {
        *this = *this - v;
        return *this;
    }

    Vec3f& operator*=(const float c) {
        *this = *this * c;
        return *this;
    }

    float lengthSq() const {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }

    float length();
    float distance(Vec3f* v) {
        Vec3f disp = *this - *v;
        return disp.length();
    }
    void normalize();
    void normalize(const Vec3f* input);

    void rot(const Vec3f* axis, float rot, Vec3f* out) const;
    float angle(const Vec3f* v) const;
    void slerp(const Vec3f* v, Vec3f* out, float t) const;
};
static_assert(sizeof(Vec3f) == 12, "Class is wrong size!");

class Rect2D {
public:
    float m_left;
    float m_right;
    float m_up;
    float m_down;
};

Vec3f operator*(const float c, const Vec3f& v);
