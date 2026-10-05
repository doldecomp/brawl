#include <havok/hkStream.h>

hkBool hkStreamWriter::seekTellSupported() const {
    return hkBool(false);
}

hkResult hkStreamWriter::seek(int, int) {
    return HK_FAILURE;
}

int hkStreamWriter::tell() const {
    return -1;
}
