#pragma once

#include <types.h>

// Havok reflection class descriptor (reconstructed from asm; Havok 3.x/4.0-era layout).
struct hkClass;
struct hkClassEnum;

// One declared member of a reflected class (0x14 bytes)
struct hkClassMember {
    enum Type {
        TYPE_VOID = 0,
        TYPE_BOOL = 1,
        TYPE_CHAR = 2,
        TYPE_INT8 = 3,
        TYPE_UINT8 = 4,
        TYPE_INT16 = 5,
        TYPE_UINT16 = 6,
        TYPE_INT32 = 7,
        TYPE_UINT32 = 8,
        TYPE_INT64 = 9,
        TYPE_UINT64 = 10,
        TYPE_REAL = 11,
        TYPE_VECTOR4 = 12,
        TYPE_QUATERNION = 13,
        TYPE_MATRIX3 = 14,
        TYPE_ROTATION = 15,
        TYPE_QSTRANSFORM = 16,
        TYPE_MATRIX4 = 17,
        TYPE_TRANSFORM = 18,
        TYPE_ZERO = 19,
        TYPE_POINTER = 20,
        TYPE_FUNCTIONPOINTER = 21,
        TYPE_ARRAY = 22,
        TYPE_INPLACEARRAY = 23,
        TYPE_ENUM = 24,
        TYPE_STRUCT = 25,
        TYPE_SIMPLEARRAY = 26,
        TYPE_HOMOGENEOUSARRAY = 27,
        TYPE_VARIANT = 28,
        TYPE_CSTRING = 29,
        TYPE_ULONG = 30,
        TYPE_FLAGS = 31
    };

    const char* m_name;        // 0x00
    const hkClass* m_class;    // 0x04
    const hkClassEnum* m_enum; // 0x08
    u8 m_type;                 // 0x0C
    u8 m_subtype;              // 0x0D
    u16 m_cArraySize;          // 0x0E
    u16 m_flags;               // 0x10
    u16 m_offset;              // 0x12
};

// One named constant of a reflected enum (0x8 bytes)
struct hkClassEnumItem {
    int m_value;        // 0x00
    const char* m_name; // 0x04
};

// A reflected enum (0xC bytes)
struct hkClassEnum {
    const char* m_name;               // 0x00
    const hkClassEnumItem* m_items;   // 0x04
    int m_numItems;                   // 0x08
};

struct hkClass {
    const char* m_name;                      // 0x00
    const hkClass* m_parent;                 // 0x04
    int m_objectSize;                        // 0x08
    int m_numImplementedInterfaces;          // 0x0C
    const hkClassEnum* m_declaredEnums;      // 0x10
    int m_numDeclaredEnums;                  // 0x14
    const hkClassMember* m_declaredMembers;  // 0x18
    int m_numDeclaredMembers;                // 0x1C
    const void* m_defaults;                  // 0x20

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

#ifndef HK_OFFSET_OF
#define HK_OFFSET_OF(CLS, MEMBER) ((int)(&((CLS*)0)->MEMBER))
#endif
