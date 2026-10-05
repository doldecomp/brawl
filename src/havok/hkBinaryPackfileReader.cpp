#include <havok/hkBinaryPackfileReader.h>

extern const hkClass hkClassClass;
extern const hkClass hkClassMemberClass;
extern const hkClass hkClassEnumClass;
extern const hkClass hkClassEnumItemClass;
extern const hkClass hkClassVersion1Class;

namespace {

void updateSectionHeaders(hkPackfileSectionHeader* headers, int numHeaders) {
    for (int i = 0; i < numHeaders; i++) {
        headers[i].m_endOffset = headers[i].m_importsOffset;
        headers[i].m_exportsOffset = headers[i].m_importsOffset;
    }
}

// Collects the pointer slots of every reached object and the type each object was found with.
struct PackfileObjectsListener : hkObjectInspector::Listener {
    hkArray<hkVariant>* m_loadedObjects;               // 0x04
    hkPointerMapBase<hkUlong>* m_classOfObject;        // 0x08
    hkPointerMapBase<hkUlong> m_visited;               // 0x0C

    virtual hkResult objectCallback(void* object, const hkClass& klass, hkArray<hkObjectInspector::Pointer>& pointers);
};

hkResult PackfileObjectsListener::objectCallback(void* object, const hkClass& klass,
                                                 hkArray<hkObjectInspector::Pointer>& pointers) {
    hkVariant v;
    v.m_object = object;
    v.m_class = &klass;
    m_loadedObjects->pushBack(v);
    m_visited.insert((hkUlong)object, 2);
    int i = 0;
    while (i < pointers.getSize()) {
        bool seen = false;
        void* target = *pointers[i].m_address;
        if (target != 0) {
            if (hkPointerMapHasKey(m_visited, (hkUlong)target)) {
                seen = true;
            }
        }
        if (seen) {
            pointers[i].m_class = (const hkClass*)m_classOfObject->getWithDefault((hkUlong)target, (hkUlong)pointers[i].m_class);
            m_visited.insert((hkUlong)target, 1);
            i++;
        } else {
            pointers.m_size--;
            for (int j = i; j < pointers.m_size; j++) {
                pointers[j] = pointers[j + 1];
            }
        }
    }
    return HK_SUCCESS;
}

} // namespace

hkBinaryPackfileReader::hkBinaryPackfileReader() {
    m_header = 0;
    m_sectionHeaders = 0;
    m_startOffset = 0;
    m_loadedObjects = 0;
    m_tracker = 0;
    m_data = new BinaryPackfileData();
}

hkBinaryPackfileReader::~hkBinaryPackfileReader() {
    delete m_tracker;
    delete m_loadedObjects;
    m_data->removeReference();
}

hkPackfileObjectUpdateTracker::~hkPackfileObjectUpdateTracker() {
    m_packfileData->removeReference();
}

hkPackfileData* hkBinaryPackfileReader::getPackfileData() {
    return m_data;
}

hkResult hkBinaryPackfileReader::loadEntireFile(hkStreamReader* reader) {
    if (loadFileHeader(reader, 0) == HK_SUCCESS && loadSectionHeadersNoSeek(reader, 0) == HK_SUCCESS) {
        for (int i = 0; i < m_header->m_numSections; i++) {
            if (loadSectionNoSeek(reader, i, 0) == HK_FAILURE) {
                return HK_FAILURE;
            }
        }
        return fixupGlobalReferences() == HK_FAILURE;
    }
    return HK_FAILURE;
}

hkResult hkBinaryPackfileReader::loadEntireFileInplace(void* fileInMemory) {
    int* data = (int*)fileInMemory;
    char marker[0x40];
    hkString::memSet(marker, -1, 0x40);
    hkPackfileHeader expected;
    expected.m_magic[0] = 0x57E0E057;
    expected.m_magic[1] = 0x10C0C010;
    (void)marker;
    if (data[0] == 0x57E0E057 && data[1] == 0x10C0C010) {
        m_header = (hkPackfileHeader*)data;
        hkPackfileSectionHeader* sh = 0;
        if (m_header->m_numSections > 0) {
            sh = (hkPackfileSectionHeader*)(data + 0x10);
        }
        m_sectionHeaders = sh;
        if (m_header->m_fileVersion < 4) {
            updateSectionHeaders(m_sectionHeaders, m_header->m_numSections);
        }
        int n = m_header->m_numSections;
        m_sections.reserveSmart(n);
        m_sections.m_size = n;
        for (int i = 0; i < m_header->m_numSections; i++) {
            hkPackfileSectionHeader* h = &m_sectionHeaders[i];
            char* base = (char*)data + h->m_absoluteDataStart;
            int* fix = (int*)(base + h->m_localFixupsOffset);
            for (int k = 0; k < (h->m_globalFixupsOffset - h->m_localFixupsOffset) / 4; k += 2) {
                if (fix[0] != -1) {
                    *(void**)(base + fix[0]) = base + fix[1];
                }
                fix += 2;
            }
            m_sections[i] = base;
        }
        int cnIndex = m_header->m_contentsClassNameSectionIndex;
        if (cnIndex >= 0 && m_header->m_contentsClassNameSectionOffset >= 0 && m_header->m_fileVersion < 3) {
            const hkClass* k = (const hkClass*)getSectionDataByIndex(cnIndex, 0);
            m_header->m_contentsClassNameSectionOffset = (int)k->getName() - (int)m_sections[cnIndex];
        }
        return fixupGlobalReferences();
    }
    return HK_FAILURE;
}

hkObjectUpdateTracker& hkBinaryPackfileReader::getUpdateTracker() {
    if (m_tracker == 0) {
        m_tracker = new hkPackfileObjectUpdateTracker(m_data);
        for (int i = 0; i < m_header->m_numSections; i++) {
            char* data = (char*)m_sections[i];
            if (data != 0) {
                hkPackfileSectionHeader* h = &m_sectionHeaders[i];
                int* fix = (int*)(data + h->m_globalFixupsOffset);
                for (int k = 0; k < (h->m_virtualFixupsOffset - h->m_globalFixupsOffset) / 4; k += 3) {
                    if (fix[0] != -1) {
                        void* target = getSectionDataByIndex(fix[1], fix[2]);
                        m_tracker->objectPointedBy(target, data + fix[0]);
                    }
                    fix += 3;
                }
                fix = (int*)(data + h->m_virtualFixupsOffset);
                for (int k = 0; k < (h->m_exportsOffset - h->m_virtualFixupsOffset) / 4; k += 3) {
                    if (fix[0] != -1) {
                        void* object = getSectionDataByIndex(i, fix[0]);
                        const char* name = (const char*)getSectionDataByIndex(fix[1], fix[2]);
                        m_tracker->addFinish(object, name);
                    }
                    fix += 3;
                }
            }
        }
        m_tracker->m_topLevelObject = getOriginalContents();
        m_tracker->m_topLevelClassName = getOriginalContentsClassName();
    }
    return *m_tracker;
}

void hkPackfileObjectUpdateTracker::objectPointedBy(void* newObject, void* fromWhere) {
    void** slot = (void**)fromWhere;
    void* old = *slot;
    if (old != 0) {
        int idx = m_pointers.getFirstIndex(old);
        while (idx != -1) {
            hkPointerMultiMap<void**>::Entry* e = &m_pointers.m_elements[idx];
            if (e->m_value == slot) {
                if (newObject == old) {
                    return;
                }
                m_pointers.removeByIndex(old, idx);
                break;
            }
            idx = e->m_next;
        }
    }
    if (newObject != 0) {
        m_pointers.insert(newObject, slot);
    }
    *slot = newObject;
}

void hkPackfileObjectUpdateTracker::addFinish(void* newObject, const char* className) {
    m_finishObjects.insert(newObject, className);
}

void hkClassNameRegistry::registerClass(const hkClass* klass, const char* name) {
    name = name ? name : klass->getName();
    m_map.insert(name, (hkUlong)klass);
}

hkClassNameRegistry* hkBinaryPackfileReader::getClassNameRegistry() {
    hkClassNameRegistry* registry = 0;
    int numClasses = 0;
    if (m_header->m_fileVersion < 4 && hkString::strCmp(m_header->m_contentsVersion, "Havok-4.0.0-b1") != 0) {
        int index = getSectionIndex("__classindex__");
        if (index >= 0 && m_sectionHeaders[index].m_localFixupsOffset != 0 && m_sections[index] != 0) {
            registry = new hkClassNameRegistry();
            int* p = (int*)m_sections[index];
            for (int i = 0; i < m_sectionHeaders[index].m_localFixupsOffset / 4 && *p != -1; i += 2) {
                const hkClass* k = (const hkClass*)getSectionDataByIndex(p[0], p[1]);
                if (k != 0) {
                    numClasses++;
                    registry->registerClass(k, k->getName());
                }
                p += 2;
            }
        }
    } else {
        registry = new hkClassNameRegistry();
        for (int i = 0; i < m_header->m_numSections; i++) {
            char* data = (char*)m_sections[i];
            if (data != 0) {
                hkPackfileSectionHeader* h = &m_sectionHeaders[i];
                int* fix = (int*)(data + h->m_virtualFixupsOffset);
                for (int k = 0; k < (h->m_exportsOffset - h->m_virtualFixupsOffset) / 4; k += 3) {
                    if (fix[0] != -1) {
                        const char* name = (const char*)getSectionDataByIndex(fix[1], fix[2]);
                        if (hkString::strCmp(name, "hkClass") == 0) {
                            hkClass* c = (hkClass*)(data + fix[0]);
                            numClasses++;
                            registry->registerClass(c, c->getName());
                        }
                    }
                    fix += 3;
                }
            }
        }
    }
    hkVersionRegistry* versions = hkVersionRegistry::s_instance;
    if (numClasses == 0) {
        hkClassNameRegistry* result = versions->getClassNameRegistry(getOriginalContentsVersion());
        if (registry != 0) {
            registry->removeReference();
        }
        result->addReference();
        return result;
    }
    const hkClass* classes[5];
    classes[0] = &hkClassClass;
    classes[1] = &hkClassMemberClass;
    classes[2] = &hkClassEnumClass;
    classes[3] = &hkClassEnumItemClass;
    classes[4] = 0;
    if (m_header->m_fileVersion == 1) {
        classes[0] = &hkClassVersion1Class;
    }
    for (const hkClass** c = classes; *c != 0; c++) {
        registry->registerClass(*c, (*c)->getName());
    }
    return registry;
}

hkArray<hkVariant>& hkBinaryPackfileReader::getLoadedObjects() {
    if (m_loadedObjects == 0) {
        hkClassNameRegistry* registry = getClassNameRegistry();
        hkPointerMapBase<hkUlong> classOfObject;
        for (int i = 0; i < m_header->m_numSections; i++) {
            char* data = (char*)m_sections[i];
            if (data != 0) {
                hkPackfileSectionHeader* h = &m_sectionHeaders[i];
                int* fix = (int*)(data + h->m_virtualFixupsOffset);
                for (int k = 0; k < (h->m_exportsOffset - h->m_virtualFixupsOffset) / 4; k += 3) {
                    if (fix[0] != -1) {
                        const char* name = (const char*)getSectionDataByIndex(fix[1], fix[2]);
                        const hkClass* c = registry->getClassByName(name);
                        classOfObject.insert((hkUlong)(data + fix[0]), (hkUlong)c);
                    }
                    fix += 3;
                }
            }
        }
        m_loadedObjects = new hkArray<hkVariant>();
        PackfileObjectsListener listener;
        listener.m_loadedObjects = m_loadedObjects;
        listener.m_classOfObject = &classOfObject;
        m_loadedObjects->reserveSmart(classOfObject.m_numElems & 0x7FFFFFFF);
        hkObjectInspector::walkPointers(getOriginalContents(),
                                        *registry->getClassByName(getOriginalContentsClassName()), listener);
        registry->removeReference();
    }
    return *m_loadedObjects;
}

void* hkBinaryPackfileReader::getContentsWithRegistry(const char* expectedClassName,
                                                      hkFinishLoadedObjectRegistry* registry) {
    if (registry != 0) {
        finishLoadedObjects(registry);
    }
    void* contents;
    const char* className;
    hkPackfileObjectUpdateTracker* t = m_tracker;
    if (t != 0) {
        contents = t->m_topLevelObject;
        className = t->m_topLevelClassName;
    } else {
        contents = getOriginalContents();
        className = getOriginalContentsClassName();
    }
    if (expectedClassName != 0 && className != 0) {
        if (hkString::strCmp(expectedClassName, className) != 0) {
            return 0;
        }
    }
    return contents;
}

const char* hkBinaryPackfileReader::getOriginalContentsVersion() {
    if (m_header->m_contentsVersion[0] != -1) {
        return m_header->m_contentsVersion;
    }
    if (m_header->m_fileVersion == 1) {
        return "Havok-3.0.0";
    }
    if (m_header->m_fileVersion == 2) {
        return "Havok-3.1.0";
    }
    return 0;
}

hkResult hkBinaryPackfileReader::loadFileHeader(hkStreamReader* reader, void* buffer) {
    m_startOffset = reader->seekTellSupported() ? reader->tell() : 0;
    if (buffer == 0) {
        buffer = hkMemory::getInstance().allocate(0x40, 5);
        hkPackfileData* d = m_data;
        d->m_memory.pushBack(buffer);
    }
    hkPackfileHeader magic;
    if (reader->read(buffer, 0x40) == 0x40) {
        hkPackfileHeader* h = (hkPackfileHeader*)buffer;
        if (h->m_magic[0] == magic.m_magic[0] && h->m_magic[1] == magic.m_magic[1]) {
            m_header = h;
            return HK_SUCCESS;
        }
    }
    m_header = 0;
    return HK_FAILURE;
}

hkResult hkBinaryPackfileReader::loadSectionHeadersNoSeek(hkStreamReader* reader, void* buffer) {
    if (buffer == 0) {
        buffer = hkMemory::getInstance().allocate(m_header->m_numSections * sizeof(hkPackfileSectionHeader), 5);
        hkPackfileData* d = m_data;
        d->m_memory.pushBack(buffer);
    }
    int size = m_header->m_numSections * sizeof(hkPackfileSectionHeader);
    if (size == reader->read(buffer, size)) {
        m_sectionHeaders = (hkPackfileSectionHeader*)buffer;
        int old = m_sections.getSize();
        int n = m_header->m_numSections;
        if (old < n) {
            m_sections.reserveSmart(n);
            for (int i = old; i < n; i++) {
                m_sections[i] = 0;
            }
        }
        m_sections.m_size = n;
        if (m_header->m_fileVersion < 4) {
            updateSectionHeaders(m_sectionHeaders, m_header->m_numSections);
        }
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

hkResult hkBinaryPackfileReader::loadSectionNoSeek(hkStreamReader* reader, int sectionIndex, void* buffer) {
    hkPackfileSectionHeader* h = &m_sectionHeaders[sectionIndex];
    int size = h->m_endOffset;
    if (buffer == 0) {
        buffer = hkMemory::getInstance().allocate(size, 5);
        hkPackfileData* d = m_data;
        d->m_memory.pushBack(buffer);
    }
    if (size == reader->read(buffer, size)) {
        char* data = (char*)buffer;
        int* fix = (int*)(data + h->m_localFixupsOffset);
        for (int i = 0; i < (h->m_globalFixupsOffset - h->m_localFixupsOffset) / 4; i += 2) {
            if (fix[0] != -1) {
                *(void**)(data + fix[0]) = data + fix[1];
            }
            fix += 2;
        }
        hkArray<hkPackfileData::Export> exports;
        h->getExports(buffer, exports);
        for (int i = 0; i < exports.getSize(); i++) {
            m_data->addExport(exports[i].m_name, exports[i].m_object);
        }
        hkArray<hkPackfileData::Import> imports;
        h->getImports(buffer, imports);
        for (int i = 0; i < imports.getSize(); i++) {
            m_data->addImport(imports[i].m_name, imports[i].m_object);
        }
        m_sections[sectionIndex] = buffer;
        if (sectionIndex == m_header->m_contentsClassNameSectionIndex && m_header->m_contentsClassNameSectionOffset >= 0 &&
            m_header->m_fileVersion < 3) {
            const hkClass* k = (const hkClass*)getSectionDataByIndex(sectionIndex, m_header->m_contentsClassNameSectionOffset);
            m_header->m_contentsClassNameSectionOffset = (int)k->getName() - (int)buffer;
        }
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

hkResult hkBinaryPackfileReader::fixupGlobalReferences() {
    for (int i = 0; i < m_header->m_numSections; i++) {
        char* data = (char*)m_sections[i];
        if (data != 0) {
            hkPackfileSectionHeader* h = &m_sectionHeaders[i];
            int* fix = (int*)(data + h->m_globalFixupsOffset);
            for (int k = 0; k < (h->m_virtualFixupsOffset - h->m_globalFixupsOffset) / 4; k += 3) {
                if (fix[0] != -1) {
                    *(void**)(data + fix[0]) = getSectionDataByIndex(fix[1], fix[2]);
                }
                fix += 3;
            }
        }
    }
    return HK_SUCCESS;
}

hkResult hkBinaryPackfileReader::finishLoadedObjects(hkFinishLoadedObjectRegistry* registry) {
    if (m_tracker == 0) {
        for (int i = 0; i < m_header->m_numSections; i++) {
            char* data = (char*)m_sections[i];
            if (data != 0) {
                hkPackfileSectionHeader* h = &m_sectionHeaders[i];
                int* fix = (int*)(data + h->m_virtualFixupsOffset);
                for (int k = 0; k < (h->m_exportsOffset - h->m_virtualFixupsOffset) / 4; k += 3) {
                    if (fix[0] != -1) {
                        const char* name = (const char*)getSectionDataByIndex(fix[1], fix[2]);
                        void* object = data + fix[0];
                        const hkTypeInfo* info = registry->finishLoadedObject(object, name);
                        if (info != 0) {
                            m_data->m_trackedObjects.insert(object, info);
                        }
                    }
                    fix += 3;
                }
            }
        }
    } else {
        hkPointerMapBase<hkUlong>& map = m_tracker->m_finishObjects.m_impl;
        for (int it = hkPointerMapGetFirstIndex(map); hkPointerMapIsValid(map, it); it = hkPointerMapGetNext(map, it)) {
            const hkTypeInfo* info = registry->finishLoadedObject((void*)hkPointerMapGetKey(map, it),
                                                                  (const char*)hkPointerMapGetValue(map, it));
            if (info != 0) {
                m_data->m_trackedObjects.insert((void*)hkPointerMapGetKey(map, it), info);
            }
        }
    }
    return HK_SUCCESS;
}

const hkTypeInfo* hkFinishLoadedObjectRegistry::finishLoadedObject(void* object, const char* className) const {
    const hkTypeInfo* info = (const hkTypeInfo*)m_map.m_impl.getWithDefault(className, 0);
    if (info != 0 && info->m_finish != 0) {
        info->m_finish(object);
    }
    return info;
}

int hkBinaryPackfileReader::getSectionIndex(const char* sectionTag) {
    for (int i = 0; i < m_header->m_numSections; i++) {
        if (hkString::strCmp(m_sectionHeaders[i].m_sectionTag, sectionTag) == 0) {
            return i;
        }
    }
    return -1;
}

void* hkBinaryPackfileReader::getSectionDataByIndex(int sectionIndex, int offset) {
    char* data = (char*)m_sections[sectionIndex];
    if (data != 0) {
        return data + offset;
    }
    return 0;
}

void* hkBinaryPackfileReader::getOriginalContents() {
    bool valid = false;
    int sec = m_header->m_contentsSectionIndex;
    int off = m_header->m_contentsSectionOffset;
    if (sec >= 0 && off >= 0) {
        valid = true;
    }
    if (valid) {
        return getSectionDataByIndex(m_header->m_contentsSectionIndex, m_header->m_contentsSectionOffset);
    }
    return getSectionDataByIndex(getSectionIndex("__data__"), 0);
}

const char* hkBinaryPackfileReader::getOriginalContentsClassName() {
    bool valid = false;
    int sec = m_header->m_contentsClassNameSectionIndex;
    int off = m_header->m_contentsClassNameSectionOffset;
    if (sec >= 0 && off >= 0) {
        valid = true;
    }
    if (valid) {
        return (const char*)getSectionDataByIndex(m_header->m_contentsClassNameSectionIndex,
                                                  m_header->m_contentsClassNameSectionOffset);
    }
    return 0;
}

const char* hkBinaryPackfileReader::getContentsClassName() {
    if (m_tracker != 0) {
        return m_tracker->m_topLevelClassName;
    }
    return getOriginalContentsClassName();
}

hkResult hkPackfileObjectUpdateTracker::removeFinish(void* oldObject) {
    return m_finishObjects.remove(oldObject);
}

void hkPackfileObjectUpdateTracker::replaceObject(void* oldObject, void* newObject, const hkClass* newClass) {
    if (oldObject == m_topLevelObject) {
        m_topLevelObject = newObject;
        m_topLevelClassName = newClass->getName();
    }
    int idx = m_pointers.getFirstIndex(oldObject);
    if (newObject != 0) {
        m_pointers.m_indexMap.insert(newObject, idx);
    }
    for (; idx != -1; idx = m_pointers.m_elements[idx].m_next) {
        *m_pointers.m_elements[idx].m_value = newObject;
    }
    for (int i = 0; i < m_packfileData->m_exports.getSize(); i++) {
        if (m_packfileData->m_exports[i].m_object == oldObject) {
            m_packfileData->m_exports[i].m_object = newObject;
        }
    }
    removeFinish(oldObject);
    if (newClass != 0) {
        addFinish(newObject, newClass->getName());
    }
}

void hkPackfileObjectUpdateTracker::addChunk(void* p, int nbytes, int cl) {
    hkPackfileData* d = m_packfileData;
    hkPackfileData::Allocation a = {p, nbytes, cl};
    d->m_allocations.pushBack(a);
}

void hkPackfileObjectUpdateTracker::addAllocation(void* p) {
    hkPackfileData* d = m_packfileData;
    d->m_memory.pushBack(p);
}

void hkClassNameRegistry::merge(hkClassNameRegistry& other) {
    for (int it = other.m_map.getIterator(); other.m_map.isValid(it); it = other.m_map.getNext(it)) {
        m_map.insert(other.m_map.getKey(it), other.m_map.getValue(it));
    }
}

void hkClassNameRegistry::registerList(const hkClass* const* classes) {
    for (; *classes != 0; classes++) {
        registerClass(*classes, 0);
    }
}

template <typename Value>
int hkPointerMultiMap<Value>::getFirstIndex(void* key) const {
    return m_indexMap.m_impl.getWithDefault((hkUlong)key, (hkUlong)-1);
}

template <typename Value>
void hkPointerMultiMap<Value>::insert(void* key, const Value& value) {
    int next = m_indexMap.m_impl.getWithDefault((hkUlong)key, (hkUlong)-1);
    int idx = getFreeIndex();
    m_elements[idx].m_value = value;
    m_elements[idx].m_next = next;
    m_indexMap.m_impl.insert((hkUlong)key, idx);
}

template <typename Value>
int hkPointerMultiMap<Value>::removeByIndex(void* key, int index) {
    int next = m_elements[index].m_next;
    if (next == -1) {
        int slot = m_indexMap.m_impl.findKey((hkUlong)key);
        int head = m_indexMap.m_impl.m_elem[slot + m_indexMap.m_impl.m_hashMod + 1];
        if (head == index) {
            index = -1;
            m_indexMap.m_impl.m_elem[slot + m_indexMap.m_impl.m_hashMod + 1] = (hkUlong)-1;
        } else {
            m_elements[index] = m_elements[head];
            m_indexMap.m_impl.m_elem[slot + m_indexMap.m_impl.m_hashMod + 1] = index;
        }
    } else {
        m_elements[index] = m_elements[next];
    }
    m_elements[next].m_next = m_freeList;
    m_freeList = next;
    return index;
}

template <typename Value>
int hkPointerMultiMap<Value>::getFreeIndex() {
    int idx = m_freeList;
    if (idx != -1) {
        m_freeList = m_elements[idx].m_next;
    } else {
        idx = m_elements.m_size;
        if (m_elements.m_size == (m_elements.m_capacityAndFlags & hkArrayBase::CAPACITY_MASK)) {
            hkArrayUtil::_reserveMore(&m_elements, sizeof(Entry));
        }
        m_elements.m_size++;
    }
    return idx;
}

namespace {

int extractAndAdvanceInt(const char* base, int& offset) {
    int cur = offset;
    offset = cur + 4;
    return *(const int*)(base + cur);
}

const char* extractAndAdvanceString(const char* base, int& offset) {
    int len = 0;
    const char* s = base + offset;
    for (const char* c = s; *c != 0; c++) {
        len++;
    }
    for (; (len & 3) != 0; len++) {
    }
    offset += len;
    return s;
}

} // namespace

void hkPackfileSectionHeader::getExports(void* sectionData, hkArray<hkPackfileData::Export>& exports) const {
    int offset = 0;
    const char* table = (const char*)sectionData + m_exportsOffset;
    while (offset < m_importsOffset - m_exportsOffset) {
        int dataOffset = extractAndAdvanceInt(table, offset);
        if (dataOffset == -1) {
            break;
        }
        const char* name = extractAndAdvanceString(table, offset);
        hkPackfileData::Export& e = exports.expandOne();
        e.m_name = name;
        e.m_object = (char*)sectionData + dataOffset;
    }
}

void hkPackfileSectionHeader::getImports(void* sectionData, hkArray<hkPackfileData::Import>& imports) const {
    int offset = 0;
    const char* table = (const char*)sectionData + m_importsOffset;
    while (offset < m_endOffset - m_importsOffset) {
        int dataOffset = extractAndAdvanceInt(table, offset);
        if (dataOffset == -1) {
            break;
        }
        const char* name = extractAndAdvanceString(table, offset);
        hkPackfileData::Import& e = imports.expandOne();
        e.m_name = name;
        e.m_object = (char*)sectionData + dataOffset;
    }
}
