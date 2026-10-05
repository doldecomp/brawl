#include <havok/hkRegistry.h>

void hkVtableClassRegistry::registerList(const hkTypeInfo* const* infos, const hkClass* const* classes) {
    const hkTypeInfo* const* a = infos;
    const hkClass* const* b = classes;
    while (*a != 0 && *b != 0) {
        if ((*a)->m_vtable != 0) {
            registerVtable((*a)->m_vtable, *b);
        }
        a++;
        b++;
    }
}
