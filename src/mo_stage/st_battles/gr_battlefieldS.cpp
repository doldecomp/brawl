#include <memory.h>

#include <st_battles/gr_battlefieldS.h>

grBattleFieldS* grBattleFieldS::create(int mdlIndex, const char* tgtNodeName, const char* taskName) {
    grBattleFieldS* ground = new (Heaps::StageInstance) grBattleFieldS(taskName);
    if (ground) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(tgtNodeName);
    }
    return ground;
}

grBattleFieldS::~grBattleFieldS() { }
