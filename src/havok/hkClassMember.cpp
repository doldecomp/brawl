#include <havok/hkClass.h>

const hkClassMember::TypeProperties hkClassMember::TYPE_PROPERTIES[] = {
    {hkClassMember::TYPE_VOID, "void", -1, -1},
    {hkClassMember::TYPE_BOOL, "hkBool", 1, 1},
    {hkClassMember::TYPE_CHAR, "hkChar", 1, 1},
    {hkClassMember::TYPE_INT8, "hkInt8", 1, 1},
    {hkClassMember::TYPE_UINT8, "hkUint8", 1, 1},
    {hkClassMember::TYPE_INT16, "hkInt16", 2, 2},
    {hkClassMember::TYPE_UINT16, "hkUint16", 2, 2},
    {hkClassMember::TYPE_INT32, "hkInt32", 4, 4},
    {hkClassMember::TYPE_UINT32, "hkUint32", 4, 4},
    {hkClassMember::TYPE_INT64, "hkInt64", 8, 8},
    {hkClassMember::TYPE_UINT64, "hkUint64", 8, 8},
    {hkClassMember::TYPE_REAL, "hkReal", 4, 4},
    {hkClassMember::TYPE_VECTOR4, "hkVector4", 16, 16},
    {hkClassMember::TYPE_QUATERNION, "hkQuaternion", 16, 16},
    {hkClassMember::TYPE_MATRIX3, "hkMatrix3", 48, 16},
    {hkClassMember::TYPE_ROTATION, "hkRotation", 48, 16},
    {hkClassMember::TYPE_QSTRANSFORM, "hkQsTransform", 48, 16},
    {hkClassMember::TYPE_MATRIX4, "hkMatrix4", 64, 16},
    {hkClassMember::TYPE_TRANSFORM, "hkTransform", 64, 16},
    {hkClassMember::TYPE_ZERO, "hkZero", -1, -1},
    {hkClassMember::TYPE_POINTER, "hkPointer", 4, 4},
    {hkClassMember::TYPE_POINTER, "hkFunctionPointer", 4, 4},
    {hkClassMember::TYPE_ARRAY, "hkArray", 12, 4},
    {hkClassMember::TYPE_INPLACEARRAY, "hkInplaceArray", -1, -1},
    {hkClassMember::TYPE_ENUM, "hkEnum", -1, -1},
    {hkClassMember::TYPE_STRUCT, "hkStruct", -1, -1},
    {hkClassMember::TYPE_SIMPLEARRAY, "hkSimpleArray", 8, 4},
    {hkClassMember::TYPE_HOMOGENEOUSARRAY, "hkHomogeneousArray", 12, 4},
    {hkClassMember::TYPE_VARIANT, "hkVariant", 8, 4},
    {hkClassMember::TYPE_CSTRING, "char*", 4, 4},
    {hkClassMember::TYPE_ULONG, "hkTypeMax", -1, -1},
};

int hkClassMember::getSizeInBytes() const {
    int type = m_type;
    switch (type) {
    case TYPE_ZERO:
        type = m_subtype;
        break;
    }
    int size = -1;
    switch (type) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
    case TYPE_POINTER:
    case TYPE_FUNCTIONPOINTER:
    case TYPE_ARRAY:
    case TYPE_SIMPLEARRAY:
    case TYPE_HOMOGENEOUSARRAY:
    case TYPE_VARIANT:
    case TYPE_CSTRING:
        {
            int n = getCstyleArraySize() ? getCstyleArraySize() : 1;
            size = n * TYPE_PROPERTIES[type].m_size;
        }
        break;
    case TYPE_ENUM:
        {
            int n = getCstyleArraySize() ? getCstyleArraySize() : 1;
            size = (n * m_flags) / 8;
        }
        break;
    case TYPE_STRUCT:
        {
            int n = getCstyleArraySize() ? getCstyleArraySize() : 1;
            size = n * getStructClass()->getObjectSize();
        }
        break;
    case TYPE_VOID:
    case TYPE_ZERO:
    case TYPE_INPLACEARRAY:
    case TYPE_ULONG:
        break;
    }
    return size;
}

int hkClassMember::getAlignment() const {
    int type = m_type;
    switch (type) {
    case TYPE_ZERO:
        type = m_subtype;
        break;
    }
    int align;
    if (type == TYPE_ENUM) {
        align = (unsigned)m_flags >> 3;
    } else if (type == TYPE_STRUCT) {
        align = 1;
        for (int i = 0; i < m_class->getNumMembers(); i++) {
            if (m_class->getMember(i).getAlignment() > align) {
                align = m_class->getMember(i).getAlignment();
            }
        }
    } else {
        align = TYPE_PROPERTIES[type].m_alignment;
    }
    return align;
}

int hkClassMember::getArrayType() const {
    return m_subtype;
}

const hkClass* hkClassMember::getStructClass() const {
    return m_class;
}

int hkClassMember::getCstyleArraySize() const {
    return m_cArraySize;
}
