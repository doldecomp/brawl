#include <havok/hkStream.h>

bool hkStreamWriter::seekTellSupported() const {
    return false;
}

hkResult hkStreamWriter::seek(int, int) {
    return HK_FAILURE;
}

int hkStreamWriter::tell() const {
    return -1;
}
