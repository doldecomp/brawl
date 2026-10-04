#pragma once

#include <types.h>

// Havok reflection class descriptor (reconstructed from asm; Havok ~3.x/4.0 era layout).
struct hkClassEnum;
struct hkClassMember;

struct hkClass {
    const char* m_name;                // 0x00
    const hkClass* m_parent;           // 0x04
    int m_objectSize;                  // 0x08
    int m_numImplementedInterfaces;    // 0x0C
    const hkClassEnum* m_declaredEnums;// 0x10
    int m_numDeclaredEnums;            // 0x14
    const hkClassMember* m_declaredMembers; // 0x18
    int m_numDeclaredMembers;          // 0x1C
    const void* m_defaults;            // 0x20

    hkClass(const char* name, const hkClass* parent, int objectSize, const hkClass** interfaces,
            int numInterfaces, const hkClassEnum* enums, int numEnums,
            const hkClassMember* members, int numMembers, const void* defaults);

    const char* getName() const;
    const hkClass* getParent() const;
    int getNumDeclaredInterfaces() const;
    int getNumMembers() const;
    const hkClassMember& getMember(int i) const;
    const hkClassMember& getMember(int i);
    int getNumDeclaredMembers() const;
    const hkClassMember& getDeclaredMember(int i) const;
    int getObjectSize() const;
    void setObjectSize(int size);
};
