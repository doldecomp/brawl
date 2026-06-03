#include <st_tengan/gr_tengan_ashiba.h>
#include <st_tengan/st_tengan_data.h>
#include <ec/ec_mgr.h>
#include <mt/mt_prng.h>
#include <memory.h>

grTenganAshiba* grTenganAshiba::create(int mdlIndex, const char* tgtNodeName, const char* taskName)
{
    grTenganAshiba* ground = new (Heaps::StageInstance) grTenganAshiba(taskName);
	if (ground) {	
	    ground->setMdlIndex(mdlIndex);
	    ground->setTgtNode(tgtNodeName);
	}
	ground->setupMelee();

    return ground;
}

grTenganAshiba::grTenganAshiba(const char* taskName) : grTengan(taskName) {
    grCalcWorldCallBack *callback = &m_calcWorldCallBack;
    m_ashibaState = 0;
    m_ashibaTimer = 0.0f;
    m_posLimitWork = NULL;
    m_ashibaPos.m_x = 0.0f;
    m_ashibaPos.m_y = 0.0f;
    m_ashibaPos.m_z = 0.0f;
    m_ashibaPosY = 0.0f;
    m_speed = 0.0f;
    m_isMovingUp = 0;
    unk1F1 = 0;
    if (callback == NULL) {
        return;
    }
        callback->m_numNodeCallbackData = 1;
        callback->initialize(false, Heaps::StageInstance);
        callback->m_nodeCallbackDatas[0].m_flags |= 1;
        //m_calcWorldCallBack.m_nodeCallbackDatas[0].m_flag2 = true;
        //this->setupMelee();
//    }
}

grTenganAshiba::~grTenganAshiba() {
	
}

void grTenganAshiba::update(float deltaFrame)
{
    if (m_isUpdate) {
        updateMove(deltaFrame);
        updateCallBack(deltaFrame);
        grTengan::update(deltaFrame);
    }
}

void grTenganAshiba::updateMove(float deltaFrame) {
    if (m_posLimitWork != NULL) {
        stTenganParams* tenganData = (stTenganParams*)getStageData();
        if (tenganData != NULL) {
        if (m_posLimitWork[0].m_y != m_posLimitWork[1].m_y) {
            float fVar1 = m_ashibaTimer - deltaFrame;
            m_ashibaTimer = fVar1;
            if (fVar1 < 0.0f) {
                m_ashibaTimer = 0.0f;
            }
            switch(m_ashibaState) {
                case 0:
                    m_ashibaPos.m_x = m_posLimitWork[1].m_x;
                    m_ashibaPos.m_y = m_posLimitWork[1].m_y;
                    m_ashibaPos.m_z = m_posLimitWork[1].m_z;
                    m_ashibaPos.m_y += (m_posLimitWork[0].m_y - m_posLimitWork[1].m_y)* randf();
                    if (randf() < 0.5f) {
                        m_isMovingUp = 1;
                    } else {
                        m_isMovingUp = 0;
                    }
                    m_ashibaState = 1;
                case 1:
                    if (m_ashibaTimer == 0.0f) {
                        m_speed = 0.0f;
                        unk1F1 = 0;
                        m_ashibaState = 2;
                    }
                    break;
                case 2:
                    bool isForceTurn = 0;
                    bool isTurn = 0;
                    fVar1 = m_speed + tenganData->yuka_fly_accel;
                    m_speed = fVar1;
                    if (fVar1 > tenganData->yuka_fly_speed_max) {
                        m_speed = tenganData->yuka_fly_speed_max;
                    }
                    if (unk1F1 == 0 and m_speed == tenganData->yuka_fly_speed_max) {
                        if (randf() < tenganData->yuka_fly_rate_turn) {
                            isForceTurn = true;//(randf() < tenganData->yuka_fly_rate_turn);
                        }
                        unk1F1 = 1;
                    }
                    if (isForceTurn == true) {
                        isTurn = true;
                    } else if (m_isMovingUp == 1) {
                        fVar1 = m_speed * deltaFrame;
                        m_ashibaPos.m_y += fVar1;
                        if (m_ashibaPos.m_y >= m_posLimitWork[0].m_y) {
                            isTurn = true;
                        }
                    } else {
                        fVar1 = m_speed * deltaFrame;
                        m_ashibaPos.m_y -= fVar1;
                        if (m_ashibaPos.m_y <= m_posLimitWork[1].m_y) {
                            isTurn = true;
                        }
                    }
                    if (isTurn == true) {
                        m_ashibaState = 3;
                        m_ashibaPosY = m_ashibaPos.m_y;
                    }
                    break;
                case 3:
                    fVar1 = m_speed - tenganData->yuka_fly_accel;
                    m_speed = fVar1;
                    if (fabs(fVar1) > tenganData->yuka_fly_speed_max) {
                        m_speed = tenganData->yuka_fly_speed_max * -1.0f;
                    }
                    if (m_isMovingUp == true) {
                        m_ashibaPos.m_y += m_speed * deltaFrame;
                    } else {
                        m_ashibaPos.m_y -= m_speed * deltaFrame;
                    }
                    if (((m_isMovingUp == true) and (m_ashibaPosY > m_ashibaPos.m_y))
                    ||((m_isMovingUp == false) and (m_ashibaPosY < m_ashibaPos.m_y))) {
                        if (randf() < tenganData->yuka_fly_rate_stop) {
                            fVar1 = randf();
                            float fVar2 = tenganData->yuka_fly_frame_stop_max;
                            float fVar3 = tenganData->yuka_fly_frame_stop_min;
                            m_ashibaState = 1;
                            float temp_f = (fVar2-fVar3);
                            m_ashibaTimer = fVar3+temp_f*fVar1;
                        } else {
                            m_ashibaState = 2;
                        }
                        m_isMovingUp = !(m_isMovingUp);
                    }
                    m_ashibaPosY = m_ashibaPos.m_y;
                    break;
            }
        }
        }
    }
}

void grTenganAshiba::updateCallBack(float frameDelta) {
    grCalcWorldCallBack* calcWorldCallBack = &this->m_calcWorldCallBack;
    if (calcWorldCallBack != NULL) {
        nw4r::g3d::ScnMdl* scnMdl = this->m_sceneModels[0];
        if (scnMdl != NULL) {
            if (scnMdl->m_calcWorldCallBack == NULL) {
                calcWorldCallBack->m_index = 0;
                calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex = this->m_nodeIndex;
                scnMdl->m_calcWorldCallBack = calcWorldCallBack;
                scnMdl->EnableScnMdlCallbackTiming(1);
                scnMdl->m_nodeIndex = calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex;
            }
            grNodeCallbackData* callbackData = calcWorldCallBack->m_nodeCallbackDatas;
            callbackData->m_pos.m_x = m_ashibaPos.m_x;
            callbackData->m_pos.m_y = m_ashibaPos.m_y;
            callbackData->m_pos.m_z = m_ashibaPos.m_z;
        }
    }
}
