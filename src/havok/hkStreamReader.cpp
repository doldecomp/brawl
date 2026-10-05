#include <havok/hkStream.h>

int hkStreamReader::skip(int nbytes) {
    char buf[0x200];
    int remaining = nbytes;
    while (remaining != 0) {
        int chunk = remaining > 0x200 ? 0x200 : remaining;
        int got = read(buf, chunk);
        if (got == 0) {
            break;
        }
        remaining -= got;
    }
    return nbytes - remaining;
}

hkBool hkStreamReader::markSupported() const {
    return hkBool(false);
}

hkResult hkStreamReader::setMark(int) {
    return HK_FAILURE;
}

hkResult hkStreamReader::rewindToMark() {
    return HK_FAILURE;
}

hkBool hkStreamReader::seekTellSupported() const {
    return hkBool(false);
}

hkResult hkStreamReader::seek(int, int) {
    return HK_FAILURE;
}

int hkStreamReader::tell() const {
    return -1;
}
