#pragma once

#include <gr/gr_yakumono.h>

class grGW : public grYakumono {
protected:
    u8 unk150;
    float unk154;
    u8* unk158;
    u8 unk15C;
    u8 unk15D;
    float unk160;
    float unk164;
    Vec3f unk168;

public:
    grGW(const char* taskName);
    virtual ~grGW();
    virtual void update(float deltaFrame);
    virtual void updateScaleBase(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setSceneIDWork(u8* scene);
    virtual void setSceneID(u8 scene);
};
static_assert(sizeof(grGW) == 0x174, "Class is wrong size!");
