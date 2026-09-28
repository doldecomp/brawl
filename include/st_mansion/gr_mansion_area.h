#pragma once

#include <mt/mt_vector.h>
#include <snd/snd_3d_generator.h>

#include <st_mansion/gr_mansion.h>

class grMansionArea : public grMansion {
protected:
    Vec3f* unk158;
    u8* unk15C;
    u8* unk160;
    float* unk164;
    float unk168;
    u8 unk16C;
    u8 unk16D;
    u8 unk16E;
    u32 unk170;
    u8 unk174;
    float unk178;
    snd3DGenerator unk17C;

public:
    grMansionArea(const char* taskName);
    virtual ~grMansionArea();
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual void updateDestroy(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setPillarNode(u32 nodeIndex) { unk170 = nodeIndex; }
    virtual void setPosWork(Vec3f* position) { unk158 = position; }
    virtual void setStateWork(u8* state) { unk15C = state; }
    virtual void setStateSubWork(u8* state) { unk160 = state; }
    virtual void setScaleRateWork(float* rate) { unk164 = rate; }
    virtual void setType(u8 type) { unk16D = type; }
    virtual void setTypeLR(u8 type) { unk16E = type; }
    virtual void setScaleRateFlg(u8 flag) { unk16C = flag; }
};
static_assert(sizeof(grMansionArea) == 0x184, "Class is wrong size!");
