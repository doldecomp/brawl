#include <havok/hkRegistry.h>

// Statically linked type and class tables (generated; defined elsewhere in the link).
extern const hkTypeInfo* const hkBuiltinTypeRegistry_StaticLinkedTypeInfos[];
extern const hkClass* const hkBuiltinTypeRegistry_StaticLinkedClasses[];

void hkBuiltinTypeRegistry::addType(const hkTypeInfo* info, const hkClass* klass) {
    const char* name = klass->getName();
    getClassNameRegistry()->registerClass(klass, name);
    getFinishLoadedObjectRegistry()->registerTypeInfo(info);
    getVtableClassRegistry()->registerVtable(info->m_vtable, klass);
}

void hkFinishLoadedObjectRegistry::registerTypeInfo(const hkTypeInfo* info) {
    m_map.insert(info->m_name, (hkUlong)info);
}

void hkVtableClassRegistry::registerVtable(const void* vtable, const hkClass* klass) {
    m_map.insert(vtable, klass);
}

struct hkDefaultBuiltinTypeRegistry : hkBuiltinTypeRegistry {
    hkClassNameRegistry* m_classNameRegistry;               // 0x08
    hkFinishLoadedObjectRegistry* m_finishLoadedObjectRegistry; // 0x0C
    hkVtableClassRegistry* m_vtableClassRegistry;           // 0x10

    hkDefaultBuiltinTypeRegistry() {
        const hkTypeInfo* const* p;
        hkClassNameRegistry* classNames = new hkClassNameRegistry();
        m_classNameRegistry = classNames;
        classNames->registerList(hkBuiltinTypeRegistry_StaticLinkedClasses);
        hkFinishLoadedObjectRegistry* finish = new hkFinishLoadedObjectRegistry();
        m_finishLoadedObjectRegistry = finish;
        for (p = hkBuiltinTypeRegistry_StaticLinkedTypeInfos; *p != 0; p++) {
            finish->registerTypeInfo(*p);
        }
        hkVtableClassRegistry* vtables = new hkVtableClassRegistry();
        m_vtableClassRegistry = vtables;
        vtables->registerList(hkBuiltinTypeRegistry_StaticLinkedTypeInfos,
                              hkBuiltinTypeRegistry_StaticLinkedClasses);
    }
    virtual ~hkDefaultBuiltinTypeRegistry();
    virtual hkFinishLoadedObjectRegistry* getFinishLoadedObjectRegistry();
    virtual hkClassNameRegistry* getClassNameRegistry();
    virtual hkVtableClassRegistry* getVtableClassRegistry();
};

hkBuiltinTypeRegistry* hkBuiltinTypeRegistry::create() {
    hkDefaultBuiltinTypeRegistry* reg = new hkDefaultBuiltinTypeRegistry();
    return reg;
}

hkVtableClassRegistry* hkDefaultBuiltinTypeRegistry::getVtableClassRegistry() {
    return m_vtableClassRegistry;
}

hkClassNameRegistry* hkDefaultBuiltinTypeRegistry::getClassNameRegistry() {
    return m_classNameRegistry;
}

hkFinishLoadedObjectRegistry* hkDefaultBuiltinTypeRegistry::getFinishLoadedObjectRegistry() {
    return m_finishLoadedObjectRegistry;
}

hkDefaultBuiltinTypeRegistry::~hkDefaultBuiltinTypeRegistry() {
    m_classNameRegistry->removeReference();
    m_finishLoadedObjectRegistry->removeReference();
    m_vtableClassRegistry->removeReference();
}

void hkFinishLoadedObjectRegistry::merge(hkFinishLoadedObjectRegistry& other) {
    for (hkStringMapBase::Iterator it = other.m_map.getIterator(); other.m_map.isValid(it);
         it = other.m_map.getNext(it)) {
        m_map.insert(other.m_map.getKey(it), other.m_map.getValue(it));
    }
}

static hkSingletonInitNode hkBuiltinTypeRegistry_initNode((void* (*)())hkBuiltinTypeRegistry::create,
                                                          (void**)&hkSingleton<hkBuiltinTypeRegistry>::s_instance);

template <>
hkBuiltinTypeRegistry* hkSingleton<hkBuiltinTypeRegistry>::s_instance = 0;
