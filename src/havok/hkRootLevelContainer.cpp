#include <havok/hkRegistry.h>

void* hkRootLevelContainer::findObjectByType(const char* typeName, const void* prevObject) const {
    int i = 0;
    int offset = 0;
    const hkRootLevelContainerNamedVariant* e;
    do {
        if (prevObject == 0 || i >= m_namedVariants.m_size) {
            break;
        }
        i++;
        e = (const hkRootLevelContainerNamedVariant*)((char*)m_namedVariants.m_data + offset);
        offset += sizeof(hkRootLevelContainerNamedVariant);
    } while (e->m_variant.m_object != prevObject);
    offset = i * sizeof(hkRootLevelContainerNamedVariant);
    for (; i < m_namedVariants.m_size; offset += sizeof(hkRootLevelContainerNamedVariant), i++) {
        e = (const hkRootLevelContainerNamedVariant*)((char*)m_namedVariants.m_data + offset);
        if (hkString::strCmp(typeName, e->getTypeName()) == 0) {
            return m_namedVariants.m_data[i].m_variant.m_object;
        }
    }
    return 0;
}
