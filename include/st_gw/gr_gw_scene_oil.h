#pragma once

#include <st_gw/gr_gw_scene.h>

struct grGWGuestData { // Name unknown
    Vec3f unk0[8];
    u8 unk60;
    u8 unk61;
};
static_assert(sizeof(grGWGuestData) == 0x64, "Class is wrong size!");

class grGWSceneOil : public grGWScene {
private:
    grGWGuestData* unk194;
    grGWGuestData* unk198;

public:
    static grGWSceneOil* create(int modelIndex, const char* nodeName, const char* taskName);
    grGWSceneOil(const char* taskName)
        : grGWScene(taskName), unk194(nullptr), unk198(nullptr) { }
    virtual ~grGWSceneOil();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual void setDataGuestManWork(grGWGuestData* data) { unk194 = data; }
    virtual void setDataGuestWomanWork(grGWGuestData* data) { unk198 = data; }
};
static_assert(sizeof(grGWSceneOil) == 0x19C, "Class is wrong size!");
