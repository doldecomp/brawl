#pragma once

#include <ft/fighter.h>
#include <so/so_array.h>
#include <ft/ft_common_data_accesser.h>
#include <so/turn/so_turn_module.h>
#include <StaticAssert.h>
#include <types.h>

// Only the behavior-accessed tail is recovered. The module builder remains opaque.
// The constructor obtains this data from ftCommonDataAccesser::getData(Fighter_Wolf).
// HYPOTHESIS: the record grouping extends ftData; its turn record offset is verified.
struct ftWolfData : ftData {
    u8 unk58[0x94 - sizeof(ftData)];
    soTurnData reflectorTurnData;
};
static_assert(sizeof(ftWolfData) == 0x9c, "Reflector turn data offset is wrong!");

class ftWolf : public Fighter {
    u8 unk194[0x1cc84 - sizeof(Fighter)];
public:
    // HYPOTHESIS: field grouping follows copies; field meanings remain unknown.
    class PostureInfo {
    public:
        struct { u32 unk0, unk4; } unk0;
        u32 unk8;
        float unkc;
    };
    ftWolfData* m_commonData;
private:
    // Set by reflector collision callbacks and consumed by the reflector check.
    u8 unk1cc88;
    u8 unk1cc89;
    u8 unk1cc8a[2];
    // Points to the embedded soArrayVector<PostureInfo, 4> at +0x1cc90.
    soArray<PostureInfo>* m_postureHistory;
    u8 unk1cc90[0x1ccdc - 0x1cc90];
public:
    virtual ~ftWolf();
    virtual void onStart(int startKind);
    virtual void processUpdate();
};
static_assert(sizeof(ftWolf) == 0x1ccdc, "Wolf allocation size is wrong!");
static_assert(sizeof(ftWolf::PostureInfo) == 16, "Posture info is the wrong size!");
