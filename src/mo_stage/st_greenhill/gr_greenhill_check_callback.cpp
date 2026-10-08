#include <st_greenhill/gr_greenhill.h>
#include <gr/gr_calc_world_callback.h>

// The ball model is moved by a world-calc callback: it follows the marker position the random order currently selects.
void grGreenhillCheck::updateCallBack(float deltaFrame) {
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
            if (unk164 != NULL) {
                grNodeCallbackData* callbackData = calcWorldCallBack->m_nodeCallbackDatas;
                Vec3f* marker = &unk164[m_order[0]];
                callbackData->m_pos.m_x = marker->m_x;
                callbackData->m_pos.m_y = marker->m_y;
                callbackData->m_pos.m_z = marker->m_z;
            }
        }
    }
}
