#include <st_final/gr_final.h>
#include <ec/ec_mgr.h>
#include <memory.h>

grFinal* grFinal::create(int mdlIndex, const char* tgtNodeName, const char* taskName) {
    grFinal* ground = new (Heaps::StageInstance) grFinal(taskName);
    if (ground) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(tgtNodeName);
    }
    return ground;
}

grFinal::~grFinal() { }

void grFinal::update(float deltaFrame) {
    updateEff();
}

void grFinal::updateEff() {
    if (m_type == 0) {
        switch (m_step) {
        case 0:
            g_ecMgr->setDrawPrio(1);
            g_ecMgr->setEffect(ef_ptc_stg_final_zenpan);
            g_ecMgr->setDrawPrio(0xffffffff);
            unk4 = EFF_SOMETHING;
            m_step++;
            break;
        case 1:
            if (!(getMotionFrame(0) < 2540.0f)) {
                g_ecMgr->setDrawPrio(1);
                u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_star);
                g_ecMgr->setDrawPrio(0xffffffff);
                g_ecMgr->setParent(unk, m_sceneModels[0], "spaceB", 0); // sceneModel is actually supposed to be a wrapper of some kind
                m_step++;
            }
            break;
        case 2:
            if (!(getMotionFrame(0) < 6100.0f)) {
                g_ecMgr->setDrawPrio(1);
                u32 unk = g_ecMgr->setEffect(ef_ptc_stg_final_kirakira);
                g_ecMgr->setDrawPrio(0xffffffff);
                g_ecMgr->setParent(unk, m_sceneModels[0], "spaceF", 0); // sceneModel is actually supposed to be a wrapper of some kind
                m_step++;
            }
            break;
        case 3:
            if (getMotionFrame(0) < unk4) {
                m_step = 0;
            } else {
                unk4 = getMotionFrame(0);
            }
            break;
        }
    }
}
