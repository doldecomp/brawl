#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/event/so_event_presenter.h>
#include <so/so_null.h>
#include <so/sound/so_sound_3d_generator_accesser_impl.h>
#include <so/situation/so_situation_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/collision/so_collision_hit_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <types.h>

class soModuleAccesser;

class soSoundIdExchanger : public soNullable {
public:
    virtual ~soSoundIdExchanger();
    virtual SndID getId(SndID sndID, soModuleAccesser* moduleAccesser);
    virtual int getStepId(int);    // TODO: Verify
    virtual int getLandingId(int); // TODO: Verify
};
static_assert(sizeof(soSoundIdExchanger) == 8, "Class is wrong size!");

class soSoundIdExchangerNull : public soSoundIdExchanger {
public:
    virtual ~soSoundIdExchangerNull();
    virtual SndID getId(SndID sndID, soModuleAccesser* moduleAccesser);
    virtual int getStepId(int);
    virtual int getLandingId(int);
};

extern soSoundIdExchangerNull g_soSoundIdExchangerNull;

class soSoundModule {
public:
    class SoundIdList {
    public:
        SndID* sndIDs;
        u32 numSndIDs;
    };

    class SoundIdData {
    public:
        SoundIdList* soundIdLists;
        u32 numSoundIdLists;
    };

    // TODO: Verify params
    virtual ~soSoundModule();
    virtual void update(Vec3f* pos);
    virtual void deactivate();
    virtual void activate(Vec3f* pos);
    virtual void setPos(Vec3f* pos, int);
    virtual int playSE(SndID sndId, bool, int, int);
    virtual int playSENo3d(SndID sndId, bool);
    virtual int playSEPos(SndID sndId, Vec3f* pos, bool, int, int);
    virtual int playStatusSE(SndID sndId, bool, int);
    virtual void stopStatusSE();
    virtual void setPlayHitSEFlag(bool);
    virtual bool getPlayHitSEFlag();
    virtual void playHitSE(float, void*);
    virtual void playDamageSE(u32 index1, u32 index2);
    virtual void setSEVol(float, int, int);
    virtual float getSEVol(int);
    virtual void setSEPitch(float);
    virtual void setSEPitch(u32, double);
    virtual float getSEPitch();
    virtual void stopSE(int, int);
    virtual void stopSEHandle(int);
    virtual void setSESpeed(int, float);
    virtual void playLandingSE();
    virtual void setSoundIdData(SoundIdData*);
    virtual SoundIdData* getSoundIdData();
    virtual void setFixGeneratorStatus();
    virtual void setCheckSoundGroup(int);
    virtual int getCheckSoundGroup();
    virtual bool isPlay(int);
};
static_assert(sizeof(soSoundModule) == 4, "Class is wrong size!");

class soSoundModuleImpl : public soSoundModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soCollisionHitEventObserver, public soSituationEventObserver {
    char _52[8];
    soSound3dGeneratorAccesser* m_soundGeneratorAccesser;
    soModuleAccesser* m_moduleAccesser;
    soSoundIdExchanger* m_soundIdExchanger;
    SndID m_sndID;
    SoundIdData* m_soundIdData;
    float m_sePitch;
    int m_checkSoundGroup;
    bool m_playHitSEFlag;
    u8 m_generatorStatus;
    char _pad[2];

public:
    // TODO: Verify params
    virtual ~soSoundModuleImpl();
    virtual void update(Vec3f* pos);
    virtual void deactivate();
    virtual void activate(Vec3f* pos);
    virtual void setPos(Vec3f* pos, int);
    virtual int playSE(SndID sndId, bool, int, int);
    virtual int playSENo3d(SndID sndId, bool);
    virtual int playSEPos(SndID sndId, Vec3f* pos, bool, int, int);
    virtual int playStatusSE(SndID sndId, bool, int);
    virtual void stopStatusSE();
    virtual void setPlayHitSEFlag(bool);
    virtual bool getPlayHitSEFlag();
    virtual void playHitSE(float, void*);
    virtual void playDamageSE(u32 index1, u32 index2);
    virtual void setSEVol(float, int, int);
    virtual float getSEVol(int);
    virtual void setSEPitch(float);
    virtual void setSEPitch(u32, double);
    virtual float getSEPitch();
    virtual void stopSE(int, int);
    virtual void stopSEHandle(int);
    virtual void setSESpeed(int, float);
    virtual void playLandingSE();
    virtual void setSoundIdData(SoundIdData*);
    virtual SoundIdData* getSoundIdData();
    virtual void setFixGeneratorStatus();
    virtual void setCheckSoundGroup(int);
    virtual int getCheckSoundGroup();
    virtual bool isPlay(int);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventCollisionHit(float power, soCollisionAttackData*, u32 index, int, soModuleAccesser* moduleAccesser, soCollisionLog*);
    virtual void notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soSoundModuleImpl) == 92, "Class is wrong size!");
