#include <havok/hkIostream.h>

hkIstream::hkIstream(hkStreamReader* reader) {
    m_streamReader = reader;
    m_streamReader->addReference();
}

hkIstream::~hkIstream() {
    if (m_streamReader) {
        m_streamReader->removeReference();
    }
}
