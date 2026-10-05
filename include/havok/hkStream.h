#pragma once

#include <havok/hkMemory.h>

// Abstract byte source. Only skip() is out-of-line; the rest are trivial defaults.
struct hkStreamReader : hkReferencedObject {
    virtual hkBool isOk() const = 0;
    virtual int read(void* buf, int nbytes) = 0;
    virtual int skip(int nbytes);
    virtual hkBool markSupported() const;
    virtual hkResult setMark(int markLimit);
    virtual hkResult rewindToMark();
    virtual hkBool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;
};

// Abstract byte sink.
struct hkStreamWriter : hkReferencedObject {
    virtual hkBool isOk() const = 0;
    virtual int write(const void* buf, int nbytes) = 0;
    virtual void flush() = 0;
    virtual hkBool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;

    void writeString(const char* s);
};

// Reads from another reader through an aligned buffer with mark/rewind support.
struct hkBufferedStreamReader : hkStreamReader {
    struct Buffer {
        char* m_buf;      // 0x00
        int m_current;    // 0x04
        int m_end;        // 0x08
        int m_bufSize;    // 0x0C
        int m_markPos;    // 0x10
        int m_markLimit;  // 0x14

        Buffer(int size);
        ~Buffer();
    };

    hkStreamReader* m_stream; // 0x08
    Buffer m_buffer;          // 0x0C

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    hkBufferedStreamReader(hkStreamReader* reader, int bufSize);
    virtual ~hkBufferedStreamReader();

    virtual hkBool isOk() const;
    virtual int read(void* buf, int nbytes);
    virtual int skip(int nbytes);
    virtual hkBool markSupported() const;
    virtual hkResult setMark(int markLimit);
    virtual hkResult rewindToMark();
    virtual hkBool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;
    virtual hkResult refillBuffer();

    void prepareBufferForRefill();
};

// Writes to another writer through an aligned buffer, or into a caller supplied memory block.
struct hkBufferedStreamWriter : hkStreamWriter {
    hkStreamWriter* m_stream; // 0x08
    char* m_buf;              // 0x0C
    int m_current;            // 0x10
    int m_capacity;           // 0x14
    hkBool m_ownsBuffer;      // 0x18

    HK_DECLARE_REF_ALLOCATOR(HK_MEMORY_CLASS_STREAM)

    hkBufferedStreamWriter(hkStreamWriter* writer, int bufSize);
    hkBufferedStreamWriter(void* buf, int bufSize, hkBool isString);
    virtual ~hkBufferedStreamWriter();

    virtual hkBool isOk() const;
    virtual int write(const void* buf, int nbytes);
    virtual void flush();
    virtual hkBool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;

    int flushBuffer();
};
