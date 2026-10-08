// MATCH-ONLY: this unit calls the grFzero constructor/destructor out of line.
#define GR_FZERO_BASE_EXTERNAL
#include <st_fzero/gr_fzero.h>
#include <gr/gr_calc_world_callback.h>

inline grFzeroPlateRing::grFzeroPlateRing(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_mtxWork = NULL;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 8;
}

grFzeroPlateRing* grFzeroPlateRing::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroPlateRing* ground = new (Heaps::StageInstance) grFzeroPlateRing(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroPlateRing::~grFzeroPlateRing() {
}

void grFzeroPlateRing::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateCallBack(deltaFrame);
    }
}

// The model follows the stage matrix.
void grFzeroPlateRing::updateCallBack(float deltaFrame) {
    grCalcWorldCallBack* calcWorldCallBack = &m_calcWorldCallBack;
    if (calcWorldCallBack != NULL) {
        nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
        if (scnMdl != NULL) {
            if (scnMdl->m_calcWorldCallBack == NULL) {
                calcWorldCallBack->m_index = 0;
                calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex = m_nodeIndex;
                scnMdl->m_calcWorldCallBack = calcWorldCallBack;
                scnMdl->EnableScnMdlCallbackTiming(1);
                scnMdl->m_nodeIndex = calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex;
            }
            if (m_mtxWork != NULL) {
                calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix = *m_mtxWork;
            }
        }
    }
}
