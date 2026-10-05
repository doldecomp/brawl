#include <havok/hkStream.h>
#include <havok/hkString.h>

#pragma dont_inline on
hkBufferedStreamReader::Buffer::Buffer(int size) {
    m_buf = (char*)hkMemory::s_instance->alignedAllocate(0x40, size, HK_MEMORY_CLASS_STREAM);
    m_current = 0;
    m_end = 0;
    m_bufSize = size;
    m_markPos = -1;
    m_markLimit = -1;
}

hkBufferedStreamReader::Buffer::~Buffer() {
    hkMemory::s_instance->alignedDeallocate(m_buf);
}
#pragma dont_inline reset

hkBufferedStreamReader::hkBufferedStreamReader(hkStreamReader* reader, int bufSize)
    : m_stream(reader), m_buffer(bufSize) {
    m_stream->addReference();
}

hkBufferedStreamReader::~hkBufferedStreamReader() {
    m_stream->removeReference();
}

void hkBufferedStreamReader::prepareBufferForRefill() {
    Buffer& b = m_buffer;
    int mark = b.m_markPos;
    if (mark < 0) {
        b.m_current = 0;
        b.m_end = 0;
    } else {
        int lead = b.m_current - mark;
        if (lead > b.m_markLimit) {
            b.m_current = 0;
            b.m_end = 0;
            b.m_markPos = -1;
            b.m_markLimit = -1;
        } else if (mark > 0) {
            int rem = lead % 512;
            int pad = rem != 0 ? 512 - rem : 0;
            hkString::memMove(b.m_buf + pad, b.m_buf + mark, lead);
            b.m_markPos = pad;
            int aligned = (lead / 512 + (rem != 0)) * 512;
            b.m_current = aligned;
            b.m_end = aligned;
        }
    }
}

hkResult hkBufferedStreamReader::refillBuffer() {
    if (!m_stream->isOk()) {
        return HK_FAILURE;
    }
    prepareBufferForRefill();
    int space = m_buffer.m_bufSize - m_buffer.m_end;
    int total = 0;
    while (total < space) {
        int n = m_stream->read(m_buffer.m_buf + m_buffer.m_current, space);
        m_buffer.m_end += n;
        total += n;
        if (n != space) {
            return total == 0;
        }
    }
    return HK_SUCCESS;
}

int hkBufferedStreamReader::read(void* buf, int nbytes) {
    char* dst = (char*)buf;
    int remaining = nbytes;
    int avail = m_buffer.m_end - m_buffer.m_current;
    while (remaining > avail) {
        hkString::memCpy(dst, m_buffer.m_buf + m_buffer.m_current, avail);
        dst += avail;
        remaining -= avail;
        m_buffer.m_current += avail;
        if (refillBuffer()) {
            return nbytes - remaining;
        }
        avail = m_buffer.m_end - m_buffer.m_current;
    }
    hkString::memCpy(dst, m_buffer.m_buf + m_buffer.m_current, remaining);
    m_buffer.m_current += remaining;
    return nbytes;
}

int hkBufferedStreamReader::skip(int nbytes) {
    int remaining = nbytes;
    int avail = m_buffer.m_end - m_buffer.m_current;
    while (remaining > avail) {
        remaining -= avail;
        if (refillBuffer()) {
            return nbytes - remaining;
        }
        avail = m_buffer.m_end - m_buffer.m_current;
    }
    m_buffer.m_current += remaining;
    return nbytes;
}

hkBool hkBufferedStreamReader::isOk() const {
    bool ok = true;
    if (m_buffer.m_current == m_buffer.m_end) {
        if (!(bool)m_stream->isOk()) {
            ok = false;
        }
    }
    return hkBool(ok);
}

hkBool hkBufferedStreamReader::markSupported() const {
    return hkBool(m_buffer.m_bufSize != 0);
}

hkResult hkBufferedStreamReader::setMark(int markLimit) {
    m_buffer.m_markLimit = markLimit;
    m_buffer.m_markPos = m_buffer.m_current;
    return markLimit > m_buffer.m_bufSize;
}

hkResult hkBufferedStreamReader::rewindToMark() {
    if (m_buffer.m_markPos >= 0) {
        m_buffer.m_current = m_buffer.m_markPos;
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

hkBool hkBufferedStreamReader::seekTellSupported() const {
    return m_stream->seekTellSupported();
}

hkResult hkBufferedStreamReader::seek(int offset, int whence) {
    m_buffer.m_markPos = -1;
    m_buffer.m_markLimit = -1;
    m_buffer.m_current = 0;
    m_buffer.m_end = 0;
    return m_stream->seek(offset, whence);
}

int hkBufferedStreamReader::tell() const {
    int t = m_stream->tell();
    if (t >= 0) {
        return t - (m_buffer.m_end - m_buffer.m_current);
    }
    return -1;
}
