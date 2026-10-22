#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <type_traits>

typedef s16 soAttributeMask;
static const soAttributeMask ATTRIBUTE_MASK_NONE = 0;
struct soAttributeFlag {
    union {
        struct {
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
        };
        soAttributeMask m_mask;
    };
    soAttributeFlag() : m_mask(ATTRIBUTE_MASK_NONE) { }
    soAttributeFlag(soAttributeMask bits) : m_mask(bits) { }
    ~soAttributeFlag() { }
};

template <class T>
class soInstanceUnit {
public:
    T m_element;
    int m_id;

    soInstanceUnit() : m_element(), m_id(-1) { }
    soInstanceUnit(T& elm, s32 id) : m_element(elm), m_id(id) { }
};

template <typename T>
class soInstanceUnitFullProperty : public soInstanceUnit<T> {
public:
    soAttributeFlag m_attribute;
    s16 m_10;

    soInstanceUnitFullProperty() : m_attribute(0), m_10(-1) { }
    soInstanceUnitFullProperty(T& elm, s32 id, soAttributeFlag attr, s16 p4) :
        soInstanceUnit<T>(elm, id), m_attribute(attr), m_10(p4) { }
    ~soInstanceUnitFullProperty() { }

    soAttributeFlag getAttribute() const {
        return m_attribute;
    }
};

// TODO: inferred class
template <typename T>
class soInstanceUnitFullPropertyWrapper {
public:
    soAttributeFlag m_attr;
    soInstanceUnitFullProperty<T> m_prop;

    soInstanceUnitFullPropertyWrapper() { }
    soInstanceUnitFullPropertyWrapper(soAttributeFlag attr, T& elm, s32 id, s16 p4) :
        m_attr(attr), m_prop(elm, id, m_attr, p4) { }
    ~soInstanceUnitFullPropertyWrapper() { }
};
