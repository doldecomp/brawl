#include <havok/hkObjectInspector.h>
#include <havok/hkError.h>
#include <havok/hkIostream.h>

hkResult hkObjectInspector::getPointers(void* object, const hkClass& klass, hkArray<Pointer>& pointersOut) {
    for (int i = 0; i < klass.getNumMembers(); i++) {
        const hkClassMember& member = klass.getMember(i);
        char* base = (char*)object + member.m_offset;
        switch (member.m_type) {
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 21: case 24: case 29:
            break;
        case hkClassMember::TYPE_POINTER:
            if (member.m_subtype == hkClassMember::TYPE_STRUCT) {
                const hkClass* sc = member.getStructClass();
                int n = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
                Pointer* p = pointersOut.expandBy(n);
                for (int k = 0; k < n; k++) {
                    p[k].m_address = (void**)(base + k * 4);
                    p[k].m_class = sc;
                }
            }
            break;
        case hkClassMember::TYPE_ARRAY:
        case hkClassMember::TYPE_INPLACEARRAY:
        case hkClassMember::TYPE_SIMPLEARRAY: {
            int sub = member.getArrayType();
            void* data = *(void**)base;
            if (data != 0) {
                if (sub == hkClassMember::TYPE_POINTER) {
                    const hkClass* sc = member.getStructClass();
                    int n = ((int*)base)[1];
                    Pointer* p = pointersOut.expandBy(n);
                    for (int k = 0; k < n; k++) {
                        p[k].m_address = (void**)((char*)data + k * 4);
                        p[k].m_class = sc;
                    }
                } else if (sub == hkClassMember::TYPE_STRUCT) {
                    const hkClass* sc = member.getStructClass();
                    int n = ((int*)base)[1];
                    int sz = sc->getObjectSize();
                    for (int k = 0; k < n; k++) {
                        if (getPointers((char*)data + k * sz, *sc, pointersOut) == HK_FAILURE) {
                            return HK_FAILURE;
                        }
                    }
                } else if (sub == hkClassMember::TYPE_VARIANT) {
                    int n = ((int*)base)[1];
                    Pointer* p = pointersOut.expandBy(n);
                    struct Variant { void* m_object; const hkClass* m_class; };
                    for (int k = 0; k < n; k++) {
                        Variant* v = (Variant*)data + k;
                        p[k].m_address = &v->m_object;
                        p[k].m_class = v->m_class;
                    }
                }
            }
            break;
        }
        case hkClassMember::TYPE_STRUCT: {
            const hkClass* sc = member.getStructClass();
            int n = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
            int sz = sc->getObjectSize();
            for (int k = 0; k < n; k++) {
                if (getPointers(base + k * sz, *sc, pointersOut) == HK_FAILURE) {
                    return HK_FAILURE;
                }
            }
            break;
        }
        case hkClassMember::TYPE_HOMOGENEOUSARRAY: {
            char* data = (char*)((int*)base)[1];
            const hkClass* sc = *(const hkClass**)base;
            if (data != 0 && sc != 0) {
                int n = ((int*)base)[2];
                int sz = sc->getObjectSize();
                for (int k = 0; k < n; k++) {
                    if (getPointers(data + k * sz, *sc, pointersOut) == HK_FAILURE) {
                        return HK_FAILURE;
                    }
                }
            }
            break;
        }
        case hkClassMember::TYPE_VARIANT: {
            int n = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
            Pointer* p = pointersOut.expandBy(n);
            struct Variant { void* m_object; const hkClass* m_class; };
            for (int k = 0; k < n; k++) {
                Variant* v = (Variant*)base + k;
                p[k].m_address = &v->m_object;
                p[k].m_class = v->m_class;
            }
            break;
        }
        default: {
            char buf[0x200];
            hkOstream os(buf, sizeof(buf), hkBool(true));
            os << "Unknown class member found during write of data.";
            hkError::s_instance->message(3, 0x641E3E03, buf, "hkObjectInspector.cpp", 0xFC);
            return HK_FAILURE;
        }
        }
    }
    return HK_SUCCESS;
}

hkResult hkObjectInspector::walkPointers(void* object, const hkClass& klass, Listener& listener) {
    hkArray<Pointer> pointers;
    if (getPointers(object, klass, pointers) == HK_SUCCESS && listener.objectCallback(object, klass, pointers) == HK_SUCCESS) {
        for (int i = 0; i < pointers.getSize(); i++) {
            if (*pointers[i].m_address != 0 && walkPointers(*pointers[i].m_address, *pointers[i].m_class, listener) == HK_FAILURE) {
                return HK_FAILURE;
            }
        }
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}
