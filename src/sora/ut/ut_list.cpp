#include <types.h>
#include <ut/ut_list.h>

void utList::addTail(utListNode* node) {
    if (!m_length) {
        node->m_next = nullptr;
        node->m_prev = nullptr;
        if (m_head) {
            m_head->m_prev = node;
            node->m_next = m_head;
        }
        m_head = node;
        m_tail = node;
        m_length++;
    } else {
        node->m_prev = m_tail;
        node->m_next = nullptr;
        m_tail->m_next = node;
        m_tail = node;
        m_length++;
    }
}

void utList::remove(utListNode* node) {
    utListNode* next = node->m_next;
    utListNode* prev = node->m_prev;
    if (next) {
        next->m_prev = prev;
    } else {
        m_tail = prev;
    }

    if (prev) {
        prev->m_next = next;
    } else {
        m_head = next;
    }
    node->m_prev = nullptr;
    node->m_next = nullptr;
    m_length--;
}

bool utList::removeExist(utListNode* node) {
    if (isExistNode(node) != -1) {
        remove(node);
        return true;
    }
    return false;
}

utListNode* utList::getNode(u32 index) {
    if (m_length) {
        if (index == 0) {
            return m_head;
        }
        utListNode* curr = m_head;
        s32 i = 0;
        for ( ; curr; curr = curr->m_next, i++) {
            if (index == i) {
                return curr;
            }
        }
    }
    return nullptr;
}

s32 utList::isExistNode(utListNode* node) const {
    if (m_length) {
        utListNode* curr;
        s32 i;
        for (curr = m_head, i = 0; curr; curr = curr->m_next, i++) {
            if (curr == node) {
                return i;
            }
        }
    }
    return -1;
}
