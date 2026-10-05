#include <havok/hkPackfile.h>

hkPackfileData::hkPackfileData() : m_name(0) {
}

void hkPackfileData::callDestructors() {
    for (int it = hkPointerMapGetFirstIndex(m_trackedObjects.m_impl); hkPointerMapIsValid(m_trackedObjects.m_impl, it);
         it = hkPointerMapGetNext(m_trackedObjects.m_impl, it)) {
        const hkTypeInfo* info = (const hkTypeInfo*)hkPointerMapGetValue(m_trackedObjects.m_impl, it);
        if (info->m_cleanup != 0) {
            info->m_cleanup((void*)hkPointerMapGetKey(m_trackedObjects.m_impl, it));
        }
    }
    m_trackedObjects.m_impl.clear();
}

hkPackfileData::~hkPackfileData() {
    callDestructors();
    int i = 0;
    hkMemory& mem = hkMemory::getInstance();
    for (; i < m_memory.getSize(); i++) {
        mem.deallocate(m_memory[i]);
    }
    for (i = 0; i < m_allocations.getSize(); i++) {
        mem.deallocateChunk(m_allocations[i].m_pointer, m_allocations[i].m_size, m_allocations[i].m_class);
    }
    hkMemory::getInstance().deallocate(m_name);
}

void hkPackfileData::getImportsExports(hkArray<Export>& exports, hkArray<Import>& imports) {
    exports = m_exports;
    imports = m_imports;
}

void hkPackfileData::addExport(const char* name, void* object) {
    Export e;
    e.m_name = name;
    e.m_object = object;
    m_exports.pushBack(e);
}

void hkPackfileData::addImport(const char* name, void* object) {
    Import i;
    i.m_name = name;
    i.m_object = object;
    m_imports.pushBack(i);
}
