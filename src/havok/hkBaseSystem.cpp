#include <havok/hkBaseSystem.h>
#include <havok/hkIostream.h>
#include <havok/hkMonitorStream.h>
#include <havok/hkMultiThreadLock.h>
#include <havok/hkStackTracer.h>
#include <havok/hkString.h>
#include <revolution/DVD.h>

extern "C" s32 DVDSeekPrio(DVDFileInfo* info, s32 offset, s32 prio);

extern void (*g_hkSocketShutdown)();
extern char g_hkSocketState;

signed char hkBaseSystem::s_initialized = 0;

template <>
hkDummySingleton* hkSingleton<hkDummySingleton>::s_instance = 0;
template <>
hkError* hkSingleton<hkError>::s_instance = 0;
hkMemory* hkMemory::s_instance = 0;

void hkBaseSystem::showHavokBuild() {}

void hkBaseSystem::initSingletons() {
    hkArray<hkSingletonInitNode*> pending;
    hkSingletonInitNode** link = &hkSingletonInitNode::s_head;
    hkSingletonInitNode* node = hkSingletonInitNode::s_head;
    while (node != 0) {
        if (*node->m_instance == 0) {
            void* inst = node->m_create();
            if (inst != 0) {
                *node->m_instance = inst;
                link = &node->m_next;
                node = node->m_next;
            } else {
                pending.pushBack(node);
                node = node->m_next;
                (*link)->m_next = 0;
                *link = node;
            }
        } else {
            link = &node->m_next;
            node = node->m_next;
        }
    }
    while (pending.m_size != 0) {
        for (int i = pending.m_size - 1; i >= 0; i--) {
            hkSingletonInitNode* n = pending[i];
            void* inst = n->m_create();
            if (inst != 0) {
                *n->m_instance = inst;
                *link = n;
                link = &n->m_next;
                pending.m_size--;
                pending[i] = pending[pending.m_size];
            }
        }
    }
}

void hkBaseSystem::quitSingletons() {
    hkInplaceArray<hkSingletonInitNode*, 128> nodes;
    for (hkSingletonInitNode* n = hkSingletonInitNode::s_head; n != 0; n = n->m_next) {
        nodes.pushBack(n);
    }
    for (int i = nodes.m_size - 1; i >= 0; i--) {
        ((hkReferencedObject*)*nodes[i]->m_instance)->removeReference();
        *nodes[i]->m_instance = 0;
    }
}

hkResult hkBaseSystem::initThread(hkThreadMemory* threadMemory) {
    hkThreadMemory::init();
    hkThreadMemory::replaceInstance(threadMemory);
    hkMonitorStream::init();
    return HK_SUCCESS;
}

hkResult hkBaseSystem::init(hkMemory* memory, hkThreadMemory* threadMemory,
                            void (*errorReport)(const char*, void*), void* errorReportContext) {
    if (!s_initialized) {
        hkMonitorStream::init();
        if (memory == 0) {
            *(int*)0 = 0;
            return HK_FAILURE;
        }
        hkMemory::replaceInstance(memory);
        if (threadMemory == 0) {
            void* mem = g_hkMalloc(0x320, 0x10);
            hkThreadMemory* tm = (hkThreadMemory*)mem;
            if (mem != 0) {
                tm = ::new (mem) hkThreadMemory(memory, 0x10);
            }
            initThread(tm);
            tm->removeReference();
        } else {
            initThread(threadMemory);
        }
        hkDefaultStreambufFactory* factory = new hkDefaultStreambufFactory();
        if (hkStreambufFactory::s_instance) {
            hkStreambufFactory::s_instance->removeReference();
        }
        hkStreambufFactory::s_instance = factory;
        hkDefaultError* error = new hkDefaultError();
        error->m_outputFunc = errorReport;
        error->m_outputContext = errorReportContext;
        if (hkError::s_instance) {
            hkError::s_instance->removeReference();
        }
        hkError::s_instance = error;
        initSingletons();
        hkDummySingleton::getInstance().forceLinkage();
        s_initialized = 1;
        showHavokBuild();
        hkMultiThreadLock::staticInit();
    }
    return HK_SUCCESS;
}

void hkDummySingleton::forceLinkage() {}

hkResult hkBaseSystem::clearThreadResources() {
    hkMonitorStream::s_instance.quit();
    hkThreadMemory::s_instance->releaseCachedMemory();
    hkThreadMemory::replaceInstance(0);
    hkThreadMemory::quit();
    return HK_SUCCESS;
}

// MATCH-ONLY: inline reference release written out by hand (quit() must not inline quitSingletons).
#define HK_RELEASE(T, var)                              {                                                       T* p_ = var;                                        if (p_) {                                               if (p_->m_memSizeAndFlags != 0) {                       if (--p_->m_referenceCount == 0) {                      delete p_;                                      }                                               }                                               }                                               }

#pragma dont_inline on
hkResult hkBaseSystem::quit() {
    bool initialized = s_initialized == 1;
    if (initialized) {
        hkMultiThreadLock::staticQuit();
        quitSingletons();
        if (g_hkSocketState && g_hkSocketShutdown) {
            g_hkSocketShutdown();
            g_hkSocketState = 0;
        }
        HK_RELEASE(hkError, hkError::s_instance);
        hkError::s_instance = 0;
        HK_RELEASE(hkStreambufFactory, hkStreambufFactory::s_instance);
        hkStreambufFactory::s_instance = 0;
        clearThreadResources();
        hkMemory::replaceInstance(0);
        s_initialized = 0;
    }
    return HK_SUCCESS;
}
#pragma dont_inline reset

void* hkDummySingleton::create() {
    return new hkDummySingleton();
}

hkStreamWriter* hkDefaultStreambufFactory::openWriter(const char* name) {
    hkNullStreamWriter* sink = new hkNullStreamWriter();
    hkStreamWriter* writer = new hkBufferedStreamWriter(sink, 0x1000);
    sink->removeReference();
    return writer;
}

hkStreamReader* hkDefaultStreambufFactory::openReader(const char* name) {
    hkGameCubeDvdReader* dvd = new hkGameCubeDvdReader();
    dvd->m_position = -1;
    dvd->m_fileSize = -1;
    if (DVDOpen(name, (DVDFileInfo*)dvd->m_fileInfo) == 1) {
        dvd->m_fileSize = ((DVDFileInfo*)dvd->m_fileInfo)->size;
        dvd->m_position = 0;
    }
    if (!dvd->markSupported()) {
        hkStreamReader* reader = new hkBufferedStreamReader(dvd, 0x1000);
        dvd->removeReference();
        return reader;
    }
    return dvd;
}

void hkNullStreamWriter::flush() {}

hkBool hkNullStreamWriter::isOk() const {
    return hkBool(false);
}

int hkNullStreamWriter::write(const void* buf, int nbytes) {
    return 0;
}

int hkGameCubeDvdReader::tell() const {
    return m_position;
}

hkResult hkGameCubeDvdReader::seek(int offset, int whence) {
    int pos = 0;
    switch (whence) {
    case 0:
        pos = offset;
        break;
    case 1:
        pos = m_position + offset;
        break;
    case 2:
        pos = m_fileSize + offset;
        break;
    }
    if (DVDSeekPrio((DVDFileInfo*)m_fileInfo, pos, 2) == 0) {
        m_position = pos;
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

hkBool hkGameCubeDvdReader::seekTellSupported() const {
    return hkBool(true);
}

int hkGameCubeDvdReader::read(void* buf, int nbytes) {
    if (isOk()) {
        if (m_position + nbytes > m_fileSize) {
            nbytes = (m_fileSize - m_position + 0x1F) & ~0x1F;
        }
        int n = DVDReadPrio((DVDFileInfo*)m_fileInfo, buf, nbytes, m_position, 2);
        if (n >= 1) {
            m_position += n;
            return n;
        }
        m_position = m_fileSize + 1;
    }
    return 0;
}

hkBool hkGameCubeDvdReader::isOk() const {
    bool ok;
    __typeof__(m_fileSize) tmp0 = m_fileSize;
    ok = false;
    __typeof__(tmp0) tmp1 = tmp0;
    if (( tmp1 >= 0) && (m_position <= m_fileSize)) {
        ok = true;
    }
    return hkBool(ok);
}


hkGameCubeDvdReader::~hkGameCubeDvdReader() {
    if (m_fileSize != -1) {
        DVDClose((DVDFileInfo*)m_fileInfo);
    }
}

void hkDefaultError::sectionEnd() {
    m_sections.m_size--;
}

void hkDefaultError::sectionBegin(const char* name) {
    m_sections.pushBack((int)name);
}

int hkDefaultError::message(int level, int id, const char* description, const char* file, int line) {
    if (id == -1 && m_sections.m_size != 0) {
        id = m_sections[m_sections.m_size - 1];
    }
    if (!isEnabled(id)) {
        return 0;
    }
    const char* levelName = "";
    bool printTrace = false;
    switch (level) {
    case 0:
        levelName = "Report";
        break;
    case 1:
        levelName = "Warning";
        break;
    case 2:
        printTrace = true;
        levelName = "Assert";
        break;
    case 3:
        printTrace = true;
        levelName = "Error";
        break;
    }
    char idText[12];
    hkString::sprintf(idText, "0x%x", id);
    char buf[0x200];
    hkBool isString(true);
    hkOstream os(buf, 0x200, isString);
    os << file << '(' << line << "): [" << idText << "] " << levelName << " : '" << description
       << "'\n";
    m_outputFunc(buf, m_outputContext);
    if (printTrace) {
        hkStackTracer tracer;
        unsigned long trace[20];
        int n = tracer.getStackTrace(trace, 20);
        if (n > 2) {
            m_outputFunc("Stack trace is:\n", m_outputContext);
            tracer.dumpStackTrace(trace + 2, n - 2, m_outputFunc, m_outputContext);
        }
    }
    return level == 2 || level == 3;
}

hkBool hkDefaultError::isEnabled(int id) {
    return hkBool(m_disabled.getWithDefault(id, 0) == 0);
}

void hkDefaultError::enableAll() {
    m_disabled.clear();
}

void hkDefaultError::setEnabled(int id, hkBool enabled) {
    if (enabled) {
        m_disabled.remove(id);
    } else {
        m_disabled.insert(id, 1);
    }
}

static hkSingletonInitNode hkDummySingleton_initNode(
    hkDummySingleton::create, (void**)&hkSingleton<hkDummySingleton>::s_instance);
