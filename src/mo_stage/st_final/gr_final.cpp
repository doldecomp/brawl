#include <st_final/gr_final.h>
#include <ec/ec_mgr.h>
#include <memory.h>

grFinal* grFinal::create(int mdlIndex, const char* tgtNodeName, const char* taskName)
{
    grFinal* ground = new (Heaps::StageInstance) grFinal(taskName);
	if (ground) {	
//	    ground->setupMelee();
	    ground->setMdlIndex(mdlIndex);
	    ground->setTgtNode(tgtNodeName);
	}

    return ground;
}

grFinal::~grFinal() {
	
}

void grFinal::update(float deltaFrame)
{
    this->updateEff();
}

void grFinal::updateEff()
{
    if (this->type == 0)
    {
        switch (this->step)
        {
        case 0:
            g_ecMgr->setDrawPrio(1);
            g_ecMgr->setEffect(ef_ptc_stg_final_zenpan);
            g_ecMgr->setDrawPrio(0xffffffff);
            unk_float = EFF_SOMETHING;
            step++;
            break;
        case 1:
            if (!(this->getMotionFrame(0) < 2540.0f))
            {
                g_ecMgr->setDrawPrio(1);
                u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_star);
                g_ecMgr->setDrawPrio(0xffffffff);
                g_ecMgr->setParent(unk, this->m_sceneModels[0], "spaceB", 0); // sceneModel is actually supposed to be a wrapper of some kind
                step++;
            }
            break;
        case 2:
			if (!(this->getMotionFrame(0) < 6100.0f))
//            if (this->getMotionFrame(0) > 6100.0f)
            {
                g_ecMgr->setDrawPrio(1);
                u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_kirakira);
                g_ecMgr->setDrawPrio(0xffffffff);
                g_ecMgr->setParent(unk, this->m_sceneModels[0], "spaceF", 0); // sceneModel is actually supposed to be a wrapper of some kind
                step++;
            }
            break;
        case 3:
            if (this->getMotionFrame(0) < this->unk_float)
            {
                step = 0;
            }
            else
            {	
				this->unk_float = this->getMotionFrame(0);
            }
            break;
        }
    }
}