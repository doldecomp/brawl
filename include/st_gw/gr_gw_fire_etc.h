#pragma once

#include <nw4r/ut/ut_LinkList.h>
#include <st_gw/gr_gw.h>

class grGWFireEtc : public grGW {
    struct Victim { // Name unknown
        nw4r::ut::LinkListNode unk0;
        u8 unk8;
        float unkC;
    };
    struct NodeState { // Name unknown
        u32 unk0[22];
        float unk58;
    };
    enum State { STATE_0, STATE_1, STATE_2, STATE_3, STATE_4 }; // Name unknown
    enum VictimStep { // Name unknown
        STEP_3 = 3, STEP_4 = 4, STEP_11 = 11, STEP_12 = 12,
        STEP_17 = 17, STEP_18 = 18, STEP_END = 21, STEP_REMOVED = 255
    };
    enum MistakeState { MISTAKE_11 = 11, MISTAKE_12 = 12 }; // Name unknown
    u8* unk174;
    u8* unk178;
    u8* unk17C;
    u32 unk180;
    u32 unk184;
    NodeState unk188;
    u8* unk1E4;
    u8 unk1E8;
    nw4r::ut::LinkList<Victim, 0> unk1EC;
public:
    inline grGWFireEtc(const char* taskName);
    virtual ~grGWFireEtc();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    virtual void updateVictim(float deltaFrame);
    virtual void setIndexWork(u8* value) { unk178 = value; }
    virtual void setIndexFighterWork(u8* value) { unk17C = value; }
    virtual void setStateMistakeWork(u8* value) { unk174 = value; }
    virtual void setEventWork(u8* value) { unk1E4 = value; }
    virtual void addVictim();
    virtual void clearVictim();
    virtual void clearVictimAll();
    virtual Victim* getVictim(u32 index);
    static grGWFireEtc* create(int modelIndex, const char* nodeName, const char* taskName);
};
static_assert(sizeof(grGWFireEtc) == 0x1F8, "Class is wrong size!");

class grGWFireFighter : public grGW {
    enum State { STATE_0, STATE_1, STATE_2, STATE_3, STATE_4 }; // Name unknown
    u32 unk174;
    u32 unk178[3];
    Vec3f* unk184;
    u8* unk188;
    u8* unk18C;
    u8* unk190;
    u8 unk194;
public:
    inline grGWFireFighter(const char* taskName);
    virtual ~grGWFireFighter();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    virtual void updateFighter(float deltaFrame);
    virtual void setEventWork(u8* value) { unk190 = value; }
    virtual void setPosWork(Vec3f* value) { unk184 = value; }
    virtual void setIndexWork(u8* value) { unk188 = value; }
    virtual void setIndexVictimWork(u8* value) { unk18C = value; }
    static grGWFireFighter* create(int modelIndex, const char* nodeName, const char* taskName);
};
static_assert(sizeof(grGWFireFighter) == 0x198, "Class is wrong size!");
