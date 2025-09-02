
#include <gr/gr_yakumono.h>
#include <gr/gr_gimmick.h>
#include <st_config/gr_config.h>

inline grConfig::grConfig(const char* taskName): grYakumono(taskName) { 
	setupMelee();
}


grConfig* grConfig::create(int mdlIndex, const char *tgtNodeName, const char *taskName) {//: grPictchat(taskname) {
	grConfig *bg = new (Heaps::StageInstance) grConfig(taskName);
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


grConfig::~grConfig() { }