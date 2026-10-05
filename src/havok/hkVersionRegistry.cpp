#include <havok/hkRegistry.h>
#include <havok/hkStructureLayout.h>

// Index value marking "no predecessor" in the path search.
static int s_nullIndex = -1;

int hkVersionRegistry::Updater::getNumElements(const Updater* const* updaters) {
    int n = 0;
    while (*updaters != 0) {
        n++;
        updaters++;
    }
    return n;
}

hkVersionRegistry::hkVersionRegistry()
    : m_updaters((const Updater**)StaticLinkedUpdaters, Updater::getNumElements(StaticLinkedUpdaters),
                 Updater::getNumElements(StaticLinkedUpdaters)) {
}

hkVersionRegistry::~hkVersionRegistry() {
    for (int it = m_versionToClassNameRegistryMap.getIterator(); m_versionToClassNameRegistryMap.isValid(it);
         it = m_versionToClassNameRegistryMap.getNext(it)) {
        ((hkClassNameRegistry*)m_versionToClassNameRegistryMap.getValue(it))->removeReference();
    }
    m_versionToClassNameRegistryMap.m_impl.clear();
}

hkResult hkVersionRegistry::getVersionPath(const char* versionFrom, const char* versionTo,
                                           hkArray<const Updater*>& pathOut) const {
    if (hkString::strCmp(versionFrom, versionTo) == 0) {
        return HK_SUCCESS;
    }

    int n = m_updaters.getSize();
    hkArray<int> prev;
    if (n > 0) {
        prev.reserveSmart(n);
        for (int i = prev.m_size; i < n; i++) {
            prev[i] = s_nullIndex;
        }
    }
    prev.m_size = n;

    hkArray<int> toGoal;   // updaters that do not end at versionTo
    hkArray<int> frontier; // updaters that end at versionTo
    for (int i = 0; i < m_updaters.getSize(); i++) {
        const Updater* u = m_updaters[i];
        if (hkString::strCmp(versionTo, u->m_toVersion) != 0) {
            toGoal.pushBack(i);
        } else if (hkString::strCmp(versionFrom, u->m_fromVersion) == 0) {
            pathOut.pushBack(m_updaters[i]);
            return HK_SUCCESS;
        } else {
            frontier.pushBack(i);
        }
    }

    while (frontier.getSize() != 0) {
        hkArray<int> next;
        for (int a = toGoal.getSize() - 1; a >= 0; a--) {
            int idx = toGoal[a];
            for (int f = 0; f < frontier.getSize(); f++) {
                int fi = frontier[f];
                if (hkString::strCmp(m_updaters[idx]->m_toVersion, m_updaters[fi]->m_fromVersion) == 0) {
                    prev[idx] = fi;
                    if (hkString::strCmp(m_updaters[idx]->m_fromVersion, versionFrom) == 0) {
                        for (int cur = idx; cur != -1; cur = prev[cur]) {
                            pathOut.pushBack(m_updaters[cur]);
                        }
                        return HK_SUCCESS;
                    }
                    next.pushBack(idx);
                    toGoal.m_size--;
                    toGoal[a] = toGoal[toGoal.m_size];
                }
            }
        }
        frontier.swap(next);
    }
    return HK_FAILURE;
}

hkClassNameRegistry* hkVersionRegistry::getClassNameRegistry(const char* versionString) {
    hkClassNameRegistry* registry;
    if (m_versionToClassNameRegistryMap.get(versionString, &registry) == HK_SUCCESS) {
        return registry;
    }
    const ClassVersion* v = StaticLinkedClassVersions;
    registry = 0;
    for (; v->m_version != 0; v++) {
        if (hkString::strCmp(versionString, v->m_version) == 0) {
            if (hkString::strCmp(versionString, "Havok-4.0.0-r1") == 0) {
                registry = hkBuiltinTypeRegistry::getInstance().getClassNameRegistry();
                registry->addReference();
            } else {
                registry = new hkClassNameRegistry();
                const hkClass* const* classes = v->m_classes;
                hkStructureLayout layout;
                hkPointerMapBase<hkUlong> done;
                for (; *classes != 0; classes++) {
                    layout.computeMemberOffsetsInplace((hkClass*)*classes, done);
                }
                registry->registerList(v->m_classes);
            }
            m_versionToClassNameRegistryMap.insert(v->m_version, (hkUlong)registry);
            break;
        }
    }
    return registry;
}

hkVersionRegistry* hkVersionRegistry::create() {
    return new hkVersionRegistry();
}

static hkSingletonInitNode hkVersionRegistry_initNode((void* (*)())hkVersionRegistry::create,
                                                      (void**)&hkSingleton<hkVersionRegistry>::s_instance);

template <>
hkVersionRegistry* hkSingleton<hkVersionRegistry>::s_instance = 0;
