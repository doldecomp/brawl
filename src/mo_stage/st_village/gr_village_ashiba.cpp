
#include <gr/gr_yakumono.h>
#include <gr/gr_gimmick.h>
#include <st_village/gr_village_ashiba.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <gf/gf_heap_manager.h>
//#include <g3d/g3d_scnmdl.h>
//#include <g3d_scnmdl.h>

inline grVillageAshiba::grVillageAshiba(const char* taskName): grVillage(taskName) { 
	//setupMelee();
    curAnimId = 1; // 0x168
    _0x16C = 0.0;
}


grVillageAshiba* grVillageAshiba::create(int mdlIndex, const char *tgtNodeName, const char *taskName) {//: grPictchat(taskname) {
	grVillageAshiba *bg = new (Heaps::StageInstance) grVillageAshiba(taskName);
	if (bg != 0) {
		
		//bg->setupMelee();
		bg->setMdlIndex(mdlIndex);
		//bg->m_heapType = Heaps::StageInstance;
		//bg->makeCalcuCallback(1, Heaps::StageInstance);
		//bg->setCalcuCallbackRoot(7);
		bg->setTgtNode(tgtNodeName);
	}
	return bg;
}


grVillageAshiba::~grVillageAshiba() { }

void grVillageAshiba::update(float deltaFrame) {
    grVillage::update(deltaFrame);
    if (m_isUpdate) {
        switch(m_state) {
            case 0:
                setMotion(0, true, 0, NULL);
                switch(*m_stateWork) {
                    case 2:
                        setMotionFrame(300, 0);
                        break;
                }
                m_state = 4;
                break;
            case 4:
                break;
        }
    }
}

/*inline void setVisibilityAnim(nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmVisNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmVis anim = modelAnim->m_resFile.GetResAnmVis(animId);

        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
        if (anim.IsValid())
        {
            nw4r::g3d::AnmObjVisRes* anmObj = nw4r::g3d::AnmObjVisRes::Construct(allocator, &instanceSize, anim, model);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjVisRes != NULL)
                {
                    modelAnim->m_anmObjVisRes->Destroy();
                }

                modelAnim->m_anmObjVisRes = anmObj;
            }
        }
    }
}*/
//setVisibilityAnim(model,modelAnim);
void grVillageAshiba::setMotion(u8 animId, bool shouldLoop, u32 unk3, float* frameCount)
{
    if (this->curAnimId == animId and unk3 == 0)
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
    this->curAnimId = animId;
    
    if (animId >= 1)
        return;
//    MEMAllocator* allocator;
    bool result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if ((result) and (animId < modelAnim->m_resFile.GetResAnmVisNumEntries()))
    {
        int instanceSize;
        nw4r::g3d::ResAnmVis anim = modelAnim->m_resFile.GetResAnmVis(animId);

        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
        if (anim.IsValid())
        {
            nw4r::g3d::AnmObjVisRes* anmObj = nw4r::g3d::AnmObjVisRes::Construct(allocator, &instanceSize, anim, model);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjVisRes != NULL)
                {
                    modelAnim->m_anmObjVisRes->Destroy();
                }

                modelAnim->m_anmObjVisRes = anmObj;
            }
        }
    }
    
    result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if ((result) and (animId < modelAnim->m_resFile.GetResAnmChrNumEntries()))
    {
        int instanceSize;
        nw4r::g3d::ResAnmChr anim = modelAnim->m_resFile.GetResAnmChr(animId);

            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
        if (anim.IsValid())
        {
            nw4r::g3d::AnmObjChrRes* anmObj = nw4r::g3d::AnmObjChrRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjChrRes != NULL)
                {
                    modelAnim->m_anmObjChrRes->Destroy();
                }

                modelAnim->m_anmObjChrRes = anmObj;
            }
        }
    }

    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if ((result) and (animId < modelAnim->m_resFile.GetResAnmTexPatNumEntries()))
    {
        int instanceSize;
        nw4r::g3d::ResAnmTexPat anim = modelAnim->m_resFile.GetResAnmTexPat(animId);

        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
            nw4r::g3d::AnmObjTexPatRes* anmObj = nw4r::g3d::AnmObjTexPatRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjTexPatRes != NULL)
                {
                    modelAnim->m_anmObjTexPatRes->Destroy();
                }

                modelAnim->m_anmObjTexPatRes = anmObj;
            }
        }
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if ((result) and (animId < modelAnim->m_resFile.GetResAnmTexSrtNumEntries()))
    {
        int instanceSize;
        nw4r::g3d::ResAnmTexSrt anim = modelAnim->m_resFile.GetResAnmTexSrt(animId);

        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
            nw4r::g3d::AnmObjTexSrtRes* anmObj = nw4r::g3d::AnmObjTexSrtRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjTexSrtRes != NULL)
                {
                    modelAnim->m_anmObjTexSrtRes->Destroy();
                }

                modelAnim->m_anmObjTexSrtRes = anmObj;
            }
        }
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if ((result) and (animId < modelAnim->m_resFile.GetResAnmClrNumEntries()))
    {
        int instanceSize;
        nw4r::g3d::ResAnmClr anim = modelAnim->m_resFile.GetResAnmClr(animId);

        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
            nw4r::g3d::AnmObjMatClrRes* anmObj = nw4r::g3d::AnmObjMatClrRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjMatClrRes != NULL)
                {
                    modelAnim->m_anmObjMatClrRes->Destroy();
                }

                modelAnim->m_anmObjMatClrRes = anmObj;
            }
        }
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