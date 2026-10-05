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
    hkResult get(const char* key, V* out) const {
        hkUlong v;
        if (m_impl.get(key, &v) == HK_SUCCESS) {
            *out = (V)v;
            return HK_SUCCESS;
        }
        return HK_FAILURE;
    }
};

template <typename K, typename V>
struct hkPointerMap {
    hkPointerMapBase<hkUlong> m_impl;
    void insert(K key, V value) { m_impl.insert((hkUlong)key, (hkUlong)value); }
};

// A key is present when its slot index is within the table (inline in the original).
inline hkBool hkPointerMapHasKey(const hkPointerMapBase<hkUlong>& map, hkUlong key) {
    return map.findKey(key) <= map.m_hashMod;
}

// Iteration over occupied slots (inline in the original).
inline int hkPointerMapGetFirstIndex(const hkPointerMapBase<hkUlong>& map) {
    int i = 0;
    while (i <= map.m_hashMod) {
        if (map.m_elem[i] != 0) {
            break;
        }
        i++;
    }
    return i;
}
inline int hkPointerMapGetNext(const hkPointerMapBase<hkUlong>& map, int i) {
    i++;
    while (i <= map.m_hashMod) {
        if (map.m_elem[i] != 0) {
            break;
        }
        i++;
    }
    return i;
}
inline hkBool hkPointerMapIsValid(const hkPointerMapBase<hkUlong>& map, int i) {
    return i <= map.m_hashMod;
}
inline hkUlong hkPointerMapGetKey(const hkPointerMapBase<hkUlong>& map, int i) {
    return map.m_elem[i];
}
inline hkUlong hkPointerMapGetValue(const hkPointerMapBase<hkUlong>& map, int i) {
    return map.m_elem[i + map.m_hashMod + 1];
}
