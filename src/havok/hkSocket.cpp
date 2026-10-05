// HYPOTHESIS: platform socket layer state (unused on this platform; only the
// static-init flag survives in the binary).
struct hkSocketState {
    bool m_initialized;
    hkSocketState() : m_initialized(false) {}
};

void* g_hkSocketUnk = 0;
hkSocketState g_hkSocketState;
