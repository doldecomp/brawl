#pragma once

#include <havok/hkPointerMapBase.h>
#include <havok/hkStringMapBase.h>

typedef unsigned long hkUlong;

// Typed wrappers (the base does the work; the wrapper only adds type safety).
template <typename V>
struct hkStringMap {
    hkStringMapBase m_impl;
    void insert(const char* key, hkUlong value) { m_impl.insert(key, value); }
    int getIterator() const { return m_impl.getIterator(); }
    int getNext(int it) const { return m_impl.getNext(it); }
    hkBool isValid(int it) const { return m_impl.isValid(it); }
    const char* getKey(int it) const { return m_impl.getKey(it); }
    hkUlong getValue(int it) const { return m_impl.getValue(it); }
};

template <typename K, typename V>
struct hkPointerMap {
    hkPointerMapBase<hkUlong> m_impl;
    void insert(K key, V value) { m_impl.insert((hkUlong)key, (hkUlong)value); }
};

// A key is present when its slot index is within the table (inline in the original).
inline hkBool hkPointerMapHasKey(const hkPointerMapBase<hkUlong>& map, hkUlong key) {
    return (hkUlong)map.findKey(key) <= (hkUlong)map.m_hashMod;
}
