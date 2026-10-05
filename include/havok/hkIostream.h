#pragma once

#include <havok/hkStream.h>
#include <stdarg.h>

// Input stream wrapper around a reader.
struct hkIstream : hkReferencedObject {
    hkStreamReader* m_streamReader; // 0x08

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    hkIstream(hkStreamReader* reader);
    virtual ~hkIstream();
};

// Output stream wrapper around a writer; the buffer constructor builds a string stream.
struct hkOstream : hkReferencedObject {
    hkStreamWriter* m_writer; // 0x08

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    hkOstream(void* buf, int bufSize, hkBool isString);
    virtual ~hkOstream();

    hkOstream& operator<<(char c);
    hkOstream& operator<<(const char* s);
    hkOstream& operator<<(const void* p);
    hkOstream& operator<<(hkBool b);
    hkOstream& operator<<(int i);
    hkOstream& operator<<(unsigned int u);
    hkOstream& operator<<(float f);
    hkOstream& operator<<(long long i);
    hkOstream& operator<<(unsigned long long u);
    hkOstream& operator<<(hkOstream& (*manip)(hkOstream&));
    void printf(const char* fmt, ...);
};

hkOstream& hkEndl(hkOstream& os);
