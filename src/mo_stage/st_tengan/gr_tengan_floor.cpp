#include <st_tengan/gr_tengan_floor.h>
#include <ec/ec_mgr.h>
#include <snd/snd_system.h>
#include <memory.h>

grTenganFloor* grTenganFloor::create(int mdlIndex, const char* tgtNodeName, const char* taskName)
{
    grTenganFloor* ground = new (Heaps::StageInstance) grTenganFloor(taskName);
	if (ground) {	
	    ground->setMdlIndex(mdlIndex);
	    ground->setTgtNode(tgtNodeName);
	}
	ground->setupMelee();

    return ground;
}

inline grTenganFloor::grTenganFloor(const char* taskName) : grYakumono(taskName) {
	//memset(m_tgtNode,0,0x80);
    m_state = 0;
    m_stateTimer = 0.0f;
    m_frameWork = NULL;
    m_stateWork = NULL;
    m_type = 0;
    unk16d = 0;
    unk170 = 0.0f;
    m_animId = 2;
    m_animTimer = 0.0f;
    m_unused.m_x = 0.0f;
    m_unused.m_y = 0.0f;
    m_unused.m_z = 0.0f;
}

grTenganFloor::~grTenganFloor() {
	
}

void grTenganFloor::update(float deltaFrame)
{
    if (m_isUpdate) {
        updateActive(deltaFrame);
        updatePreBuild(deltaFrame);
        grGimmick::update(deltaFrame);
    }
}

void grTenganFloor::updateActive(float deltaFrame)
{
    if (getStageData() != NULL) {
        float fVar1 = m_stateTimer - deltaFrame;
        m_stateTimer = fVar1;
        if (fVar1 < 0.0f) {
            m_stateTimer = 0.0f;
        }
        fVar1 = m_animTimer - deltaFrame;
        m_animTimer = fVar1;
        if (fVar1 < 0.0f) {
            m_animTimer = 0.0f;
        }
        switch (m_state) {
            case 0:
                setMotion(0, false, 1, NULL);
                m_state = 1;
                break;
            case 1:
                bool isBreak = false;
                switch (m_type) {
                    case 0:
                    case 1:
                    case 2:
                        if (m_stateWork[0] == 1) {
                            isBreak = true;
                            
                            //g_ecMgr->setParent(g_ecMgr->setEffect(ef_ptc_stg_tengan_yukabreak), m_sceneModels[0], 0, false);
                            
                            g_ecMgr->setParent(g_ecMgr->setEffect(ef_ptc_stg_tengan_yukabreak),m_sceneModels[0],1,0);
                        }
                        break;
                    case 3:
                        if (m_stateWork[0] == 1 || m_stateWork[1] == 1) {
                            isBreak = true;
                        }
                        break;
                    case 4:
                        if (m_stateWork[1] == 1 || m_stateWork[2] == 1) {
                            isBreak = true;
                        }
                        break;
                }
                if (isBreak == true) {
                    setMotion(1, false, 1, &m_animTimer);
                    setEnableCollisionStatus(false);
                    m_state = 2;
                }
                break;
            case 2:
                if (*m_frameWork < 1.0f) {
                    switch(m_type) {
                        case 0:
                        case 1:
                        case 2:
                            g_ecMgr->setParent(g_ecMgr->setEffect(ef_ptc_stg_tengan_yukahukkatu),m_sceneModels[0],1,0);
                            setMotion(0, false, 1, NULL);
                            g_sndSystem->playSE(snd_se_stage_Tengan_43,-1,0,0,-1);
                            break;
                    }
                    setNodeVisibilityAll(1,0);
                    m_state = 3;
                }
                if (m_animTimer == 0.0f) {
                    setVisibility(false);
                }
                break;
            case 3:
                if (*m_frameWork == 0.0f) {
                    *m_stateWork = 0;
                    setVisibility(true);
                    setEnableCollisionStatus(true);
                    m_state = 0;
                }
                break;
        }
    }
}

void grTenganFloor::updatePreBuild(float deltaFrame)
{
    if (m_state != 3) {
        return;
    }
    unk170 = 0.0f;
    setVisibility(false);
}

void grTenganFloor::setMotion(u8 animId, bool shouldLoop, u32 unk3, float* frameCount)
{
    if (this->m_animId == animId and unk3 == 0)
        return;
    
    // get sceneMdl and model animations
    nw4r::g3d::ScnMdl* sceneMdl = *this->m_sceneModels;

    if (sceneMdl == NULL)
        return;
    
    gfModelAnimation* modelAnim = *this->m_modelAnims;
    if (modelAnim == NULL)
        return;
    
    // get scene model data
    nw4r::g3d::ResMdl model = sceneMdl->m_resMdl;

    if (!model.IsValid())
        return;

    modelAnim->unbindNodeAnim(sceneMdl);
    modelAnim->unbindVisibleAnim(sceneMdl);
    modelAnim->unbindTexAnim(sceneMdl);
    modelAnim->unbindTexSrtAnim(sceneMdl);
    modelAnim->unbindMatColAnim(sceneMdl);
    this->m_animId = animId;
    
    if (animId >= 2)
        return;
//    MEMAllocator* allocator;
    bool result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if ((result))
    {
        setChrAnim2(animId,model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if ((result))
    {
        setVisibilityAnim2(animId,model, modelAnim, Heaps::StageInstance);
    }
    
    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if ((result))
    {
        setTexPatAnim2(animId,model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if ((result))
    {
        setTexSortAnim2(animId,model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if ((result))
    {
        setColorAnim2(animId,model, modelAnim, Heaps::StageInstance);
    }

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoop(shouldLoop);

    if (frameCount != NULL)
    {
        *frameCount = modelAnim->getFrameCount();
    }
}
