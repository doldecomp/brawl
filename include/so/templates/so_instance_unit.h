#pragma once

// Local copy of the BrawlHeaders instance-unit declarations for template emission.
// Explicit mask assignment preserves the signed halfword copy used by these records.

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
    // MATCH-ONLY: Argument copies use the signed attribute mask load.
    soAttributeFlag(const soAttributeFlag& other) : m_mask(other.m_mask) { }
    ~soAttributeFlag() { }
    soAttributeFlag& operator=(const soAttributeFlag& other) {
        m_mask = other.m_mask;
        return *this;
    }
};

template <class T>
class soInstanceUnit {
public:
    T m_element;
    int m_id;

    soInstanceUnit() : m_element(), m_id(-1) { }
    soInstanceUnit(T& elm, s32 id) : m_element(elm), m_id(id) { }
};

// MATCH-ONLY: Default pointer records leave the element untouched.
template<class T>
class soInstanceUnit<T*> {
public:
    T* m_element;
    int m_id;
    soInstanceUnit() : m_id(-1) { }
    soInstanceUnit(T*& elm, s32 id) : m_element(elm), m_id(id) { }
};

template <typename T>
class soInstanceUnitFullProperty : public soInstanceUnit<T> {
public:
    soAttributeFlag m_attribute;
    s16 m_10;

    soInstanceUnitFullProperty();
    soInstanceUnitFullProperty(T& elm, s32 id, soAttributeFlag attr, s16 p4);
    ~soInstanceUnitFullProperty();

    soAttributeFlag getAttribute() const;

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


// MATCH-ONLY: Managers call the separately owned record constructor.
#ifndef SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_CTOR
template<class T>
soInstanceUnitFullProperty<T>::soInstanceUnitFullProperty(T& elm, s32 id, soAttributeFlag attr, s16 p4) :
    soInstanceUnit<T>(elm, id), m_attribute(attr.m_mask), m_10(p4) { }
#endif

// MATCH-ONLY: Managers call the separately owned signed mask getter.
#ifndef SO_INSTANCE_UNIT_EXTERNAL_GET_ATTRIBUTE
template<class T>
soAttributeFlag soInstanceUnitFullProperty<T>::getAttribute() const {
    return soAttributeFlag(m_attribute.m_mask);
}
#endif


template<class T>
soInstanceUnitFullProperty<T>::soInstanceUnitFullProperty() :
    m_attribute(0), m_10(-1) { }

template<class T>
soInstanceUnitFullProperty<T>::~soInstanceUnitFullProperty() { }
