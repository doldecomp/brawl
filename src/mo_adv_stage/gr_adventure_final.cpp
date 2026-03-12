#include <sora_adv_stage/gr_adventure_final.h>
#include <ec/ec_mgr.h>
#include <memory.h>

grAdventureFinal* grAdventureFinal::create(int mdlIndex, const char* tgtNodeName, const char* taskName) {
    grAdventureFinal* ground = new (Heaps::StageInstance) grAdventureFinal(taskName);
    if (ground) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(tgtNodeName);
    }
    return ground;
}

grAdventureFinal::~grAdventureFinal() { }

void grAdventureFinal::update(float deltaFrame) {
    this->updateEff();
}

void grAdventureFinal::updateEff()
{
    switch (m_step) {
    case 0:
        g_ecMgr->setDrawPrio(1);
        g_ecMgr->setEffect(ef_ptc_stg_final_zenpan);
        g_ecMgr->setDrawPrio(0xffffffff);
        unk4 = EFF_SOMETHING;
        m_step++;
        break;
    case 1:
        if (!(this->getMotionFrame(0) < 2540.0f)) {
            g_ecMgr->setDrawPrio(1);
            u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_star);
            g_ecMgr->setDrawPrio(0xffffffff);
            g_ecMgr->setParent(unk, m_sceneModels[0], "spaceB", 0); // sceneModel is actually supposed to be a wrapper of some kind
            m_step++;
        }
        break;
    case 2:
        if (!(this->getMotionFrame(0) < 6100.0f)) {
            g_ecMgr->setDrawPrio(1);
            u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_kirakira);
            g_ecMgr->setDrawPrio(0xffffffff);
            g_ecMgr->setParent(unk, m_sceneModels[0], "spaceF", 0); // sceneModel is actually supposed to be a wrapper of some kind
            m_step++;
        }
        break;
    case 3:
        if (this->getMotionFrame(0) < unk4) {
            m_step = 0;
        } else {
            unk4 = this->getMotionFrame(0);
        }
        break;
    }
}
