
#include <gr/gr_yakumono.h>
#include <gr/gr_gimmick.h>
#include <st_village/gr_village.h>


grVillage* grVillage::create(int mdlIndex, const char *tgtNodeName, const char *taskName) {
	grVillage *bg = new (Heaps::StageInstance) grVillage(taskName);
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

grVillage::grVillage(const char* taskName): grYakumono(taskName) { 
	m_state = 0;
	m_stateTimer = 0;
    m_sceneWork = NULL;
    m_sceneBit = 0;
    m_stateWork = NULL;
    m_guestPositionsWork = NULL;
    setupMelee();
}

grVillage::~grVillage() { }

void grVillage::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateVisible(deltaFrame);
    }
    
}

void grVillage::updateVisible(float deltaFrame) {
    //grGimmick::update(deltaFrame);
    if (m_sceneWork == NULL) {
        return;
    }
    if (m_sceneBit == NULL) {
        return;
    }
    if (m_sceneBit & (1 << *m_sceneWork)) {
        setVisibility(true);
    } else {
        setVisibility(false);
    }
}

bool grVillage::isSceneBit() {
    //grGimmick::update(deltaFrame);
    if (m_sceneWork == NULL) {
        return false;
    }
    if (m_sceneBit == NULL) {
        return true;
    }
    return (m_sceneBit & (1 << *m_sceneWork));
}