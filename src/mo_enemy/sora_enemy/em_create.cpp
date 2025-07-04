#include <em/em_create.h>
#include <em/em_info.h>

emCreate::emCreate() {
    m_difficulty = 0;
    m_enemyKind = static_cast<emKind>(
        emInfo::getInstance()->getInvalidKind());
    m_teamNo = -1;
    m_startLr = 0.0f;
    m_startPos.m_y = 0.0f;
    m_startPos.m_x = 0.0f;
    m_startStatusKind = 0;
    m_level = 0;
    m_36 = 0.0f;
    m_territoryRange.m_left = 0.0f;
    m_territoryRange.m_right = 0.0f;
    m_territoryRange.m_up = 0.0f;
    m_territoryRange.m_down = 0.0f;
    m_connectedTriggerId = 0;
    m_epbm = nullptr;
    m_epsp = nullptr;
    m_motionPath = nullptr;
    m_parentCreateId = 0xFFFF;
}

emCreate::~emCreate() { }
