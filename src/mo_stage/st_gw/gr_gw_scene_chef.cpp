#include <memory.h>

#include <st_gw/gr_gw_scene_chef.h>

grGWSceneChef* grGWSceneChef::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWSceneChef* ground = new (Heaps::StageInstance) grGWSceneChef(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWSceneChef::~grGWSceneChef() { }

void grGWSceneChef::update(float deltaFrame) {
    grGWScene::update(deltaFrame);
}
