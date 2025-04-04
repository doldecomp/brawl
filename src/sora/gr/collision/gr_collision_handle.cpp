#include <gr/collision/gr_collision_handle.h>
#include <gr/collision/gr_collision.h>
#include <types.h>

grCollisionHandle::grCollisionHandle(u16* idPtr) {
    m_id = *idPtr;
    m_idPtr = idPtr;
}

bool grCollisionHandle::isValid() {
    bool result = false;
    m_idPtr = 0;
    if (m_id != InvalidID) {
        grCollisionList::Iterator it = g_grCollisionList.GetBeginIter();
        for ( ; it != g_grCollisionList.GetEndIter(); it++) {
            if (m_id == it->m_id) {
                m_idPtr = &it->m_id;
                result = true;
                break;
            }
        }
    }
    return result;
}
