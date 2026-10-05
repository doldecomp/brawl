#include <havok/hkPointerMapBase.h>
#include <havok/hkString.h>

template <typename T>
hkPointerMapBase<T>::hkPointerMapBase() {
    m_elem = (T*)hkMemory::getInstance().allocateChunk(sizeof(T) * 2 * 16, 0x15);
    m_numElems = 0;
    m_hashMod = 15;
    clear();
}

template <typename T>
hkPointerMapBase<T>::~hkPointerMapBase() {
    if (!(m_numElems & DONT_DEALLOCATE_FLAG)) {
        hkMemory::getInstance().deallocateChunk(m_elem, (m_hashMod + 1) * sizeof(T) * 2, 0x15);
    }
}

template <typename T>
void hkPointerMapBase<T>::insert(T key, T value) {
    if (m_numElems * 2 > m_hashMod) {
        resizeTable(m_hashMod * 2 + 2);
    }
    T h = ((key >> 4) * 0x9E3779B1) & m_hashMod;
    while (m_elem[h] != 0 && key != m_elem[h]) {
        h = (h + 1) & m_hashMod;
    }
    m_numElems += m_elem[h] != key;
    m_elem[h] = key;
    m_elem[h + m_hashMod + 1] = value;
}

template <typename T>
int hkPointerMapBase<T>::findKey(T key) const {
    T h = ((key >> 4) * 0x9E3779B1) & m_hashMod;
    while (m_elem[h] != 0) {
        if (m_elem[h] == key) {
            return h;
        }
        h = (h + 1) & m_hashMod;
    }
    return m_hashMod + 1;
}

template <typename T>
T hkPointerMapBase<T>::getWithDefault(T key, T defaultValue) const {
    T v;
    if (get(key, &v) == HK_SUCCESS) {
        defaultValue = v;
    }
    return defaultValue;
}

template <typename T>
hkResult hkPointerMapBase<T>::get(T key, T* out) const {
    int idx = findKey(key);
    if (isValid(idx)) {
        *out = m_elem[idx + m_hashMod + 1];
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

template <typename T>
hkBool hkPointerMapBase<T>::isValid(int index) const {
    return hkBool(index <= m_hashMod);
}

template <typename T>
void hkPointerMapBase<T>::remove(int index) {
    m_numElems--;
    m_elem[index] = 0;
    int mask = m_hashMod;
    int i = mask & (mask + index);
    while (m_elem[i] != 0) {
        i = mask & (mask + i);
    }
    T start = (i + 1) & mask;
    T hole = index;
    T j = (index + 1) & mask;
    while (m_elem[j] != 0) {
        T key = m_elem[j];
        T h = mask & ((key >> 4) * 0x9E3779B1);
        if (j >= start) {
            if (h > hole) {
                goto next;
            }
        }
        if (j < hole) {
            if (h > hole) {
                goto next;
            }
            if (h <= j) {
                goto next;
            }
        }
        if (h > hole) {
            if (h < start) {
                goto next;
            }
        }
        m_elem[hole] = key;
        m_elem[hole + m_hashMod + 1] = m_elem[j + m_hashMod + 1];
        hole = j;
        m_elem[j] = 0;
    next:
        mask = m_hashMod;
        j = (j + 1) & mask;
    }
}

template <typename T>
hkResult hkPointerMapBase<T>::remove(T key) {
    int idx = findKey(key);
    if (isValid(idx)) {
        remove(idx);
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

template <typename T>
void hkPointerMapBase<T>::clear() {
    hkString::memSet(m_elem, 0, (m_hashMod + 1) * sizeof(T) * 2);
    m_numElems &= DONT_DEALLOCATE_FLAG;
}

template <typename T>
void hkPointerMapBase<T>::reserve(int numElements) {
    int n = numElements * 3;
    int cap = 4;
    while (cap < n) {
        cap *= 2;
    }
    resizeTable(cap);
}

template <typename T>
void hkPointerMapBase<T>::resizeTable(int newCapacity) {
    T* oldElem = m_elem;
    int oldFlag = m_numElems & DONT_DEALLOCATE_FLAG;
    int oldCap = m_hashMod + 1;
    m_elem = (T*)hkMemory::getInstance().allocateChunk(newCapacity * sizeof(T) * 2, 0x15);
    hkString::memSet(m_elem, 0, newCapacity * sizeof(T));
    m_numElems = 0;
    m_hashMod = newCapacity - 1;
    for (int i = 0; i < oldCap; i++) {
        if (oldElem[i] != 0) {
            insert(oldElem[i], oldElem[oldCap + i]);
        }
    }
    if (oldFlag == 0) {
        hkMemory::getInstance().deallocateChunk(oldElem, oldCap * sizeof(T) * 2, 0x15);
    }
}

template hkPointerMapBase<unsigned long>::hkPointerMapBase();
template hkPointerMapBase<unsigned long>::~hkPointerMapBase();
#pragma dont_inline on
template void hkPointerMapBase<unsigned long>::insert(unsigned long, unsigned long);
#pragma dont_inline reset
#pragma dont_inline on
template int hkPointerMapBase<unsigned long>::findKey(unsigned long) const;
#pragma dont_inline reset
template unsigned long hkPointerMapBase<unsigned long>::getWithDefault(unsigned long, unsigned long) const;
#pragma dont_inline on
template hkResult hkPointerMapBase<unsigned long>::get(unsigned long, unsigned long*) const;
#pragma dont_inline reset
template hkBool hkPointerMapBase<unsigned long>::isValid(int) const;
template void hkPointerMapBase<unsigned long>::remove(int);
template hkResult hkPointerMapBase<unsigned long>::remove(unsigned long);
#pragma dont_inline on
template void hkPointerMapBase<unsigned long>::clear();
#pragma dont_inline reset
template void hkPointerMapBase<unsigned long>::reserve(int);
template void hkPointerMapBase<unsigned long>::resizeTable(int);

template hkPointerMapBase<unsigned long long>::hkPointerMapBase();
template hkPointerMapBase<unsigned long long>::~hkPointerMapBase();
template void hkPointerMapBase<unsigned long long>::insert(unsigned long long, unsigned long long);
#pragma dont_inline on
template int hkPointerMapBase<unsigned long long>::findKey(unsigned long long) const;
#pragma dont_inline reset
template void hkPointerMapBase<unsigned long long>::remove(int);
#pragma dont_inline on
template void hkPointerMapBase<unsigned long long>::clear();
#pragma dont_inline reset
template void hkPointerMapBase<unsigned long long>::reserve(int);
template void hkPointerMapBase<unsigned long long>::resizeTable(int);
