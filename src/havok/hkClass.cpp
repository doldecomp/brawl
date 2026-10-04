#include <havok/hkClass.h>

struct hkClassMember {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
};

hkClass::hkClass(const char* name, const hkClass* parent, int objectSize, const hkClass** interfaces,
                 int numInterfaces, const hkClassEnum* enums, int numEnums,
                 const hkClassMember* members, int numMembers, const void* defaults) {
    m_name = name;
    m_parent = parent;
    m_objectSize = objectSize;
    m_numImplementedInterfaces = numInterfaces;
    m_declaredEnums = enums;
    m_numDeclaredEnums = numEnums;
    m_declaredMembers = members;
    m_numDeclaredMembers = numMembers;
    m_defaults = defaults;
}

const char* hkClass::getName() const {
    return m_name;
}

const hkClass* hkClass::getParent() const {
    return m_parent;
}

int hkClass::getNumDeclaredInterfaces() const {
    return m_numImplementedInterfaces;
}

#pragma dont_inline on
int hkClass::getNumMembers() const {
    const hkClass* c = m_parent;
    int n = m_numDeclaredMembers;
    while (c) {
        n += c->m_numDeclaredMembers;
        c = c->m_parent;
    }
    return n;
}

const hkClassMember& hkClass::getMember(int i) const {
    int j = i - getNumMembers();
    for (const hkClass* c = this; c; c = c->m_parent) {
        j += c->m_numDeclaredMembers;
        if (j >= 0) {
            return c->m_declaredMembers[j];
        }
    }
    return *m_declaredMembers;
}

#pragma dont_inline reset
const hkClassMember& hkClass::getMember(int i) {
    return static_cast<const hkClass*>(this)->getMember(i);
}

int hkClass::getNumDeclaredMembers() const {
    return m_numDeclaredMembers;
}

const hkClassMember& hkClass::getDeclaredMember(int i) const {
    return m_declaredMembers[i];
}

int hkClass::getObjectSize() const {
    return m_objectSize;
}

void hkClass::setObjectSize(int size) {
    m_objectSize = size;
}
