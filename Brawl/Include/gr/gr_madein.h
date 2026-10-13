#pragma once

#include <StaticAssert.h>
#include <gr/gr_seq_yakumono.h>
#include <mt/mt_vector.h>
#include <so/collision/so_collision_log.h>
#include <so/damage/so_damage.h>
#include <so/damage/so_damage_attacker_info.h>

class grMadein : public grSeqYakumono {
public:
    enum AttackPreset {
        Attack_Default = 0x0,
        Attack_Up = 0x1,
        Attack_Left = 0x2,
        Attack_Right = 0x3,
        Attack_Overwrite = 0x4,
    };

    class AttackInfo {
    public:
        float m_size;
        Vec3f m_offsetPos;
        char _spacer[0x18];
        AttackPreset m_preset;
    };

    class HitPointInfo {
    public:
        Vec3f m_startOffsetPos;
        Vec3f m_endOffsetPos;
        char _spacer[12];
        float m_size;
        float m_lastDamageTaken;
        float m_lastSide;
        char _spacer2[8];
        int m_lastPlayerHit;
        int m_nodeIndex;
    };

    class StageHitData {
        Vec3f m_startOffsetPos;
        Vec3f m_endOffsetPos;
        float m_size;
        char _spacer[8];
        int m_nodeIndex;
        char _spacer2[20];
    };

    enum HitCategory {
        Hit_Category_Gimmick = 0x0,
        Hit_Category_Wall = 0x1,
        Hit_Category_Enemy = 0x2
    };

protected:
    AttackInfo* m_attackInfo;
    HitPointInfo* m_hitPointInfo;
    soCollisionAttackData* m_overwriteAttackData;
    StageHitData* m_stageHitData;
    bool m_300_7 : 1;                 // | 0x80
    bool m_hasAttack : 1;             // | 0x40
    bool m_hasHitPoint : 1;           // | 0x20
    bool m_isHit : 1;                 // | 0x10
    HitCategory m_hitCategory : 2; // | 0x4, 0x8
    bool m_isLandedOn : 1;            // | 0x2
    bool m_useLandCheck : 1;          // | 0x1
    char _301[3];
    float m_304;
    char _308[4];
    int m_landerTaskId;
    char _316[38];

public:
    void createAttackPoint();
    void createAttackPointNormal(soCollisionAttackData* attackData);
    void deleteAttackPoint();
    void deleteHitPoint();
    void endEntity();
    float getEntityFrame();
    soCollisionAttackData* getOverwriteAttackData();
    soCollisionAttackData* getOverwiteAttackData();
    void initializeEntity();
    bool isEndEntity();
    bool isFrameEndOffset(float unk);
    bool isFrameOffset(float unk);
    void pauseEntity(bool isPause);
    void setAttack(float size, Vec3f* offsetPos);
    void setHitPoint(float size, Vec3f* startOffsetPos, Vec3f* endOffsetPos, bool, int nodeIndex);
    void setMatrix(Matrix matrix, void* unk1);
    void setMotion(u32 anmIndex);
    void setMotionDetails(u32 anmChrIndex, u32 anmVisIndex, u32 anmTexPatIndex, u32 anmTexSrtIndex, u32 anmClrIndex);
    void setupYakumonoClass();
    void startEntity();
    void startEntityAutoLoop();
    void startEntityLoop(int unk1);
    void switchToMatrix();
    inline void setAttackPreset(AttackPreset preset) {
        this->m_attackInfo->m_preset = preset;
    };
    inline soCollisionAttackData* setAttackOverwrite() {
        Vec3f pos(0.0, 0.0, 0.0);
        this->setAttack(0, &pos);
        this->m_attackInfo->m_preset = Attack_Overwrite;
        return this->getOverwriteAttackData();
    }
    inline void setAttack(float size, Vec3f* offsetPos, AttackPreset preset) {
        this->setAttack(size, offsetPos);
        this->m_attackInfo->m_preset = preset;
        if (preset == Attack_Overwrite) {
            this->getOverwriteAttackData();
        }
    }
    inline int getLanderTaskId() {
        return this->m_landerTaskId;
    };
    
    inline int isHit() {
        return this->m_isHit;
    };
    
    inline int getLastDamageTaken() {
        return this->m_hitPointInfo->m_lastDamageTaken;
    };

    grMadein(const char* taskName);
    virtual void setTgtNode(const char* unk1);
    virtual char* getTgtNode();
    virtual void onDamage(int index, soDamage* damage, soDamageAttackerInfo* attackerInfo);
    virtual void onInflictEach(soCollisionLog* collisionLog, float power);
    virtual void receiveCollMsg_Landing(grCollStatus* collStatus, grCollisionJoint* collisionJoint, bool isFirstContact);
    virtual void startup(gfArchive* data, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void update(float deltaFrame);
    virtual ~grMadein();

    static grMadein* create(int mdlIndex, const char* tgtNodeName, const char* taskName, HeapType heapType);
};
static_assert(sizeof(grMadein) == 0x1a4, "Class is wrong size!");
