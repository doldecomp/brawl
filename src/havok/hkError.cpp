#include <havok/hkError.h>
#include <havok/hkIostream.h>

// MATCH-ONLY: reference counting diagnostics from the inline hkReferencedObject code. The
// function itself is discarded at link time, but its string literals stay in this unit's pool.
__declspec(weak) void hkReferencedObject_refCountError(const hkReferencedObject* obj, const char* where) {
    char buf[0x200];
    hkOstream os(buf, 0x200, hkBool(true));
    os << "Reference count error on object " << (const void*)obj << " with ref count of "
       << (int)obj->m_referenceCount << " in " << where << ".\n"
       << " * Are you calling delete instead of removeReference?\n"
       << " * Have you called removeReference too many times?\n"
       << " * Is this a valid object?\n"
       << " * Do you have more than 32768 references? (unlikely)\n";
    hkErrorMessage(buf);
}

void hkErrorMessage(const char* msg) {
    char buf[0x200];
    hkBool isString(true);
    hkOstream os(buf, 0x200, isString);
    os << msg;
    hkError::getInstance().message(3, 0x2636FE25, buf, "hkError.cpp", 27);
}
