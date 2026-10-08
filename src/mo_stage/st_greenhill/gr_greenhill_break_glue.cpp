#include <st_greenhill/gr_greenhill.h>
#include <gr/gr_calc_world_callback.h>
#include <memory.h>

// MATCH-ONLY: the stage's float constant pool (0.0f).
extern const float g_greenhillBreakConstants[]; // [0] = 0.0f

// MATCH-ONLY: passing the offset by value reproduces the original's temporary copies.
static inline void assignVec2f(Vec2f& dst, Vec2f src) {
    dst = src;
}

grGreenhillBreak* grGreenhillBreak::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grGreenhillBreak* ground = new (Heaps::StageInstance) grGreenhillBreak(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGreenhillBreak::grGreenhillBreak(const char* taskName) : grGreenhill(taskName) {
    unk158 = g_greenhillBreakConstants[0];
    unk15C = g_greenhillBreakConstants[0];
    unk160 = g_greenhillBreakConstants[0];
    unk164 = NULL;
    m_type = 3;
    unk170 = g_greenhillBreakConstants[0];
    m_animId = 1;
    unk178 = g_greenhillBreakConstants[0];
    m_nodeA = 0;
    m_nodeB = 0;
    unk184 = 0;
    m_joint = NULL;
    unk18C = 0;
    unk18D = 0;
    unk190[0] = NULL;
    unk190[1] = NULL;
    unk190[2] = NULL;
    unk190[3] = NULL;
    unk190[4] = NULL;
    createSoundWork(1, 1);
    m_soundEffects[0].m_id = 0x1d19;
    m_soundEffects[0].m_repeatFrame = 0;
    m_soundEffects[0].m_nodeIndex = 0;
    m_soundEffects[0].m_endFrame = 0;
    assignVec2f(m_soundEffects[0].m_offsetPos, Vec2f(g_greenhillBreakConstants[0], g_greenhillBreakConstants[0]));
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 1;
}

grGreenhillBreak::~grGreenhillBreak() {
    if (unk190[0] != NULL) {
        delete[] static_cast<u8*>(unk190[0]);
    }
    unk190[0] = NULL;
    if (unk190[1] != NULL) {
        delete[] static_cast<u8*>(unk190[1]);
    }
    unk190[1] = NULL;
    if (unk190[2] != NULL) {
        delete static_cast<u8*>(unk190[2]);
    }
    unk190[2] = NULL;
    if (unk190[3] != NULL) {
        delete static_cast<u8*>(unk190[3]);
    }
    unk190[3] = NULL;
    if (unk190[4] != NULL) {
        delete static_cast<u8*>(unk190[4]);
    }
    unk190[4] = NULL;
}

void grGreenhillBreak::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateJoint(deltaFrame);
        updateYakumono(deltaFrame);
        updateBreak(deltaFrame);
    }
}
