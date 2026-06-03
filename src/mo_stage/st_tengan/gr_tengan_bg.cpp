#include <st_tengan/gr_tengan_bg.h>
#include <ec/ec_mgr.h>
#include <memory.h>

grTenganBg* grTenganBg::create(int mdlIndex, const char* tgtNodeName, const char* taskName)
{
    grTenganBg* ground = new (Heaps::StageInstance) grTenganBg(taskName);
	if (ground) {	
	    ground->setMdlIndex(mdlIndex);
	    ground->setTgtNode(tgtNodeName);
	}
	ground->setupMelee();

    return ground;
}

grTenganBg::grTenganBg(const char* taskName) : grTengan(taskName) {
	//memset(m_tgtNode,0,0x80);
    posDialgaWork = NULL;
    posAshibaWork = NULL;
}

grTenganBg::~grTenganBg() {
	
}

void grTenganBg::update(float deltaFrame)
{
    if(posDialgaWork) {
        getNodePosition(posDialgaWork,0,"dialgaPosition");
    }
    if(posAshibaWork) {
        getNodePosition(&posAshibaWork[0],0,"ashibaA_Up");
        getNodePosition(&posAshibaWork[1],0,"ashibaA_Down");
        getNodePosition(&posAshibaWork[2],0,"ashibaA_Up1");
        getNodePosition(&posAshibaWork[3],0,"ashibaA_Down1");
    }
    grGimmick::update(deltaFrame);
}
