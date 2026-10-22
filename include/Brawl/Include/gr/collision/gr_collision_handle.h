#pragma once

#include <types.h>

class grCollisionHandle {
    u16* m_idPtr;
    u16 m_id;
    static const u32 InvalidID = 0x0000FFFFu;
    // TODO more fields?
public:
    grCollisionHandle(u16* idPtr);
    bool isValid();
};
// TODO size assertion
