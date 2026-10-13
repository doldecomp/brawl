#pragma once

#include <StaticAssert.h>
#include <types.h>

template <typename T, u32 C>
class utQueue {
    u16 m_size;
    u16 unk2;
public:
    T m_elements[C];

    utQueue() {
        m_size = C;
        unk2 = 0;
        T* p = m_elements;
        do {
            *p = 0;
            p++;
        } while (p < m_elements + C);
    }

    u32 size() const { return C; }
};
