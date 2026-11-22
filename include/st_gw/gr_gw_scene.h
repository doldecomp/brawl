#pragma once

#include <st_gw/gr_gw.h>

class stDataMultiContainer;

class grGWScene : public grGW {
private:
    u8 unk174;
    float unk178;
    float* unk17C;
    Vec3f* unk180;
    u8* unk184;
    u8* unk188;
    u8 unk18C;
    u8 unk18D;
    stDataMultiContainer* unk190;

public:
    static grGWScene* create(int modelIndex, const char* nodeName, const char* taskName);
    grGWScene(const char* taskName);
    virtual ~grGWScene();
    virtual void update(float deltaFrame);
    virtual void updateSub(float deltaFrame);
    virtual void updateSubEnd(float deltaFrame);
    virtual void updateStep(float deltaFrame);
    virtual void updateEvent(float deltaFrame);
    virtual void selectStep();
    virtual void clearStep();
    virtual void setFrameWork(float* frame);
    virtual void setEventWork(u8* event);
    virtual void setPosGimmickWork(Vec3f* positions);
    virtual void setCtrlStepWork(u8* control);
    virtual void setTblStepAcc(stDataMultiContainer* table);
};
static_assert(sizeof(grGWScene) == 0x194, "Class is wrong size!");
