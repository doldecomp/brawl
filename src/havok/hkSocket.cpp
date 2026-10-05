// HYPOTHESIS: names follow Havok's hkSocket platform init/quit bookkeeping (init flag + quit callback)
// MATCH-ONLY: hkBool needs a constructor so the false initializer is emitted as a sinit
struct hkBool {
    char m_bool;
    hkBool(bool b) : m_bool(b) {}
};

struct hkSocket {
    static void (*s_platformNetQuit)();
    static hkBool s_platformNetInitialized;
};

void (*hkSocket::s_platformNetQuit)() = 0;
hkBool hkSocket::s_platformNetInitialized(false);
