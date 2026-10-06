#include <so/templates/so_array_value_soTransitionTerm.h>

soTransitionTerm& soTransitionTerm::operator=(const soTransitionTerm& other) {
    if (this == &other)
        return *this;
    m_flags = other.m_flags;
    unk2 = other.unk2;
    m_generalTermIndex = other.m_generalTermIndex;
    return *this;
}
