#include <memory.h>

#include <st_gw/gr_gw_scene_oil.h>

grGWSceneOil* grGWSceneOil::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWSceneOil* ground = new (Heaps::StageInstance) grGWSceneOil(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWSceneOil::~grGWSceneOil() { }

void grGWSceneOil::processAnim() {
    Ground::processAnim();
    if (unk194 != nullptr) {
        // Both man pose sets use the same four nodes.
        getNodePosition(&unk194->unk0[0], 0, "_MAN_01_POSITION");
        getNodePosition(&unk194->unk0[1], 0, "_MAN_02_POSITION");
        getNodePosition(&unk194->unk0[2], 0, "_MAN_03_POSITION");
        getNodePosition(&unk194->unk0[3], 0, "_MAN_04_POSITION");
        getNodePosition(&unk194->unk0[4], 0, "_MAN_01_POSITION");
        getNodePosition(&unk194->unk0[5], 0, "_MAN_02_POSITION");
        getNodePosition(&unk194->unk0[6], 0, "_MAN_03_POSITION");
        getNodePosition(&unk194->unk0[7], 0, "_MAN_04_POSITION");
    }
    if (unk198 != nullptr) {
        getNodePosition(&unk198->unk0[0], 0, "_WOMAN_01_POSITION");
        getNodePosition(&unk198->unk0[1], 0, "_WOMAN_02_POSITION1");
        getNodePosition(&unk198->unk0[2], 0, "_WOMAN_03_POSITION");
        getNodePosition(&unk198->unk0[3], 0, "_WOMAN_04_POSITION");
        getNodePosition(&unk198->unk0[4], 0, "_WOMAN_ANGER_01_POSITION");
        getNodePosition(&unk198->unk0[5], 0, "_WOMAN_ANGER_02_POSITION");
        getNodePosition(&unk198->unk0[6], 0, "_WOMAN_ANGER_03_POSITION");
        getNodePosition(&unk198->unk0[7], 0, "_WOMAN_ANGER_04_POSITION");
    }
}

void grGWSceneOil::update(float deltaFrame) {
    grGWScene::update(deltaFrame);
}
