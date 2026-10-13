#pragma once

#include <StaticAssert.h>
#include <types.h>

/// Node object for utList
class utListNode {
public:
    utListNode* m_next;
    utListNode* m_prev;
};
static_assert(sizeof(utListNode) == 0x8, "Class is the wrong size!");

/// Non-intrusive doubly-linked list with a head and tail
class utList {
    utListNode* m_head;
    utListNode* m_tail;
    u32 m_length;
public:
    /// Make node the new tail of the linked list
    void addTail(utListNode* node);

    /// Remove node from the list, assuming it is present
    void remove(utListNode* node);

    /// If node is not in the list, return false, else remove it and return true
    bool removeExist(utListNode* node);

    /// Get the node at the specified index
    utListNode* getNode(u32 index);

    /// If node is not present, return -1, else return its position in the list
    s32 isExistNode(utListNode* node) const;

    inline void clear() {
        m_head = nullptr;
        m_tail = nullptr;
        m_length = 0;
    }
};
static_assert(sizeof(utList) == 0xC, "Class is the wrong size!");
