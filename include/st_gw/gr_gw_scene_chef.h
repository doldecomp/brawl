#pragma once

#include <st_gw/gr_gw_scene.h>

class grGWSceneChef : public grGWScene {
public:
    static grGWSceneChef* create(int modelIndex, const char* nodeName, const char* taskName);
    grGWSceneChef(const char* taskName) : grGWScene(taskName) { }
    virtual ~grGWSceneChef();
    virtual void update(float deltaFrame);
};
static_assert(sizeof(grGWSceneChef) == 0x194, "Class is wrong size!");
