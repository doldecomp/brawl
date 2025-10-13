#pragma once

#include <gr/gr_yakumono.h>
#include <st_village/gr_village.h>
#include <types.h>

class grVillageAshiba : public grVillage {
  protected:
    u8 curAnimId; // 0x168
    char _0x169;    // 0x169
    char _0x16A;    // 0x16A
    char _0x16b;    // 0x16B
    float _0x16C;   // 0x16C
  public:
    grVillageAshiba(const char* taskName);
	static grVillageAshiba* create(int mdlIndex, const char *tgtNodeName, const char *taskName);
    virtual ~grVillageAshiba();
    virtual void update(float deltaFrame);
    virtual void setMotion(u8 animId, bool shouldLoop, u32 unk3, float* unkFloat);
};