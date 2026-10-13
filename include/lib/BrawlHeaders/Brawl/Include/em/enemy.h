#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/em_ai_module_impl.h>
#include <gr/gr_gimmick_motion_path.h>
#include <memory.h>
#include <mt/mt_vector.h>
#include <so/stageobject.h>
#include <types.h>

class Enemy : public StageObject, public soStatusEventObserver, public soCollisionAttackEventObserver, public soCollisionSearchEventObserver, public soCaptureEventObserver, public soCollisionAbsorberEventObserver, public soCollisionReflectorEventObserver {

    EnemyKind m_enemyKind; // 0xAC
    u8 unkB0[0x4];
    int m_connectedTriggerId;
    u32 m_difficulty;
    u32 m_level;
    u8 unkC0[0x8];
    grGimmickMotionPath* m_motionPath;
    u8 unkCC[0x10];
    soModuleAccesser moduleAccesser;
    u8 unk1BC[0xF4C];
    emAIModuleImpl m_aiModule; // 0x1108
    u8 unk110C[0x5310 - 0x1108 - sizeof(emAIModuleImpl)];

public:
    struct Kinetic {
        struct Energy {
            enum Id {
                Id_Jostle = 0x8,
                Id_Ground_Movement = 0x9,
            };
        };
    };

    enum MessageKind {
        Message_None = -1,
        Message_Damage = 1,
        Message_Destruct = 3,
        Message_Remove = 4,
    };

    emAIModuleImpl& getAIModule() { return m_aiModule; }
    Vec3f getCenterPos();
    s32 getNameMsgId();
    nw4r::g3d::ResFileData* getFaceTexPtr(u32 p1);
    nw4r::g3d::ResFileData* getFaceTexPtr();
    bool isCanAutoRemove();
    bool isCanCreateItem();

    virtual void processUpdate();
    virtual void processFixPosition();
    virtual void processHit();
    virtual void processGameProc();
    virtual void init();
    virtual ~Enemy();

    virtual void updatePosture(bool);
    virtual void processFixPositionPreAnimCmd();
    virtual soKind soGetKind();
    virtual int soGetSubKind();
    virtual void updateNodeSRT();
    virtual bool isTreadPassive();
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);

    virtual float getScore();
    virtual void activate(Vec3f* spawnPos, float lr, float, int statusKind);
    virtual void deactivate();
    virtual bool isSetableNode(int);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual void notifyEventCollisionSearch(soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionSearchCheck();
    virtual void notifyEventCollisionAbsorber(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual bool notifyEventCollisionAbsorberCheck();
    virtual void notifyEventCollisionReflector(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionReflectorSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionReflectorCheck();
    virtual bool notifyEventCaptureStatus(soModuleAccesser* moduleAccesser, int taskId, int, int);
    virtual bool emCreateFigure(int variation);
    virtual bool emShootItem(itKind, int variation, void*, float);
    virtual bool emItemInformationReturnEnemy(int instanceId);
    virtual bool shoot(int, int, int); // TODO: Verify parameters
    virtual bool addParts(int, int);

    template<typename T>
    static Enemy* createInstance(u32 p1, emCreate* create) {
        return new (Heaps::EnemyInstance) T(p1, create);
    }
};
static_assert(sizeof(Enemy) == 0x5310, "Class is wrong size!");

