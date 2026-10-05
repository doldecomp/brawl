#pragma once

#include <types.h>

// Havok 4.0 base object hierarchy (reconstructed from asm).
// No RTTI: vtable slot 0/1 are unused, slot 2 is the virtual destructor.

// Small-struct bool: passed/returned as an aggregate (copied to the stack for by-value args).
struct hkBool {
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b) {}
    operator bool() const {
        return m_bool != 0;
    }
    hkBool operator!() const {
        return hkBool(m_bool == 0);
    }
};

typedef int hkResult;
enum { HK_SUCCESS = 0, HK_FAILURE = 1 };

struct hkStatisticsCollector;

struct hkBaseObject {
    virtual ~hkBaseObject() {}
};

struct hkReferencedObject : hkBaseObject {
    u16 m_memSizeAndFlags; // 0x04
    s16 m_referenceCount;  // 0x06

    hkReferencedObject() : m_referenceCount(1) {}
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(hkStatisticsCollector* collector) const;

    void addReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount++;
        }
    }

    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            if (--m_referenceCount == 0) {
                delete this;
            }
        }
    }
};

// Singleton registration node: filled by a static constructor in each singleton's TU.
struct hkSingletonInitNode {
    void* (*m_create)();           // 0x00
    hkSingletonInitNode* m_next;   // 0x04
    void** m_instance;             // 0x08

    static hkSingletonInitNode* s_head;

    hkSingletonInitNode(void* (*create)(), void** instance)
    {
        m_create = create;
        m_instance = instance;
        m_next = s_head;
        s_head = this;
    }
};
