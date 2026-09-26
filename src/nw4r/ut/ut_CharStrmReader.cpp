#include <nw4r/ut/ut_CharStrmReader.h>

namespace nw4r {
namespace ut {

u16 CharStrmReader::ReadNextCharUTF8() {
    u16 ch = GetChar<u8>(0);
    if ((ch & 0x80) == 0) {
        StepStrm<u8>(1);
    } else if ((ch & 0xE0) == 0xC0) {
        ch = ((ch & 0x1F) << 6) | (GetChar<u8>(1) & 0x3F);
        StepStrm<u8>(2);
    } else {
        u8 second = GetChar<u8>(1);
        u8 third = GetChar<u8>(2);
        ch = ((ch & 0x1F) << 12) | ((second & 0x3F) << 6) | (third & 0x3F);
        StepStrm<u8>(3);
    }
    return ch;
}

u16 CharStrmReader::ReadNextCharUTF16() {
    u16 ch = GetChar<u16>(0);
    StepStrm<u16>(1);
    return ch;
}

u16 CharStrmReader::ReadNextCharCP1252() {
    u16 ch = GetChar<u8>(0);
    StepStrm<u8>(1);
    return ch;
}

u16 CharStrmReader::ReadNextCharSJIS() {
    u16 ch;
    u8 first = GetChar<u8>(0);
    bool twoBytes = (first >= 0x81 && first < 0xA0) || first >= 0xE0;
    if (twoBytes) {
        ch = (first << 8) | GetChar<u8>(1);
        StepStrm<u8>(2);
    } else {
        ch = first;
        StepStrm<u8>(1);
    }
    return ch;
}

} // namespace ut
} // namespace nw4r
