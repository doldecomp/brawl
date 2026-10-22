#pragma once

#include <StaticAssert.h>
#include <ft/ft_manager.h>
#include <gf/gf_task.h>
#include <mt/mt_vector.h>
#include <types.h>

class aiMgr : public gfTask, public ftOutsideEventObserver {
    char _76[828];

public:
    virtual void processBegin();
    virtual void renderDebug();
    virtual ~aiMgr();

    virtual void notifyEventOnDamage(int entryId, u32 hp, soDamage* damage);
    virtual void notifyEventDead(int entryId, int deadCount, Fighter::Dead::Reason deadReason, int respawnFrames);
    virtual void notifyEventChangeStart(int entryId, int playerNo, int activeInstanceIndex, ftKind);
    virtual void notifyEventChangeEnd(int entryId, int playerNo, int activeInstanceIndex, ftKind);

    int setDangerZone(Vec2f* p1, Vec2f* p2, int index, bool, bool);
    void delDangerZone(int);
};
static_assert(sizeof(aiMgr) == 0x388, "Class is wrong size!");

extern aiMgr* g_aiMgr;