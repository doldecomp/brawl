#pragma once
#include <StaticAssert.h>
#include <types.h>
// Local declaration shared by motion modules and abstract array instantiations.
class soMotionChangeParam {
public:
    int m_kind;
    float m_frame, m_rate;
    u8 _12, _13, _14, _15;
    soMotionChangeParam() {}
    soMotionChangeParam(int, float, float, u8, u8, u8, u8);
    void operator=(const soMotionChangeParam& other) {
        if (this != &other) {
            m_kind = other.m_kind;
            m_frame = other.m_frame;
            m_rate = other.m_rate;
            _12 = other._12; _13 = other._13; _14 = other._14; _15 = other._15;
        }
    }
};
static_assert(sizeof(soMotionChangeParam) == 16, "Class is wrong size!");
