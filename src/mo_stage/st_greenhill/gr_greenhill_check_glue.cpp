#include <st_greenhill/gr_greenhill.h>
#include <gr/gr_calc_world_callback.h>
#include <memory.h>

grGreenhillCheck* grGreenhillCheck::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grGreenhillCheck* ground = new (Heaps::StageInstance) grGreenhillCheck(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGreenhillCheck::grGreenhillCheck(const char* taskName) : grGreenhill(taskName) {
    m_timer2 = 0.0f;
    unk15C = NULL;
    unk160 = NULL;
    unk164 = NULL;
    m_order[0] = 4;
    m_order[1] = 4;
    m_order[2] = 4;
    m_order[3] = 4;
    m_orderDone = 0;
    m_hitTeam = 0;
    m_animId = 5;
    unk17C = 0.0f;
    m_motionEndFrame = 0.0f;
    unk184 = 0;
    m_attackEnabled = 0;
    unk188[0] = NULL;
    unk188[1] = NULL;
    unk188[2] = NULL;
    unk188[3] = NULL;
    unk188[4] = NULL;
    m_dangerZoneId = -1;
    m_effectId = 0;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 1;
}

grGreenhillCheck::~grGreenhillCheck() {
    if (unk188[0] != NULL) {
        delete static_cast<u8*>(unk188[0]);
    }
    unk188[0] = NULL;
    if (unk188[1] != NULL) {
        delete static_cast<u8*>(unk188[1]);
    }
    unk188[1] = NULL;
    if (unk188[2] != NULL) {
        delete static_cast<u8*>(unk188[2]);
    }
    unk188[2] = NULL;
    if (unk188[3] != NULL) {
        delete static_cast<u8*>(unk188[3]);
    }
    unk188[3] = NULL;
    if (unk188[4] != NULL) {
        delete static_cast<u8*>(unk188[4]);
    }
    unk188[4] = NULL;
}

// Runs the three Check updates once the gimmick is running.
void grGreenhillCheck::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateYakumono(deltaFrame);
        updateActive(deltaFrame);
        updateCallBack(deltaFrame);
    }
}

// The hit model/yakumono is built the first time the ball needs it.
void grGreenhillCheck::updateYakumono(float deltaFrame) {
    if (unk184 != 1) {
        setHit();
        if (m_yakumono != NULL) {
            unk184 = 1;
        }
    }
}
