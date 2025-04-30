#include <gf/gf_system_callback.h>
#include <types.h>

void gfReturnStatusCallbackList::add(gfReturnStatusCallback* node) {
    if (!m_head) {
        m_head = node;
    } else {
        gfReturnStatusCallback* curr = m_head;
        while (curr->m_next) {
            curr = curr->m_next;
        }
        curr->m_next = node;
    }
}

bool gfReturnStatusCallbackList::remove(gfReturnStatusCallback* node) {
    gfReturnStatusCallback* curr = m_head;
    bool success = true;
    if (curr == node) {
        m_head = node->m_next;
    } else {
        success = false;
        if (curr == node) {
            curr = nullptr;
        }
        while (curr) {
            if (curr->m_next == node) {
                break;
            }
            curr = curr->m_next;
        }
        if (curr) {
            curr->m_next = node->m_next;
            node->m_next = nullptr;
            success = true;
        }
    }
    return success;
}

bool gfReturnStatusCallbackList::process() const {
    bool allSuccess = true;
    gfReturnStatusCallback* curr = m_head;
    while (curr) {
        bool res = curr->returnStatus();
        curr = curr->m_next;
        allSuccess = (allSuccess && res);
    }
    return allSuccess;
}

namespace {
    struct UnusedClass {
        u32 a : 8;
        u32 b : 8;
        u32 c : 8;
        u32 d : 8;
        u32 y;
        UnusedClass() : b(0), y(0) { }
    };

    UnusedClass g_unk805a00a0;
}
