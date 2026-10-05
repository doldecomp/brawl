#pragma once

#include <havok/hkArray.h>
#include <havok/hkError.h>
#include <havok/hkMemory.h>
#include <havok/hkPointerMapBase.h>
#include <havok/hkSingleton.h>
#include <havok/hkStream.h>
#include <havok/hkThreadMemory.h>

struct hkDefaultError : hkError {
    hkPointerMapBase<unsigned long> m_disabled; // 0x08
    hkArray<int> m_sections;                    // 0x14
    void (*m_outputFunc)(const char*, void*);   // 0x20
    void* m_outputContext;                      // 0x24

    virtual int message(int level, int id, const char* description, const char* file, int line);
    virtual void setEnabled(int id, hkBool enabled);
    virtual hkBool isEnabled(int id);
    virtual void enableAll();
    virtual void sectionBegin(const char* name);
    virtual void sectionEnd();
};

// Opens readers/writers for named streams.
struct hkStreambufFactory : hkSingleton<hkStreambufFactory> {
    virtual hkStreamReader* openReader(const char* name) = 0;
    virtual hkStreamWriter* openWriter(const char* name) = 0;
};

// Disc reader for the Wii/GameCube DVD (read sizes are rounded up to 32 bytes).
struct hkGameCubeDvdReader : hkStreamReader {
    char m_fileInfo[0x3C];  // 0x08 (DVDFileInfo)
    int m_position;         // 0x44
    int m_fileSize;         // 0x48

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    virtual ~hkGameCubeDvdReader();
    virtual hkBool isOk() const;
    virtual int read(void* buf, int nbytes);
    virtual hkBool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;
};

struct hkNullStreamWriter : hkStreamWriter {
    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    virtual hkBool isOk() const;
    virtual int write(const void* buf, int nbytes);
    virtual void flush();
};

struct hkDefaultStreambufFactory : hkStreambufFactory {
    virtual hkStreamReader* openReader(const char* name);
    virtual hkStreamWriter* openWriter(const char* name);
};

// Touches the singleton so it is always linked.
struct hkDummySingleton : hkSingleton<hkDummySingleton> {
    virtual void forceLinkage();

    static void* create();
};

struct hkBaseSystem {
    static hkResult init(hkMemory* memory, hkThreadMemory* threadMemory,
                         void (*errorReport)(const char*, void*), void* errorReportContext);
    static hkResult quit();
    static hkResult initThread(hkThreadMemory* threadMemory);
    static hkResult clearThreadResources();
    static void initSingletons();
    static void quitSingletons();
    static void showHavokBuild();

    static signed char s_initialized;
};
