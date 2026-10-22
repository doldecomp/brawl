#pragma once

#include <StaticAssert.h>
#include <st/loader/st_loader.h>
#include <types.h>

class stLoaderPlayer : public stLoader {
public:
    enum Mode {
        Mode_Entry = 0x1,
        Mode_Appear = 0x2,
        Mode_Result = 0x6,
    };

    u32 m_playerId;
    int m_entryId;
    int m_slotId;
    char _0x54[2];
    u8 m_56;
    Mode m_mode : 8;
    char _0x58[2];
    gmCharacterKind m_characterKind : 8;
    char _0x5b[5];

    virtual void processBegin();
    virtual ~stLoaderPlayer();
    virtual void entryEntity();
    virtual void removeEntity();
    virtual bool isLoad();
    virtual bool isEmpty();
    virtual void setSuddenDeath();
    virtual void entryInfoBefore();
    virtual void entryInfo(bool);
    virtual void removeInfo();
    virtual void entryEntitySuddenDeath();
    virtual void entryEntityRebirth();
    virtual void entryEntityRebirthAdventure(u8);
    virtual void lockEntity();
    virtual void unlockEntity();
    virtual bool isEntry();
    virtual gmPlayerInitData* getWatchPlayerInitData();


};
static_assert(sizeof(stLoaderPlayer) == 0x60, "Class is wrong size!");
