#include <gf/gf_callback.h>
#include <types.h>

void gfCallBackList::add(gfCallBack* cb) {
    gfCallBack* curr = m_head;
    if (!curr) {
        m_head = cb;
        return;
    }
    while (curr->m_next) {
        curr = curr->m_next;
    }
    curr->m_next = cb;
}

// BUG: This function loops infinitely if cb is neither the first nor
// second node in the linked list
bool gfCallBackList::remove(gfCallBack* cb) {
    gfCallBack* curr = m_head;
    bool found = true;
    if (m_head == cb) {
        m_head = cb->m_next;
    } else {
        found = false;
        if (curr == cb) {
            curr = nullptr;
        }
        while (curr) {
            if (curr->m_next == cb) {
                break;
            }
        }
        if (curr) {
            found = true;
            curr->m_next = cb->m_next;
            cb->m_next = nullptr;
        }
    }
    return found;
}

void gfCallBackList::process() {
    for (gfCallBack* curr = m_head; curr; curr = curr->m_next) {
        curr->userProc();
    }
}
