#include <havok/hkStream.h>
#include <havok/hkString.h>

hkBufferedStreamWriter::hkBufferedStreamWriter(hkStreamWriter* writer, int bufSize) {
    m_stream = writer;
    m_ownsBuffer = hkBool(true);
    if (m_stream) {
        m_stream->addReference();
    }
    m_buf = (char*)hkMemory::getInstance().alignedAllocate(0x40, bufSize, HK_MEMORY_CLASS_STREAM);
    m_current = 0;
    m_capacity = bufSize;
}

hkBufferedStreamWriter::hkBufferedStreamWriter(void* buf, int bufSize, hkBool isString) {
    m_stream = 0;
    m_buf = (char*)buf;
    m_current = 0;
    m_capacity = isString ? bufSize - 1 : bufSize;
    m_ownsBuffer = hkBool(false);
    if (isString) {
        hkString::memSet(buf, 0, bufSize);
    }
}

hkBufferedStreamWriter::~hkBufferedStreamWriter() {
    flush();
    if (m_stream) {
        m_stream->removeReference();
    }
    if (m_ownsBuffer) {
        hkMemory::getInstance().alignedDeallocate(m_buf);
    }
}

#pragma dont_inline on
int hkBufferedStreamWriter::flushBuffer() {
    if (m_stream) {
        int total = m_current;
        int written = 0;
        while (written < total) {
            int n = m_stream->write(m_buf + written, total - written);
            written += n;
            if (n == 0) {
                return written;
            }
        }
        m_current = 0;
        return written;
    }
    return 0;
}
#pragma dont_inline reset

int hkBufferedStreamWriter::write(const void* buf, int nbytes) {
    int space = m_capacity - m_current;
    int remaining = nbytes;
    const char* src = (const char*)buf;
    while (remaining > space) {
        hkString::memCpy(m_buf + m_current, src, space);
        src += space;
        remaining -= space;
        int newCur = m_current + space;
        m_current = newCur;
        if (newCur != flushBuffer()) {
            return nbytes - remaining;
        }
        space = m_capacity - m_current;
    }
    hkString::memCpy(m_buf + m_current, src, remaining);
    m_current += remaining;
    return nbytes;
}

void hkBufferedStreamWriter::flush() {
    flushBuffer();
    if (m_stream) {
        m_stream->flush();
    }
}

hkBool hkBufferedStreamWriter::isOk() const {
    hkBool ok;
    if (m_stream) {
        ok = m_stream->isOk();
    } else {
        ok = hkBool(m_current != m_capacity);
    }
    return ok;
}

// MATCH-ONLY: scheduling
#pragma push
#pragma scheduling off
hkBool hkBufferedStreamWriter::seekTellSupported() const {
    hkBool r;
    if (m_stream) {
        r = m_stream->seekTellSupported();
    } else {
        r = hkBool(true);
    }
    return r;
}
#pragma pop

hkResult hkBufferedStreamWriter::seek(int offset, int whence) {
    if (m_stream) {
        flushBuffer();
        return m_stream->seek(offset, whence);
    }
    int pos = -1;
    switch (whence) {
    case 0:
        pos = offset;
        break;
    case 1:
        pos = m_current + offset;
        break;
    case 2:
        pos = m_current - offset;
        break;
    }
    int result = 0;
    if (pos < 0) {
        pos = 0;
        result = 1;
    } else if (pos > m_capacity) {
        pos = m_capacity;
        result = 1;
    }
    m_current = pos;
    return result;
}

int hkBufferedStreamWriter::tell() const {
    int t;
    if (m_stream) {
        t = m_stream->tell();
    } else {
        t = 0;
    }
    if (t >= 0) {
        return t + m_current;
    }
    return -1;
}
