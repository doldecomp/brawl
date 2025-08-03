
#include <gr/gr_yakumono.h>
#include <gr/gr_gimmick.h>
#include <st_dxshrine/gr_dxshrine.h>

inline grDxShrine::grDxShrine(const char* taskName): grYakumono(taskName) { 
	setupMelee();
}


grDxShrine* grDxShrine::create(int mdlIndex, const char *tgtNodeName, const char *taskName) {//: grPictchat(taskname) {
	grDxShrine *bg = new (Heaps::StageInstance) grDxShrine(taskName);
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


grDxShrine::~grDxShrine() { }