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
    static grGreenhillBg* create(int mdlIndex, const char* nodeName, const char* taskName); // Name unknown
    virtual void updateCollision(float deltaFrame); // Name unknown
    virtual void updateFlowers(float deltaFrame); // Name unknown
    virtual void setPositions(Vec3f* positions) { unk158 = positions; } // Name unknown
    virtual void setState(u8* state) { unk15C = state; } // Name unknown
};

class grGreenhillBreak : public grGreenhill {
    u8 unk158[0xC];
    u8* unk164;
    u8* unk168;
    u8 unk16C;

public:
    static grGreenhillBreak* create(int mdlIndex, const char* nodeName, const char* taskName); // Name unknown
    virtual void updateCollision(float deltaFrame); // Name unknown
    virtual void updateCallback(float deltaFrame); // Name unknown
    virtual void updateBreak(float deltaFrame); // Name unknown
    virtual void createYakumono(); // Name unknown
    virtual void createAttack(); // Name unknown
    virtual void createAttack(int index); // Name unknown
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount); // Name unknown
    virtual void setState(u8* state) { unk164 = state; } // Name unknown
    virtual void setIndex(u8 index) { unk16C = index; } // Name unknown
    virtual void setBackgroundState(u8* state) { unk168 = state; } // Name unknown
};

class grGreenhillCheck : public grGreenhill {
    u8 unk158[4];
    u8* unk15C;
    u8* unk160;
    Vec3f* unk164;

public:
    static grGreenhillCheck* create(int mdlIndex, const char* nodeName, const char* taskName); // Name unknown
    virtual void updateYakumono(float deltaFrame); // Name unknown
    virtual void updateMotion(float deltaFrame); // Name unknown
    virtual void updateCallback(float deltaFrame); // Name unknown
    virtual void createYakumono(); // Name unknown
    virtual void createAttack(); // Name unknown
    virtual void setMaterialColor(int state); // Name unknown
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount); // Name unknown
    virtual void setPositions(Vec3f* positions) { unk164 = positions; } // Name unknown
    virtual void setState(u8* state) { unk15C = state; } // Name unknown
    virtual void setBreakStates(u8* states) { unk160 = states; } // Name unknown
};

class grGreenhillGuest : public grGreenhill {
    GreenhillGuestData* unk158;

public:
    static grGreenhillGuest* create(int mdlIndex, const char* nodeName, const char* taskName); // Name unknown
    virtual void updateMotion(float deltaFrame); // Name unknown
    virtual void updateCallback(float deltaFrame); // Name unknown
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; } // Name unknown
};

class grGreenhillGuestLine : public grGreenhill {
    GreenhillGuestData* unk158;

public:
    static grGreenhillGuestLine* create(int mdlIndex, const char* nodeName, const char* taskName); // Name unknown
    virtual void updateMotion(float deltaFrame); // Name unknown
    virtual void setMotion(u32 index, bool loop, bool force, float* frameCount); // Name unknown
    virtual void setGuestData(GreenhillGuestData* data) { unk158 = data; } // Name unknown
};
