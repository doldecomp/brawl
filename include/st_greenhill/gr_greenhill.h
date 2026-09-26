#pragma once

#include <gr/gr_yakumono.h>

struct GreenhillGuestData;

class grGreenhill : public grYakumono {
protected:
    u8 unk150;
    float unk154;
};
static_assert(sizeof(grGreenhill) == 0x158, "Class is wrong size!");

class grGreenhillBg : public grGreenhill {
    Vec3f* unk158;
    u8* unk15C;

public:
    static grGreenhillBg* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateJoint(float deltaFrame);
    virtual void updateHang(float deltaFrame);
    virtual void setPosGimmickWork(Vec3f* positions) { unk158 = positions; }
    virtual void setBreakInfo(u8* state) { unk15C = state; }
};

class grGreenhillBreak : public grGreenhill {
    u8 unk158[0xC];
    u8* unk164;
    u8* unk168;
    u8 unk16C;

public:
    static grGreenhillBreak* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateJoint(float deltaFrame);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateBreak(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void setAttack(int index);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setStateWork(u8* state) { unk164 = state; }
    virtual void setType(u8 type) { unk16C = type; }
    virtual void setBreakInfo(u8* state) { unk168 = state; }
};

class grGreenhillCheck : public grGreenhill {
    u8 unk158[4];
    u8* unk15C;
    u8* unk160;
    Vec3f* unk164;

public:
    static grGreenhillCheck* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateYakumono(float deltaFrame);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setHit();
    virtual void setAttack();
    virtual void changeColor(int state);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setPosWork(Vec3f* positions) { unk164 = positions; }
    virtual void setStateWork(u8* state) { unk15C = state; }
    virtual void setStateBreakWork(u8* states) { unk160 = states; }
};

class grGreenhillGuest : public grGreenhill {
    GreenhillGuestData* unk158;

public:
    static grGreenhillGuest* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void updateCallBack(float deltaFrame);
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; }
};

class grGreenhillGuestLine : public grGreenhill {
    GreenhillGuestData* unk158;

public:
    static grGreenhillGuestLine* create(int mdlIndex, const char* nodeName, const char* taskName);
    virtual void updateActive(float deltaFrame);
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount);
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; }
};
