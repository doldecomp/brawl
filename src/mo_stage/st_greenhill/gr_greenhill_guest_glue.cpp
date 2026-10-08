#include <st_greenhill/gr_greenhill.h>
#include <gr/gr_calc_world_callback.h>

inline grGreenhillGuest::grGreenhillGuest(const char* taskName) : grGreenhill(taskName) {
    unk158 = NULL;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 8;
}

grGreenhillGuest* grGreenhillGuest::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grGreenhillGuest* ground = new (Heaps::StageInstance) grGreenhillGuest(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGreenhillGuest::~grGreenhillGuest() {
}

void grGreenhillGuest::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateActive(deltaFrame);
        updateCallBack(deltaFrame);
    }
}
