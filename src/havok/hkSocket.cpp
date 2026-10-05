// HYPOTHESIS: platform socket layer state (unused on this platform; only the
// shutdown hook and static-init flag survive in the binary).
struct hkSocketState {
    bool m_initialized;
    hkSocketState() : m_initialized(false) {}
};

void (*g_hkSocketShutdown)() = 0;
hkSocketState g_hkSocketState;
