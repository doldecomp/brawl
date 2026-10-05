#pragma once

#include <havok/hkBase.h>

typedef unsigned long hkUlong;

// Open-addressed hash map keyed by C string; layout {elem table, numElems, hashMod}.
// Out-of-line implementations live in the base-layer units (hkStringMapBase.cpp).
struct hkStringMapBase {
    typedef int Iterator;

    void* m_elem;      // 0x00
    int m_numElems;    // 0x04
    int m_hashMod;     // 0x08

    hkStringMapBase();
    ~hkStringMapBase();

    Iterator getIterator() const;
    Iterator getNext(Iterator it) const;
    hkBool isValid(Iterator it) const;
    const char* getKey(Iterator it) const;
    hkUlong getValue(Iterator it) const;
    void insert(const char* key, hkUlong value);
};

// Open-addressed hash map keyed by pointer-sized integer.
template <typename K>
struct hkPointerMapBase {
    void* m_elem;      // 0x00
    int m_numElems;    // 0x04
    int m_hashMod;     // 0x08

    typedef int Iterator;

    hkPointerMapBase();
    ~hkPointerMapBase();

    void insert(K key, K value);
    Iterator findKey(K key) const;
    hkBool isValid(Iterator it) const { return (K)it <= (K)m_hashMod; }
    hkBool hasKey(K key) const { return isValid(findKey(key)); }
};

// Typed wrappers (the base does the work; the wrapper only adds type safety).
template <typename V>
struct hkStringMap {
    hkStringMapBase m_impl;
    void insert(const char* key, hkUlong value) { m_impl.insert(key, value); }
    hkStringMapBase::Iterator getIterator() const { return m_impl.getIterator(); }
    hkStringMapBase::Iterator getNext(hkStringMapBase::Iterator it) const { return m_impl.getNext(it); }
    hkBool isValid(hkStringMapBase::Iterator it) const { return m_impl.isValid(it); }
    const char* getKey(hkStringMapBase::Iterator it) const { return m_impl.getKey(it); }
    hkUlong getValue(hkStringMapBase::Iterator it) const { return m_impl.getValue(it); }
};

template <typename K, typename V>
struct hkPointerMap {
    hkPointerMapBase<hkUlong> m_impl;
    void insert(K key, V value) { m_impl.insert((hkUlong)key, (hkUlong)value); }
};
