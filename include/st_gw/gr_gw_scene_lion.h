#pragma once

#include <st_gw/gr_gw_scene.h>

class grGWSceneLion : public grGWScene {
private:
    Vec3f* unk194;
    Vec3f* unk198;

public:
    static grGWSceneLion* create(int modelIndex, const char* nodeName, const char* taskName);
    grGWSceneLion(const char* taskName)
        : grGWScene(taskName), unk194(nullptr), unk198(nullptr) { }
    virtual ~grGWSceneLion();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual void setPosKeeperLWork(Vec3f* positions) { unk194 = positions; }
    virtual void setPosKeeperRWork(Vec3f* positions) { unk198 = positions; }
};
static_assert(sizeof(grGWSceneLion) == 0x19C, "Class is wrong size!");
