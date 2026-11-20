#include <memory.h>
#include <st_mansion/gr_mansion_ground.h>

#include <st_mansion/gr_mansion.h>

grMansion* grMansion::create(int modelIndex, const char* nodeName, const char* taskName) {
    grMansion* ground = new (Heaps::StageInstance) grMansion(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grMansion::grMansion(const char* taskName) : grYakumono(taskName), unk150(0), unk154(0.0f) {
    setupMelee();
}

grMansion::~grMansion() { }

grMansionGround* grMansionGround::create(int modelIndex, const char* nodeName, const char* taskName) {
    grMansionGround* ground = new (Heaps::StageInstance) grMansionGround(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grMansionGround::~grMansionGround() { }

void grMansionGround::processAnim() {
    Ground::processAnim();
    if (unk158 != nullptr) {
        getNodePosition(&unk158[0], 0, "FrontLocator_L");
        getNodePosition(&unk158[1], 0, "FrontLocator_R");
    }
}
