#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/st_greenhill.h>
#include <gr/gr_calc_world_callback.h>

// MATCH-ONLY: the stage's float constant pool.
extern const float g_greenhillGuestAngle; // rotation applied to the guest's matrix

// The guest model follows the matrix the stage keeps for it (turned by a fixed angle), and its sound follows the model.
void grGreenhillGuest::updateCallBack(float deltaFrame) {
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
            float posZ = unk158->unk04(2, 3);
            float posY = unk158->unk04(1, 3);
            float posX = unk158->unk04(0, 3);
            Vec3f pos(posX, posY, posZ);
            Vec3f rot;
            unk158->unk04.getRotate(&rot);
            Matrix matrix;
            matrix = unk158->unk04;
            Matrix identity;
            matrix.rotY(g_greenhillGuestAngle);
            matrix.mul(&identity, &matrix);
            calcWorldCallBack->m_nodeCallbackDatas[0].m_matrix = matrix;
            m_sndGenerator.setPos(&pos);
        }
    }
}
