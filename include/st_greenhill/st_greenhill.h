#pragma once

#include <mt/mt_matrix.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>

struct GreenhillGuestData { // Name unknown
    u8 unk00;
    u8 unk01;
    Matrix unk04;
    float unk34;

    GreenhillGuestData() : unk04(true) { }
};
static_assert(sizeof(GreenhillGuestData) == 0x38, "Class is wrong size!");

template<typename T>
class stClassInfoImpl<Stages::GreenHill, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::GreenHill, this);
    }

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::GreenHill, nullptr);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

class stGreenhill : public stMelee {
    u8 unk1D8[3];
    u8 unk1DB;
    u8 unk1DC;
    u8 unk1DD;
    u8 unk1DE;
    float unk1E0;
    u8 unk1E4;
    u8 unk1E5[3];
    GreenhillGuestData unk1E8[3];
    Vec3f unk290[4];
    u8 unk2C0;

public:
    stGreenhill();
    virtual ~stGreenhill();
    virtual bool loading();
    virtual void createObj();
    virtual void update(float deltaFrame);
    virtual bool isBamperVector() { return true; }
    virtual void createBackground(); // Name unknown
    virtual void createBreaks(); // Name unknown
    virtual void createMarker(); // Name unknown
    virtual void createGuests(); // Name unknown
    virtual void updateGuests(float deltaFrame); // Name unknown

    static stGreenhill* create();
    static stClassInfoImpl<Stages::GreenHill, stGreenhill> bss_loc_14;
};
static_assert(sizeof(stGreenhill) == 0x2C4, "Class is wrong size!");
