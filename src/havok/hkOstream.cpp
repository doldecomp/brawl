#include <havok/hkIostream.h>
#include <havok/hkString.h>

#pragma dont_inline on
void hkStreamWriter::writeString(const char* s) {
    if (s) {
        write(s, hkString::strLen(s));
    } else {
        write("(null)", 6);
    }
}
#pragma dont_inline reset

hkOstream::hkOstream(void* buf, int bufSize, hkBool isString) {
    m_writer = new hkBufferedStreamWriter(buf, bufSize, isString);
}

hkOstream::~hkOstream() {
    if (m_writer) {
        m_writer->removeReference();
    }
}

hkOstream& hkOstream::operator<<(char c) {
    m_writer->write(&c, 1);
    return *this;
}

hkOstream& hkOstream::operator<<(const char* s) {
    m_writer->writeString(s);
    return *this;
}

hkOstream& hkOstream::operator<<(const void* p) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%p", p);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkOstream::operator<<(hkBool b) {
    if (b) {
        m_writer->writeString("true");
    } else {
        m_writer->writeString("false");
    }
    return *this;
}

hkOstream& hkOstream::operator<<(int i) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%i", i);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkOstream::operator<<(unsigned int u) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%u", u);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkOstream::operator<<(float f) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%f", (double)f);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkOstream::operator<<(long long i) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%Li", i);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkOstream::operator<<(unsigned long long u) {
    char buf[0x400];
    hkString::snprintf(buf, 0x400, "%Lu", u);
    m_writer->writeString(buf);
    return *this;
}

hkOstream& hkEndl(hkOstream& os) {
    return os << "\r\n";
}

hkOstream& hkOstream::operator<<(hkOstream& (*manip)(hkOstream&)) {
    return manip(*this);
}

void hkOstream::printf(const char* fmt, ...) {
    char buf[0x400];
    va_list args;
    va_start(args, fmt);
    hkString::vsnprintf(buf, 0x400, fmt, args);
    va_end(args);
    m_writer->writeString(buf);
}
