#pragma once

#include <StaticAssert.h>
#include <ft/fighter.h>
#include <ft/ft_owner.h>
#include <gm/gm_result_info.h>
#include <mt/mt_vector.h>
#include <so/damage/so_damage_attacker_info.h>
#include <so/so_dispose_instance_manager.h>
#include <so/event/so_event_presenter.h>
#include <so/event/so_log_event_presenter.h>
#include <ft/ft_entry_manager.h>
#include <ft/ft_slot_manager.h>
#include <it/item.h>
#include <so/so_null.h>
#include <so/ground/so_ground_util.h>
#include <types.h>

class ftOutsideEventObserver : public soEventObserver<ftOutsideEventObserver> {
public:
    ftOutsideEventObserver() : soEventObserver<ftOutsideEventObserver>(0) {};
    ftOutsideEventObserver(short unitID) : soEventObserver<ftOutsideEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    // TODO: Verify params
    virtual void notifyEventOnDamage(int entryId, u32 hp, soDamage* damage);
    virtual void notifyEventSetDamage(int entryId, float, u32 percent, bool, bool);
    virtual void notifyEventRecover(int entryId, int);
    virtual void notifyEventOutsideDeadArea(int entryId, soGroundUtil::DeadAreaCheckResult, bool*);
    virtual void notifyEventAppeal(int entryId, int);
    virtual void notifyEventDead(int entryId, int deadCount, Fighter::Dead::Reason deadReason, int respawnFrames);
    virtual void notifyEventBeat(int entryId1, int entryId2);
    virtual void notifyEventSuicide(int entryId);
    virtual void notifyEventChangeStart(int entryId, int playerNo, int activeInstanceIndex, ftKind);
    virtual void notifyEventChangeEnd(int entryId, int playerNo, int activeInstanceIndex, ftKind);
    virtual void notifyEventChangeAppear();
    virtual void notifyEventAddDragoonParts(int entryId, int);
    virtual void notifyEventCompDragoonParts(int entryId);
    virtual void notifyEventRemoveDragoonParts(int entryId, int);
    virtual void notifyEventResetDragoonParts(int entryId);
    virtual void notifyEventReEntryRequestFighter();
    virtual void notifyEventSetCursor(int entryId, u32 index);
    virtual void notifyEventSetNameCursor(int entryId, u32 index);
    virtual void notifyEventSetLoupe(int entryId, u32 index);
    virtual void notifyEventStartFinal(int entryId);
    virtual void notifyEventEndFinal(int entryId);
    virtual void notifyEventRemoveEntry(int entryId);
    virtual void notifyEventFinalSlow(int entryId, float, int);
    virtual void notifyEventFinalSlowCancel(int entryId);
    virtual void notifyEventFinalStop(int entryId);
    virtual void notifyEventFinalStopCancel(int entryId);
    virtual void notifyEventEntryEnd(int entryId);
    virtual void notifyEventResultEnd(int entryId);
    virtual void notifyEventGetItem(int entryId, itKind kind, int itVariation, int genParamId, int instanceId);
    virtual void notifyEventSucceedHit(int entryId, u32 consecutiveHits, float totalDamage);
    virtual void notifyEventResultWin(int entryId, int);
    virtual void notifyEventYoshiEggStart(int entryId);
    virtual void notifyEventYoshiEggEnd(int entryId);
    virtual void notifyEventOnInput(int entryId);
    virtual void notifyEventPikminMakeBloomAll(int entryId);
    virtual void notifyEventKirbyCopySetup(int entryId, int);
    virtual void notifyEventKirbyCopyCancel(int entryId, int);
    virtual void notifyEventKnockout(int entryId);
    virtual void notifyEventHeartSwapStart(int entryId1, int entryId2);
    virtual void notifyEventHeartSwapEnd(int, int);

    char _spacer1[2];
};
static_assert(sizeof(ftOutsideEventObserver) == 12, "Class is wrong size!");

class ftManagerAbstract : public soNull, public gfTask, public ftOutsideEventObserver, public soDisposeInstanceEventObserver, public soLogEventObserver {
    // Note: Done so that vtable placement is proper
};

class ftManager;
extern ftManager* g_ftManager;
class ftManager : public ftManagerAbstract {

public:
    char _104[2];
    GameRule m_gameRule : 8;
    char _107[2];
    bool m_isStamina;
    bool m_isTeams : 1;
    bool m_isTeamAttack : 1;
    bool : 1;
    bool : 1;
    bool m_noOnePatternOffsett : 1; // no staling
    bool : 1;
    bool m_noDeadUp : 1;
    bool m_isHomerun : 1;
    char _111[1];
    int m_finalStatus;
    int m_finalEntryId;
    int m_noDiscretionFinalCount;
    char _122[21];
    s8 m_parasitePlayerNo;    // custom
    char _146[34];
    soEventManageModuleImpl m_eventManageModule;
    char m_200[4];
    short m_manageID;
    char _206[132];
    ftEntryManager* m_entryManager;
    ftSlotManager* m_slotManager;
    void* m_dataProvider;

    virtual ~ftManager();

    virtual void processBegin();
    virtual void processUpdate();
    virtual void processHit();
    virtual void processEnd();
    virtual void processDebug();

    virtual void notifyEventKirbyCopySetup(int entryId, int);
    virtual void notifyEventKirbyCopyCancel(int entryId, int);

    virtual void notifyDisposeInstance(bool, int, int taskId);
    virtual void notifyDrawDone();

    virtual void notifyEventEntryEnd(int entryId);
    virtual void notifyEventResultEnd(int entryId);
    void notifyReplacePokeTrainer(int param1);

    virtual void notifyLogEventCollisionHit(float, int taskId1, int taskId2, int);
    virtual void notifyLogEventDead(int entryId1, int entryId2, int, int);

    bool isValidEntryId(int entryId);
    int getEntryCount();
    int getEntryId(int playerNo);
    int getEntryIdFromIndex(int index);
    int getEntryIdFromTaskId(int taskId, int* outInstanceIndex);
    int getScoreEntryId(int entryId);
    int getPlayerNo(int entryId);
    s32 getSlotNo(s32 entryId);
    bool isFighterActivate(int entryId, int);
    Fighter* getFighter(int entryId, int instanceIndex);
    Fighter* getSubFighter(int entryId);
    ftOwner* getOwner(int entryId);
    int getTeam(int entryId, bool unk2, bool unk3);
    Vec3f getFighterCenterPos(int entryId, int unk);
    float getFighterLr(int entryId, int unk);
    int getFighterOperationType(int entryId);
    int getFighterOperationStatus(int entryId);
    Fighter* searchNearFighter(float unk1, float radius, Vec3f* pos, int team, bool unk4);
    void setHeal(int entryId, float heal);
    void setCurry(int entryId);
    void setSuperStar(int entryId);
    void setSlow(int inflictingTeam, bool setStatus, int slowStrength, int slowDuration);
    void setTimerSlow(int inflictingEntryId, bool setStatus, int slowStrength, int slowDuration);
    void setScaling(int entryId, Fighter::Scaling::Kind, Fighter::Scaling::Type);
    void setInfiniteScaling(int entryId, Fighter::Scaling::Kind, Fighter::Scaling::Type);
    void setThunder(int inflictingEntryId, int unk2);
    void setWarpFighter(int entryId, Vec3f* pos, float lr, u32 flags);
    void setFighterOperationStatus(int entryId, int fighterOperationStatus);
    void setFinal(int entryId, bool isDiscretion);
    bool addDragoon(int entryId, u32 variation);

    void pickupCoin(int entryId, int amount);
    void setDead(int entryId, int unk1, int unk2);
    void setBeat(int losingEntryId, int winningEntryId);
    void setSuicide(int entryId);
    bool isProcessHeartSwap(int entryId);
    void toKnockOutHeartSwapOpposite(int entryId, soDamageAttackerInfo* attackerInfo);

    bool isReadySlot(int slotIndex);
    bool isReadyRemoveSlot(int slotIndex);
    void removeSlot(int slotIndex);

    inline bool hasHitPoint(int entryId) {
        return getOwner(entryId)->getHitPointMax() != 0;
    };

    inline static ftManager* getInstance() { return g_ftManager; }
};

static_assert(sizeof(ftManager) == 0x160, "Class is wrong size!");

