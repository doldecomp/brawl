#pragma once

// Local shadow of BrawlHeaders' ft/ft_manager.h (include/ comes first on the include path): the original layout, with the
// state bytes at 0x68..0x7C split into named members, plus the member functions recovered in ft_manager.cpp.

#include <StaticAssert.h>
#include <so/so_instance_unit.h>

class soEventUnit;
// MATCH-ONLY: the array of event unit records (the event manager entity) is built with out-of-line record
// constructors/destructors in the original (a call to __construct_array), and the pointer is left untouched.
template <>
class soInstanceUnit<soEventUnit*> {
public:
    soEventUnit* m_element;
    int m_id;

    soInstanceUnit();
    ~soInstanceUnit();
};

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
#include <ft/ft_outside_event_presenter.h>
#include <it/item.h>
#include <so/so_null.h>
#include <so/ground/so_ground_util.h>
#include <types.h>

// The fighter data provider (loads and serves fighter resource data); only isReady is used by the fighter manager.
class ftDataProvider {
public:
    ftDataProvider();
    virtual ~ftDataProvider();
    void reqCommon(u32 a, u32 b, int c);
    void process();
    bool isReady();
    char _4[0x109C];
    bool m_isUseCompressedMode;
    char _10a1[3];
};
static_assert(sizeof(ftDataProvider) == 0x10A4, "Class is wrong size!");
extern ftDataProvider* g_ftDataProvider;

class ftOutsideEventObserver : public soEventObserver<ftOutsideEventObserver> {
public:
    ftOutsideEventObserver() : soEventObserver<ftOutsideEventObserver>(0) { initialize(-1, -1); }
    ftOutsideEventObserver(short unitID) : soEventObserver<ftOutsideEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    // TODO: Verify params
    virtual void notifyEventOnDamage(int entryId, u32 hp, soDamage* damage) { }
    virtual void notifyEventSetDamage(int entryId, float, u32 percent, bool, bool) { }
    virtual void notifyEventRecover(int entryId, int) { }
    virtual void notifyEventOutsideDeadArea(int entryId, soGroundUtil::DeadAreaCheckResult, bool*) { }
    virtual void notifyEventAppeal(int entryId, int) { }
    virtual void notifyEventDead(int entryId, int deadCount, Fighter::Dead::Reason deadReason, int respawnFrames) { }
    virtual void notifyEventBeat(int entryId1, int entryId2) { }
    virtual void notifyEventSuicide(int entryId) { }
    virtual void notifyEventChangeStart(int entryId, int playerNo, int activeInstanceIndex, ftKind) { }
    virtual void notifyEventChangeEnd(int entryId, int playerNo, int activeInstanceIndex, ftKind) { }
    virtual void notifyEventChangeAppear() { }
    virtual void notifyEventAddDragoonParts(int entryId, int) { }
    virtual void notifyEventCompDragoonParts(int entryId) { }
    virtual void notifyEventRemoveDragoonParts(int entryId, int) { }
    virtual void notifyEventResetDragoonParts(int entryId) { }
    virtual void notifyEventReEntryRequestFighter() { }
    virtual void notifyEventSetCursor(int entryId, u32 index) { }
    virtual void notifyEventSetNameCursor(int entryId, u32 index) { }
    virtual void notifyEventSetLoupe(int entryId, u32 index) { }
    virtual void notifyEventStartFinal(int entryId) { }
    virtual void notifyEventEndFinal(int entryId) { }
    virtual void notifyEventRemoveEntry(int entryId) { }
    virtual void notifyEventFinalSlow(int entryId, float, int) { }
    virtual void notifyEventFinalSlowCancel(int entryId) { }
    virtual void notifyEventFinalStop(int entryId) { }
    virtual void notifyEventFinalStopCancel(int entryId) { }
    virtual void notifyEventEntryEnd(int entryId) { }
    virtual void notifyEventResultEnd(int entryId) { }
    virtual void notifyEventGetItem(int entryId, itKind kind, int itVariation, int genParamId, int instanceId) { }
    virtual void notifyEventSucceedHit(int entryId, u32 consecutiveHits, float totalDamage) { }
    virtual void notifyEventResultWin(int entryId, int) { }
    virtual void notifyEventYoshiEggStart(int entryId) { }
    virtual void notifyEventYoshiEggEnd(int entryId) { }
    virtual void notifyEventOnInput(int entryId) { }
    virtual void notifyEventPikminMakeBloomAll(int entryId) { }
    virtual void notifyEventKirbyCopySetup(int entryId, int) { }
    virtual void notifyEventKirbyCopyCancel(int entryId, int) { }
    virtual void notifyEventKnockout(int entryId) { }
    virtual void notifyEventHeartSwapStart(int entryId1, int entryId2) { }
    virtual void notifyEventHeartSwapEnd(int, int) { }

    char _spacer1[2];
};
static_assert(sizeof(ftOutsideEventObserver) == 12, "Class is wrong size!");

// The event lookup of the presenter constructor is inlined at every use in the original (list stored through a local).
inline ftOutsideEventPresenter::ftOutsideEventPresenter(s16 manageId, int entryId) :
    soEventPresenter<ftOutsideEventObserver>(manageId, 0, true), m_entryId(entryId) { }

class ftManagerAbstract : public soNull, public gfTask, public ftOutsideEventObserver, public soDisposeInstanceEventObserver, public soLogEventObserver {
    // Note: Done so that vtable placement is proper
public:
    ftManagerAbstract() : gfTask("ftManager", Category_None, 0, 0, true) { }
};

class ftManager;
extern ftManager* g_ftManager;
class ftManager : public ftManagerAbstract {

public:
    u8 m_mode; // 0x68: 0 or 1 (setMode); mode 1 is the adventure mode (ftUtil scales speeds by the adventure multipliers)
    u8 m_paramPattern; // 0x69: setParamPattern
    u8 m_gameRule; // GameRule (read as a plain byte by the code: 1 is stock, 2 is coin/bonus)
    u8 unk6b;
    // 0x6c: game progress flags
    bool unk6c_80 : 1;
    bool m_isGameStarted : 1; // set by readyGo, cleared by quitGame
    bool m_isGameSet : 1; // set by gameSet (GAME! screen), cleared by readyGo and quitGame
    bool unk6c_10 : 1;
    bool unk6c_08 : 1;
    bool unk6c_04 : 1;
    bool unk6c_02 : 1;
    bool unk6c_01 : 1;
    u8 m_isStamina; // stamina (HP) match flag, tested as "!= 0"
    u8 m_isTeams : 1;
    bool m_isTeamAttack : 1;
    bool m_isDiscretionFinal : 1; // HYPOTHESIS: Final Smash may be triggered at will (see isEnableDiscretionFinal)
    bool unk6e_10 : 1;
    bool m_noOnePatternOffsett : 1; // no staling
    bool unk6e_04 : 1;
    bool m_noDeadUp : 1;
    bool m_isHomerun : 1;
    bool unk6f_80 : 1;
    bool unk6f_40 : 1;
    bool m_isWaitingDraw : 1; // HYPOTHESIS: cleared by notifyDrawDone, tested by isResourceRemoveSync
    bool unk6f_10 : 1;
    bool unk6f_08 : 1;
    bool unk6f_04 : 1;
    bool unk6f_02 : 1;
    bool unk6f_01 : 1;
    int m_finalStatus;
    int m_finalEntryId;
    int m_noDiscretionFinalCount;
    bool unk7c; // set by setMode/setDefault, read by isAvailableFinal
    int unk80;
    int unk84;
    int unk88;
    soInstanceManagerSimpleEntity<soEventUnit*, soArrayVector<soInstanceUnit<soEventUnit*>, 1> > m_eventManageEntity; // 0x8c
    soEventManageModuleImpl m_eventManageModule; // 0xb4
    soEventUnitWithWorkArea<ftOutsideEventObserver, 8> m_eventUnit; // 0xc8
    ftEntryManager* m_entryManager;
    ftSlotManager* m_slotManager;
    ftDataProvider* m_dataProvider;

    ftManager(u32 commonResourceA, u32 commonResourceB);

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

    bool isValidEntryId(int entryId) const;
    bool isExistEntry() const;
    int enumEntryId(int entryId) const;
    int enumIncludeEntryId(int entryId) const;
    int getEntryIdFromAreaId(int areaId) const;
    bool isEnableDiscretionFinal() const;
    void start();
    void quitGame();
    int addSlot();
    bool isUseCompressedMode() const;
    void addBootResource(int slotIndex, int resId);
    void addEntryResource(int slotIndex, int resId);
    void addResultResource(int slotIndex, int resId);
    void addItemResource(int slotIndex, int itemId);
    void removeTechniqResourceAll();
    void removeResourceAll();
    void set2PGamesHeapLayout(int layout);
    bool isReadyKirbyCopyResource(int entryId, int kirbyKind) const;
    bool isReadyFinalResource(int entryId) const;
    int getRealRebirthEntryId(int entryId);
    void startFighter(int entryId, bool unk);
    void startFighter(int entryId, Vec3f* pos, float lr);
    void disappearTrainer(int entryId);
    void standbyFighter(int entryId, int unk);
    void standbyFighterAdvFollow(int entryId);
    void standbyAllFighter();
    int getPointTeam(int entryId) const;
    int getTeam2nd(int entryId) const;
    void setVisibilityTrainer(int entryId, bool visible);
    void setFighterOperationStatusAll(int status);
    void setFighterOperationType(int entryId, s8 type);
    void setFighterOperationCpuType(int entryId, int cpuType);
    bool isProcessTechnique() const;
    bool isCpuActive(int entryId) const;
    int getFighterCount(int entryId) const;
    const char* getFighterName(int entryId) const;
    Vec3f getFighterCursorPos(int entryId, int instanceIndex) const;
    Vec2f* getFighterRhombusCenterPos(int entryId, int instanceIndex) const;
    ftOwner* getSubOwner(int entryId) const;
    void* getInput(int entryId) const;
    void* getSubInput(int entryId) const;
    int getKirbyCopyResourceCount(int entryId) const;
    int getKirbyCopyResourceKind(int entryId, int index) const;
    void onKirbyResourceLoaded(int slotIndex, int index);
    void onKirbyResourceUnLoaded(int slotIndex, int index);
    void exitFighter(int slotIndex, int unk);
    void setTemporaryCamera(int entryId, float unk1, int unk2, int unk3, int unk4);
    void setInterporateTemporaryCamera(int entryId, float unk1, float unk2, int unk3, int unk4);
    int getCoin(int entryId) const;
    void lostCoin(int entryId, int amount, bool unk);
    void generateCoin(int entryId, int amount);
    void toChange(int entryId, int unk1, int unk2, int unk3);
    void toChangeAppear(int entryId, float unk1, int unk2, int unk3);
    void setContNo(int entryId, int contNo);
    void removeDragoon(int entryId, int index);
    void removeDragoonAll(int entryId);
    int getDragoonCount(int entryId);
    int getDragoonVariation(int entryId, int index);
    void setHeartSwap(int entryId1, int entryId2);
    bool isProcessHeartSwap() const;
    int getPokeTrainerInstanceHeap(int entryId) const;
    void setZoom(int entryId, float unk1, int unk2, int unk3);
    void exitFinal(int entryId, int unk);
    bool isAvailableFinal(bool unk) const;
    void setFinalTask(u32 category, u32 taskId);
    void notifyEventPikminFinalAttack(float unk1, int unk2);
    void setDead(int entryId, int unk1, int unk2);
    void setDefault();
    void setMode(int mode);
    void stopGame();
    bool isExistLoseFighterResult(int unk, int kind) const;
    void createFighter(int entryId);
    void setControllerRumble(int entryId, int unk1, int unk2, u32 isOn, int unk3);
    void setControllerRumbleAll(int unk1, int unk2, u32 isOn, int unk3);
    void stopControllerRumbleAll(int unk1, int unk2);
    bool isResourceRemoveSync() const;
    float getFighterCursorForceDispDistance() const;
    s16 getEntryEventManageId(int entryId) const;

    float getDamageMax(int excludeEntryId);
    void setParamPattern(int pattern);
    void setPokemonStaminaSystem(bool enabled);
    void readyGo();
    void gameSet();
    void setFinalStatus(int status);
    void cancelFinalStatus();
    int getRank(int entryId) const;
    int getRankPoint(int entryId) const;
    int getCurrentFighterNo(int entryId) const;
    int getFighterNo(int entryId, int kind) const;
    int getFighterGmKind(int entryId) const;
    int getResultFighterGmKind(int entryId) const;
    bool isSubFighterActivate(int entryId) const;
    bool isSubFighterDead(int entryId) const;
    bool isFighterPositionAccessable(int entryId, int instanceIndex) const;
    bool isSubFighterPositionAccessable(int entryId) const;
    bool isFighterEnableWarp(int entryId) const;
    int getEntryCount() const;
    int getEntryId(int playerNo) const;
    int getEntryIdFromIndex(int index) const;
    int getEntryIdFromTaskId(int taskId, int* outInstanceIndex) const;
    int getScoreEntryId(int entryId) const;
    int getPlayerNo(int entryId) const;
    s32 getSlotNo(s32 entryId) const;
    bool isFighterActivate(int entryId, int) const;
    Fighter* getFighter(int entryId, int instanceIndex) const;
    Fighter* getSubFighter(int entryId) const;
    ftOwner* getOwner(int entryId) const;
    int getTeam(int entryId, bool unk2, bool unk3) const;
    Vec3f getFighterCenterPos(int entryId, int unk) const;
    float getFighterLr(int entryId, int unk) const;
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
    void setBeat(int losingEntryId, int winningEntryId);
    void setSuicide(int entryId);
    bool isProcessHeartSwap(int entryId) const;
    void toKnockOutHeartSwapOpposite(int entryId, soDamageAttackerInfo* attackerInfo);

    bool isReadySlot(int slotIndex) const;
    bool isReadyRemoveSlot(int slotIndex) const;
    bool removeSlot(int slotIndex);

    inline bool hasHitPoint(int entryId) {
        return getOwner(entryId)->getHitPointMax() != 0;
    };

    inline static ftManager* getInstance() { return g_ftManager; }
};

static_assert(sizeof(ftManager) == 0x160, "Class is wrong size!");

