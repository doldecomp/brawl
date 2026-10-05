#include <havok/hkStringMapBase.h>
#include <havok/hkString.h>

hkStringMapBase::hkStringMapBase() {
    m_elem = (unsigned long*)hkMemory::getInstance().allocateChunk(0xC0, 0x15);
    hkString::memSet(m_elem, 0xFF, 0x40);
    m_numElems = 0;
    m_hashMod = 15;
}

hkStringMapBase::~hkStringMapBase() {
    hkMemory::getInstance().deallocateChunk(m_elem, (m_hashMod + 1) * 3 * 4, 0x15);
}

int hkStringMapBase::getIterator() const {
    int i;
    for (i = 0; i <= m_hashMod; i++) {
        if (m_elem[i] != 0xFFFFFFFF) {
            break;
        }
    }
    return i;
}

const char* hkStringMapBase::getKey(int index) const {
    return (const char*)m_elem[index + m_hashMod + 1];
}

unsigned long hkStringMapBase::getValue(int index) const {
    return m_elem[index + m_hashMod * 2 + 2];
}

int hkStringMapBase::getNext(int index) const {
    int i;
    for (i = index + 1; i <= m_hashMod; i++) {
        if (m_elem[i] != 0xFFFFFFFF) {
            break;
        }
    }
    return i;
}

hkBool hkStringMapBase::isValid(int index) const {
    return hkBool(index <= m_hashMod);
}

#pragma dont_inline on
void hkStringMapBase::insert(const char* key, unsigned long value) {
    int hash = 0;
    for (const char* p = key; *p != 0; p++) {
        hash = hash * 31 + *p;
    }
    unsigned long h = hash & 0x7FFFFFFF;
    if (m_numElems * 2 > m_hashMod) {
        resizeTable(m_hashMod * 2 + 2);
    }
    int slot = h & m_hashMod;
    while (true) {
        unsigned long k = m_elem[slot];
        if (k == 0xFFFFFFFF) {
            m_numElems++;
            break;
        }
        if (h == k && hkString::strCmp(key, (const char*)m_elem[slot + m_hashMod + 1]) == 0) {
            break;
        }
        slot = (slot + 1) & m_hashMod;
    }
    m_elem[slot] = h;
    (m_elem + (slot + m_hashMod))[1] = (unsigned long)key;
    (m_elem + (slot + m_hashMod * 2))[2] = value;
}

#pragma dont_inline reset

int hkStringMapBase::findKey(const char* key) const {
    int hash = 0;
    for (const char* p = key; *p != 0; p++) {
        hash = hash * 31 + *p;
    }
    unsigned long h = hash & 0x7FFFFFFF;
    int slot = h & m_hashMod;
    while (m_elem[slot] != 0xFFFFFFFF) {
        if (h == m_elem[slot] &&
            hkString::strCmp(key, (const char*)m_elem[slot + m_hashMod + 1]) == 0) {
            return slot;
        }
        slot = (slot + 1) & m_hashMod;
    }
    return m_hashMod + 1;
}

#pragma dont_inline on
hkResult hkStringMapBase::get(const char* key, unsigned long* out) const {
    int idx = findKey(key);
    if (isValid(idx)) {
        *out = getValue(idx);
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

#pragma dont_inline reset

unsigned long hkStringMapBase::getWithDefault(const char* key, unsigned long defaultValue) const {
    unsigned long v = defaultValue;
    get(key, &v);
    return v;
}

void hkStringMapBase::resizeTable(int newCapacity) {
    unsigned long* oldElem = m_elem;
    int oldCap = m_hashMod + 1;
    m_elem = (unsigned long*)hkMemory::getInstance().allocateChunk(newCapacity * 12, 0x15);
    hkString::memSet(m_elem, 0xFF, newCapacity * 4);
    m_numElems = 0;
    m_hashMod = newCapacity - 1;
    for (int i = 0; i < oldCap; i++) {
        if (oldElem[i] != 0xFFFFFFFF) {
            insert((const char*)oldElem[oldCap + i], oldElem[oldCap * 2 + i]);
        }
    }
    hkMemory::getInstance().deallocateChunk(oldElem, oldCap * 12, 0x15);
}

void hkStringMapBase::clear() {
    for (int i = 0; i < m_hashMod + 1; i++) {
        m_elem[i] = 0xFFFFFFFF;
    }
    m_numElems = 0;
}
