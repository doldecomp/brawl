#include <gr/gr_pirates_sling.h>
#include <ai/ai_mgr.h>

// MATCH-ONLY: keep the 20.0f constant in the stage's original constant pool.
extern const float g_piratesSlingDangerZoneHalfExtent;

void grPiratesSling::updateAI(float deltaFrame) {
    switch (m_state) {
    case State_Active:
    case State_Raising:
        if (m_mtxWork != NULL) {
            const float halfExtent = g_piratesSlingDangerZoneHalfExtent;
            // MATCH-ONLY: coordinate temporaries preserve MWCC register allocation.
            float z = m_mtxWork->m[2][3];
            float y = m_mtxWork->m[1][3];
            float x = m_mtxWork->m[0][3];
            Vec3f position(x, y, z);
            Vec2f corners[2];
            float left = position.m_x - halfExtent;
            float top = halfExtent + position.m_y;
            float bottom = position.m_y - halfExtent;
            float right = halfExtent + position.m_x;
            corners[0].m_x = left;
            corners[0].m_y = top;
            corners[1].m_x = right;
            corners[1].m_y = bottom;
            m_dangerZoneId = g_aiMgr->setDangerZone(&corners[0], &corners[1],
                                                 m_dangerZoneId, false, false);
        }
        break;
    default:
        if (m_dangerZoneId != -1) {
            g_aiMgr->delDangerZone(m_dangerZoneId);
            m_dangerZoneId = -1;
        }
        break;
    }
}
