#pragma once

#include <StaticAssert.h>
#include <ft/fighter.h>
#include <so/article/so_article.h>
#include <so/stageobject.h>
#include <types.h>
#include <ut/ut_uncopyable.h>
#include <it/it_value_accesser.h>
#include <it/it_gen_archive.h>
#include <it/it_create.h>
#include <it/kinetic/it_kinetic_module_impl.h>

class itCustomizerInterface;

class BaseItem : public StageObject, public soStatusEventObserver, public soSituationEventObserver, public soCollisionAttackEventObserver, public soCollisionShieldEventObserver, public soCollisionReflectorEventObserver, public soCollisionSearchEventObserver, public soGimmickEventObserver, public soArticle {
protected:
    soModuleAccesser moduleAccesser;
    char _428[1808];

public:
    struct Status {
        enum Kind {
            Standby = 0x0,
            Initialize = 0x1,
            Have = 0x2,
            Fall = 0x3,
            Landing = 0x4,
            Throw = 0x5,
            Lost = 0x6,
            Born = 0x7,
        };
        struct Work {
            enum Int {
                Int_Value_1 = 0x20000000,
                Int_Value_2 = 0x20000001,
                Int_Value_3 = 0x20000002,
                Int_Value_4 = 0x20000003,
                Int_Value_5 = 0x20000004,
            };
            enum Float {
                Float_Value_1 = 0x21000000,
                Float_Value_2 = 0x21000001,
                Float_Value_3 = 0x21000002,
                Float_Value_4 = 0x21000003,
                Float_Value_5 = 0x21000004,
                Float_Value_6 = 0x21000005,
            };
            enum Flag {
                Flag_Use_Speed_Power = 0x22000000,
                Flag_Damage = 0x22000001,
                Flag_Dead = 0x22000002,
                Flag_Hit = 0x22000003,
                Flag_Near_Target = 0x22000004,
                Flag_Found = 0x22000005,
                Flag_Lot_Create_Bomb = 0x22000006,
            };
        };
    };

    struct Motion {
        enum Kind {
            Appear = 0x0,
            Have = 0x1,
            Fall = 0x2,
            Throw = 0x3,
            Born = 0x4,
            Lost = 0x5,
        };
    };

    struct Area {
        enum Kind {
            Body = 0x0,
            Wind = 0x1,
            Pickup = 0x2,
        };
    };

    struct Kinetic {
        struct Energy {
            enum Id {
                Id_Rot = 0x0,
                Id_Outer = 0x1,
                Id_Gravity = 0x2,
                Id_Ground = 0x3,
                Id_AI_Move = 0x4,
                Id_AI_Rot = 0x5,
                Id_Motion = 0x6,
                Id_Stop = 0x7,
                Id_Jostle = 0x8,
                Id_Ground_Movement = 0x9,
                Id_Wind = 0xA,

                Id_Control = 0x4,
                Id_Control_Rot = 0x5,
            };
        };
    };

    struct Link : StageObject::Link {
        enum No {
            No_Have = 0x3,
            No_Target = 0x4,
            No_TeamOwner = 0x6,
            No_CreateOwner = 0x7,
        };
    };

    struct AnimCmd {
        enum Type {
            Type_Remove = 0x0,
            Type_Lot_Create = 0x1,

            Type_Set_Rot = 0x3,
            Type_Set_Life_Time = 0x4,
            Type_Set_Counter = 0x5,
            Type_Set_Scale_Anim = 0x6,
            Type_Search_Target = 0x7,
            Type_Set_Notify_Article_Event_Eject = 0x8,
            Type_Create_Item = 0x9,
            Type_Warp_Pos_Target = 0xA,
            Type_Subtract_Hp = 0xB,
            Type_Set_Scale = 0xC,
            Type_Create_Item_Angle = 0xD,
            Type_Get_Node_Global_Pos = 0xE,
            Type_Get_Dist_Vector = 0xF,
            Type_Shoot = 0x10,

            Type_Get_Target_Pos = 0x14,
            Type_Remove_Eatable_Target_Item = 0x15,

            Type_Get_Node_Global_Rot = 0x1A,
            Type_Request_Slow = 0x1B,
            Type_Remove_Slow = 0x1C,
            Type_Set_Team = 0x1D,
            Type_Enable_Area = 0x1E,
            Type_Disable_Area = 0x1F,
            Type_Disable_Eatable_Target_Item_Pickup = 0x20,
            Type_Set_Pos_Target = 0x21,
        };

        enum EventKind {
            Event_Damage = 0x0,
            Event_Info_Window = 0x1,
            Event_Counter = 0x2,
            Event_Bound = 0x3,
        };
    };

    struct Instance {
        struct Work {
            enum Int {
                Int_Value_1 = 0x10000000,
                Int_Value_2 = 0x10000001,
                Int_Value_3 = 0x10000002,
                Int_Value_4 = 0x10000003,
                Int_Bound_Flag = 0x10000004, // writes 0x10 in itKineticModuleImpl::characterBound, writes on soKineticModuleImpl::updateNormal/updateRolling depending on bounce type,  writes 0x1/0x2 depending on which counter is finished
                Int_Value_6 = 0x10000005,
                Int_Life_Time_Max = 0x10000006,
                Int_Have_Node_Index = 0x10000007,
                Int_Trait_Flag = 0x10000008,
                Int_Life_Time = 0x10000009,
                Int_No_Damage_Frame = 0x1000000A,
                Int_Counter = 0x1000000B,
                Int_Counter_2 = 0x1000000C,
                Int_Message = 0x1000000D,
                Int_Message_Enemy = 0x1000000E, // used in SmashPlate and getCommunicationItemPortData
                Int_Scale_Anim_Type = 0x1000000F,
                Int_Scale_Anim_Counter = 0x10000010,
                Int_Scale_Anim_Node_Index = 0x10000011,
                Int_Scale_Anim_Counter_Limit = 0x10000012,
                Int_Target_Task_Id = 0x10000013,
                Int_Child_Task_Id = 0x10000014,
                Int_Rotate_Node_Index = 0x10000015,
                Int_Hit_Kind = 0x10000016,
                Int_Bound_Count = 0x10000017,
                Int_SE_Bound_Id = 0x10000018,
                Int_SE_Water_Id = 0x10000019,
                Int_SE_Reflect_Id = 0x1000001A,
                Int_SE_Lost_Id = 0x1000001B,
                Int_Throw_Frame = 0x1000001C,
                Int_Attack_Serial_Id = 0x1000001d,
                Int_Attack_Kind = 0x1000001e,
            };
            enum Float {
                Float_Value_1 = 0x11000000,
                Float_Value_2 = 0x11000001,
                Float_Value_3 = 0x11000002,
                Float_Value_4 = 0x11000003,
                Float_Value_5 = 0x11000004,
                Float_Value_6 = 0x11000005,
                Float_Hp = 0x11000006,
                Float_Target_Pos_X = 0x11000007,
                Float_Target_Pos_Y = 0x11000008,
                Float_Scale_Anim_Min = 0x11000009,
                Float_Scale_Anim_Max = 0x1100000a,
                Float_Scale_Anim_Now = 0x1100000b,
                Float_Base_Scale = 0x1100000c,
                Float_Inhaled_Count = 0x1100000d,
            };
            enum Flag {
                Flag_Value_1 = 0x12000000,
                Flag_Value_2 = 0x12000001,
                Flag_Value_3 = 0x12000002,
                Flag_Value_4 = 0x12000003,
                Flag_Reaction = 0x12000004,
                Flag_Reflect_Ground = 0x12000005,
                Flag_Vanish = 0x12000006,
                Flag_Target_Found = 0x12000007,
                Flag_Disable_Jostle = 0x12000008,
                Flag_unk = 0x12000009,
                Flag_Auto_Play_Lost_Effect = 0x1200000A,
                Flag_Ground_Lost = 0x1200000c,
                Flag_Water = 0x1200000d,
                Flag_Apply_World_Move = 0x1200000E,
                Flag_Eatable = 0x1200000f,
            };
        };
    };

    struct Lot {
        enum State {
            State_Error = 0x0,
            State_Miss = 0x1,
            State_Bomb = 0x2,
            State_Hit = 0x3,
        };
    };

    struct Target {
        enum Type {
            Current_Target = 0x0,
            Myself = 0x1,
            Near_Fighter = 0x2,
            Random_Fighter = 0x3,
            Random_Out_Of_Camera = 0x4,
            Camera_Target = 0x5,
            Create_Owner = 0x6,
            Create_Owner_Target = 0x7,
            Target_Infield = 0x9,
            Many_Side = 0xA,
            Under_Ground = 0xB,
            Under_Ground_2 = 0xC, // TODO: Figure out difference
            Near_Food = 0xD,
            Random_Out_Of_Camera_Lr = 0xE,
            None = 0xF,
            Ike_Final = 0x10,
            Random_Item_Drop_Pos = 0x11,
            Near_Fighter_All = 0x12,
            Many_Side_Fix = 0x13,
        };
    };

    struct Scale {
        enum AnimType {
            Anim_None = -0x1,
            Anim_Normal = 0x0,
            Anim_Loop = 0x1,
            Anim_Small_To_Normal = 0x2,
            Anim_Interpolate = 0x3,
            Anim_Keep = 0x4,
        };
    };

    typedef itParam::BoundFlag BoundFlag;
    typedef itParam::BoundMask BoundMask;

    int m_instanceId;
    union {
        struct {
            ItemKind m_itemKind;
        };
        struct {
            itKind m_kind;
            u32 m_variation;
        };
    };
    int m_createOwnerTaskId;
    itKind m_lotCreateKind;
    itCustomizerInterface* m_customizer;
    u8 m_2260;
    char _2261[7];
    itArchive* m_itArchive;
    float m_strongestAttackPower;
    int m_hitStopFrames;
    char _2280[13368];
    int m_articleId;
    char _15652[4];
    itGenId m_genId;
    char _15660[4];
    int m_attackHitTaskId;
    int m_searchHitTaskId;
    int m_15672;
    int m_15676;
    u8 searchHitCollisionIndex;
    u8 m_15681;
    char _15682[2];
    Vec3f m_searchHitPos;
    Vec3f m_startInhaledPos;
    char _15708[4];

    BaseItem(itCreate* create);
    virtual void processUpdate();
    virtual void processMapCorrection();
    virtual void processFixPosition();
    virtual void processHit();
    virtual void processFixCamera();
    virtual void processGameProc();
    virtual void renderPre();
    virtual void renderDebug();
    virtual ~BaseItem();

    virtual void updatePosture(bool);
    virtual soKind soGetKind();
    virtual int soGetSubKind();
    virtual void updateNodeSRT();
    virtual bool isTreadPassive();
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);

    // TODO: Verify parameters
    virtual void reset(Vec3f* pos, float lr, float);
    virtual void remove();
    virtual int getArticleId();
    virtual int getArticleEventManageId();
    virtual int getTaskId();
    virtual void linkOwner(int, int);
    virtual void unlinkOwner(int);
    virtual bool isActiveArticle();
    virtual void deactivateArticle();
    virtual void changeMotion(int motionKind, bool);
    virtual void changeStatus(int statusKind);
    virtual void setVisibilityWhole(u8);
    virtual void setVisibilityWholeForce(u8);
    virtual u8 getVisibilityWhole();
    virtual void setSituationKind(SituationKind);
    virtual bool isConstraint();
    virtual void setConstraintTargetNode(int);
    virtual bool isSyncOwnerStatus();
    virtual void setSyncOwnerStatus(bool);
    virtual void setAttackPowerMulPattern(float);
    virtual void setArticleId(int articleId);
    virtual void setLogAttackInfo(soLogAttackInfo* logAttackInfo);
    virtual soLogAttackInfo getLogAttackInfo();
    virtual void updateLogAttackInfo();
    virtual void deactivate();
    virtual void have(int taskId, int, int);
    virtual void action(u32, float);
    virtual void setGlowAttack(int glowAttack);
    virtual int getGlowAttack();
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventChangeSituation(SituationKind kind, SituationKind prevKind, soModuleAccesser* moduleAccesser);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual void notifyEventCollisionShield(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionShieldSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionShieldCheck();
    virtual void notifyEventCollisionReflector(soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, float power, float posX, float);
    virtual void notifyEventCollisionReflectorSearch(soCollisionSearchModule* searchModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionReflectorCheck();
    virtual void notifyEventCollisionSearch(soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionSearchCheck();
    virtual void notifyEventInfoWindow(int);
    virtual void notifyEventGimmick(soGimmickEventArgs* eventInfo, int* taskId);
    virtual void presentEventGimmick(soGimmickEventArgs* eventInfo, int sendID);
    virtual void onDamage(int damageStatusKind, soDamageLog*);
    virtual bool isUseTurnDamage();
    virtual bool isUseSpeedDamage();
    virtual bool isUseShake();

    float getParam(itValueAccesser::ParamFloat param);
    int getParam(itValueAccesser::ParamInt param);
    float getParamFloat(u32 param);
    bool isHaved();
    int getTeamOwnerTaskId();
    void setTeamOwnerTaskId(int taskId);

    void setSafePos(Vec2f* pos);
    void warp(Vec3f* pos);
    void setVanishMode(bool);
    bool sendTouchMessage(int taskId, Vec3f* pos, float);
};
static_assert(sizeof(BaseItem) == 0x3d60, "Class is wrong size!");

class itCustomizerInterface : public utUnCopyable, public soNullable {
public:
    virtual ~itCustomizerInterface() {}
    virtual void onConstruct(BaseItem* item);
    virtual void onDestruct(BaseItem* item);
    virtual void onReset(BaseItem* item);
    virtual void onProcessUpdate(BaseItem* item);
    virtual void onProcessFixPosition(BaseItem* item);
    virtual void onProcessHit(BaseItem* item);
    virtual void onProcessFixCamera(BaseItem* item);
    virtual void onProcessGameProc(BaseItem* item);
    virtual void onRenderPre(BaseItem* item);
    virtual void onRenderDebug(BaseItem* item);
    virtual void onNotifyEventChangeStatus(BaseItem* item, int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void onNotifyEventAnimCmd(BaseItem* item, acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void onNotifyEventCollisionAttackCheck(BaseItem* item, int hitTaskId);
    virtual bool onNotifyEventCollisionSearch(BaseItem* item, soCollisionLog* collisionLog);
    virtual bool onNotifyEventCollisionSearchCheck(BaseItem* item, int searchHitTaskId, u8 searchHitCollisionIndex, Vec3f* searchHitPos);
    virtual void onNotifyEventLink(BaseItem* item, void* unk1, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
    virtual bool onNotifyEventCaptureStatus(BaseItem* item); // TODO
    virtual void onNotifyEventGimmick(BaseItem* item, soGimmickEventArgs* eventInfo, int* taskId);
    virtual void onUpdateKinetic(BaseItem* item);
    virtual void onUpdateAiDir(BaseItem* item, Vec2f*, Vec2f*, Vec2f*, Vec2f*);
    virtual void onUpdateAiMove(BaseItem* item, Vec2f*, Vec2f*, Vec2f*);
    virtual bool onSearchTarget(BaseItem* item, int* taskId, Vec3f pos, int);
    virtual u32 onShoot(BaseItem* item, u32, float lr, float);
    virtual u32 onShootBlanks(BaseItem* item, u32);
    virtual int onGetBullet(BaseItem* item);
    virtual void onThrowAttack(BaseItem* item, float, float* lr, Vec3f*, Vec3f*, float* powerMulStatus, bool*);
    virtual void onAction(BaseItem* item, u32, float rate);
    virtual int onResult(BaseItem* item);
    virtual bool onHave(BaseItem* item, int);
    virtual bool onPreDamageCheck(BaseItem* item, int damageStatusKind, soDamageLog*);
    virtual bool onDamage(BaseItem* item, int damageStatusKind, soDamageLog*);
    virtual bool onReflect(BaseItem* item);
    virtual void onPreBound(BaseItem* item, Vec2f*, BaseItem::BoundMask);
    virtual bool onRemoveModelConstraint(BaseItem* item, int);
    virtual bool onEnumFighter(BaseItem* item, Fighter* fighter);
    virtual int onGetLayerType(BaseItem* item);
    virtual bool isTreadPassive(BaseItem* item);
    virtual bool isUseTurnDamage(BaseItem* item);
    virtual bool isUseSpeedDamage(BaseItem* item);
    virtual bool isUseShake(BaseItem* item);
    virtual bool isUseScaleZ(BaseItem* item);
    virtual bool isUseThrowRotParam(BaseItem* item);
    virtual bool isSafe(BaseItem* item);
    virtual bool isConstraintHave(BaseItem* item);
    virtual bool isReferenceControlerHave(BaseItem* item);
    virtual itParam::KineticFlag getKineticFlags(BaseItem* item);
    virtual bool isUsePhysics(BaseItem* item);
};
static_assert(sizeof(itCustomizerInterface) == 12, "Class is wrong size!");

template <class T>
class itCustomizer : public itCustomizerInterface {
public:
    virtual ~itCustomizer() {}
};

class itNullCustomizer : public itCustomizer<itNullCustomizer> {
public:
    virtual ~itNullCustomizer();

    static itNullCustomizer* getInstance();
};
static_assert(sizeof(itNullCustomizer) == 12, "Class is wrong size!");