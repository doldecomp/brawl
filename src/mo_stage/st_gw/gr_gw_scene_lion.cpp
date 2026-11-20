#include <memory.h>

#include <st_gw/gr_gw_scene_lion.h>

grGWSceneLion* grGWSceneLion::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWSceneLion* ground = new (Heaps::StageInstance) grGWSceneLion(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWSceneLion::~grGWSceneLion() { }

void grGWSceneLion::processAnim() {
    Ground::processAnim();
    if (unk194 != nullptr) {
        getNodePosition(&unk194[0], 0, "_KEEPER_L_POSITION_01");
        getNodePosition(&unk194[1], 0, "_KEEPER_L_POSITION_02");
        getNodePosition(&unk194[2], 0, "_KEEPER_L_POSITION_03");
    }
    if (unk198 != nullptr) {
        getNodePosition(&unk198[0], 0, "_KEEPER_R_POSITION_01");
        getNodePosition(&unk198[1], 0, "_KEEPER_R_POSITION_02");
        getNodePosition(&unk198[2], 0, "_KEEPER_R_POSITION_03");
    }
}

void grGWSceneLion::update(float deltaFrame) {
    grGWScene::update(deltaFrame);
}
