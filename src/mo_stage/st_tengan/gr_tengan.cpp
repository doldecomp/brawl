#include <st_tengan/gr_tengan.h>
#include <ec/ec_mgr.h>
#include <memory.h>

grTengan* grTengan::create(int mdlIndex, const char* tgtNodeName, const char* taskName)
{
    grTengan* ground = new (Heaps::StageInstance) grTengan(taskName);
	if (ground) {	
	    ground->setMdlIndex(mdlIndex);
	    ground->setTgtNode(tgtNodeName);
	}
	ground->setupMelee();

    return ground;
}

grTengan::grTengan(const char* taskName) : grYakumono(taskName) {
	memset(m_tgtNode,0,0x80);
}

grTengan::~grTengan() {
	
}

void grTengan::update(float deltaFrame)
{
    grGimmick::update(deltaFrame);
}

void grTengan::setTgtNode(const char* tgtNode)
{
    if (tgtNode) {
        strcpy(m_tgtNode,"");
        strncpy(m_tgtNode,tgtNode,0x7f);
    }
    //m_tgtNode = tgtNode;
}

char* grTengan::getTgtNode()
{
    return m_tgtNode;
}
