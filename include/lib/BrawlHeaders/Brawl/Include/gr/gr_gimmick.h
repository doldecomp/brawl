#pragma once

#include <StaticAssert.h>
#include <gr/gr_calc_world_callback.h>
#include <gr/ground.h>
#include <snd/snd_3d_generator.h>
#include <ec/ec_mgr.h>
#include <st/st_trigger.h>

struct grGimmickMotionPathData {
    enum PathMode {
        Path_Return = 0x0,
        Path_Loop = 0x1,
        Path_Once = 0x2,
    };

    float m_motionRatio;
    char m_index;
    PathMode m_pathMode : 8;
    char m_mdlIndex;
    char m_7;

    inline grGimmickMotionPathData() {}
    inline grGimmickMotionPathData(float motionRatio, u8 index, PathMode pathMode, u8 mdlIndex, u8 unk) : m_motionRatio(motionRatio), m_index(index), m_pathMode(pathMode), m_mdlIndex(mdlIndex), m_7(unk) {}
    inline grGimmickMotionPathData(float motionRatio, u8 index, PathMode pathMode, u8 mdlIndex) : m_motionRatio(motionRatio), m_index(index), m_pathMode(pathMode), m_mdlIndex(mdlIndex), m_7(0) {}
    inline grGimmickMotionPathData(float motionRatio, u8 index, u8 mdlIndex, u8 unk) : m_motionRatio(motionRatio), m_index(index), m_pathMode(Path_Return), m_mdlIndex(mdlIndex), m_7(unk) {}

    inline void set(float motionRatio, u8 index, u8 mdlIndex, u8 unk) {
        m_motionRatio = motionRatio;
        m_index = index;
        m_mdlIndex = mdlIndex;
        m_7 = unk;
    }

    inline void set(float motionRatio, u8 index, PathMode pathMode, u8 mdlIndex, u8 unk) {
        m_motionRatio = motionRatio;
        m_index = index;
        m_pathMode = pathMode;
        m_mdlIndex = mdlIndex;
        m_7 = unk;
    }
};
static_assert(sizeof(grGimmickMotionPathData) == 8, "Class is wrong size!");


class grGimmickMotionPathInfo;
class grGimmickMotionPath;

class grVisibleProduction {
    virtual ~grVisibleProduction();
    virtual void updateProduct();
    virtual void initialize();
    virtual void remove();
    virtual void setStart();
    virtual void productFlowStandby();
    virtual void productFlowStart();
    virtual void productFlowProducing();
    virtual void productFlowEnd();
    virtual void setEnable(bool enable);
    virtual bool isEnable();
    virtual bool isFinished();
    virtual bool isStandby();
    virtual bool isExecuting();
    virtual bool isVisiblePermission();
    virtual void setForcedEnding();

    int m_0x4;
    float m_0x8;
    bool m_enabled;
    bool m_visiblePermission;
    char _padding[2];
};

class grGimmick : public Ground {

public:
    struct AttackData {
        float m_damage;
        Vec3f m_offsetPos;
        float m_size;
        int m_vector;
        int m_reactionEffect;
        int m_reactionFix;
        int m_reactionAdd;
        char _spacer[4];
        soCollisionAttackData::Attribute m_attribute;
        bool m_isSetOffOn;
        bool m_noSetOffThru;
#ifdef MATCHING
        bool m_targetSituationAir;
#else
        u32 : 6;
        bool m_targetSituationODD : 1;
        bool m_targetSituationAir : 1;
#endif
        bool m_targetSituationGround;
        float m_slipChance;    // custom
        float m_hitStopFrame;  // custom
        float m_hitStopDelay;  // custom
#ifdef MATCHING
        unsigned int m_serialHitFrame;
#else
        bool m_isDirect : 1;
        bool m_isInvalidInvincible : 1;
        bool m_isInvalidXlu : 1;
        soCollisionAttackData::LrCheck m_lrCheck : 3;
        bool m_isCatch : 1;
        bool m_noTeam : 1;
        bool m_noHitStop : 1;
        bool m_noEffect : 1;
        bool m_noTransaction : 1;
        soCollisionAttackData::Region m_region : 5;
        unsigned int m_serialHitFrame : 16;
#endif
        soCollisionAttackData::SoundLevel m_soundLevel;
        soCollisionAttackData::SoundAttribute m_soundAttribute;
        bool m_noScale;
#ifdef MATCHING
        soCollision::ShapeType m_shapeType : 8;
#else
        u8 : 6;
        bool m_isDeath100 : 1; // custom
        soCollision::ShapeType m_shapeType : 1;
#endif
        char _spacer3[2];
        union { // custom
            struct {
                u16 m_noTargetCategory;
                u16 m_noTargetPart;
            };
            struct {
                unsigned int _pad2 : 6;
                bool m_noTargetCategoryFloor : 1;
                bool m_noTargetCategoryItemE : 1; // Soccer Ball, Blast Box etc.
                bool m_noTargetCategoryWall : 1;
                bool m_noTargetCategoryGimmick : 1;
                bool m_noTargetCategory5 : 1;
                bool m_noTargetCategory4 : 1;
                bool m_noTargetCategoryItem : 1; // Barrel, Crate etc.
                bool m_noTargetCategory2 : 1;
                bool m_noTargetCategoryEnemy : 1;
                bool m_noTargetCategoryFighter : 1;
                unsigned int _pad1 : 12;
                bool m_noTargetPartLeg : 1;
                bool m_noTargetPartKnee : 1;
                bool m_noTargetPartArm : 1;
                bool m_noTargetPartBody : 1;
            };
        };

        unsigned int m_nodeIndex;
        int m_power;

        inline AttackData() {};

        inline AttackData(Vec3f* offsetPos, float size, int vector,
                          int reactionEffect, int reactionFix, int reactionAdd,
                          soCollisionAttackData::Attribute attribute, bool isSetOffOn, bool noSetOffThru,
                          bool targetSituationAir, bool targetSituationGround, unsigned int serialHitFrame,
                          soCollisionAttackData::SoundLevel soundLevel,
                          soCollisionAttackData::SoundAttribute soundAttribute, bool noScale,
                          soCollision::ShapeType shapeType, unsigned int nodeIndex, int power) {
            initialize(offsetPos, size, vector, reactionEffect, reactionFix, reactionAdd, attribute, isSetOffOn,
                       noSetOffThru, targetSituationAir, targetSituationGround, serialHitFrame, soundLevel,
                       soundAttribute, noScale, shapeType, nodeIndex, power);

        };

        inline AttackData(float damage,
                          int reactionEffect, int reactionFix, int reactionAdd,
                          soCollisionAttackData::Attribute attribute, bool isSetOffOn, bool noSetOffThru,
                          bool targetSituationAir, unsigned int serialHitFrame,
                          soCollisionAttackData::SoundLevel soundLevel,
                          soCollisionAttackData::SoundAttribute soundAttribute, bool noScale,
                          bool targetSituationGround = true, int vector = 361) {
            initialize(damage, reactionEffect, reactionFix, reactionAdd, attribute, isSetOffOn, noSetOffThru,
                       targetSituationAir, serialHitFrame, soundLevel, soundAttribute, noScale, targetSituationGround,
                       vector);
        };

        inline void initialize(Vec3f* offsetPos, float size, int vector,
                               int reactionEffect, int reactionFix, int reactionAdd,
                               soCollisionAttackData::Attribute attribute, bool isSetOffOn, bool noSetOffThru,
                               bool targetSituationAir, bool targetSituationGround, unsigned int serialHitFrame,
                               soCollisionAttackData::SoundLevel soundLevel,
                               soCollisionAttackData::SoundAttribute soundAttribute, bool noScale,
                               soCollision::ShapeType shapeType, unsigned int nodeIndex, int power) {
            MEMINIT(this);
            m_offsetPos = *offsetPos;
            m_size = size;
            m_vector = vector;
            m_reactionEffect = reactionEffect;
            m_reactionFix = reactionFix;
            m_reactionAdd = reactionAdd;
            m_attribute = attribute;
            m_isSetOffOn = isSetOffOn;
            m_noSetOffThru = noSetOffThru;
            m_targetSituationAir = targetSituationAir;
            m_targetSituationGround = targetSituationGround;
            m_serialHitFrame = serialHitFrame;
            m_soundLevel = soundLevel;
            m_soundAttribute = soundAttribute;
            m_noScale = noScale;
            m_shapeType = shapeType;
            m_nodeIndex = nodeIndex;
            m_power = power;
        };

        inline void initialize(float damage,
                               int reactionEffect, int reactionFix, int reactionAdd,
                               soCollisionAttackData::Attribute attribute, bool isSetOffOn, bool noSetOffThru,
                               bool targetSituationAir, unsigned int serialHitFrame,
                               soCollisionAttackData::SoundLevel soundLevel,
                               soCollisionAttackData::SoundAttribute soundAttribute, bool noScale,
                               bool targetSituationGround = true, int vector = 361) {
            MEMINIT(this);
            m_damage = damage;
            m_reactionEffect = reactionEffect;
            m_reactionFix = reactionFix;
            m_reactionAdd = reactionAdd;
            m_attribute = attribute;
            m_isSetOffOn = isSetOffOn;
            m_noSetOffThru = noSetOffThru;
            m_targetSituationAir = targetSituationAir;
            m_serialHitFrame = serialHitFrame;
            m_soundLevel = soundLevel;
            m_soundAttribute = soundAttribute;
            m_noScale = noScale;

            m_targetSituationGround = targetSituationGround;
            m_vector = vector;
        };
    };
    static_assert(sizeof(AttackData) == 88, "Class is wrong size!");

    struct HitData {
        Vec3f m_startOffsetPos;
        Vec3f m_endOffsetPos;
        float m_size;
        u8 m_nodeIndex;
        char _29[3];
    };
    static_assert(sizeof(HitData) == 32, "Class is wrong size!");

    struct AttackDetails {
        union {
            soCollision::CategoryMask m_targetCategory;
            struct {
                unsigned int _pad : 22;
                bool m_targetCategoryFloor : 1;
                bool m_targetCategoryItemE : 1; // Soccer Ball, Blast Box etc.
                bool m_targetCategoryWall : 1;
                bool m_targetCategoryGimmick : 1;
                bool m_targetCategory5 : 1;
                bool m_targetCategory4 : 1;
                bool m_targetCategoryItem : 1; // Barrel, Crate etc.
                bool m_targetCategory2 : 1;
                bool m_targetCategoryEnemy : 1;
                bool m_targetCategoryFighter : 1;
            };
        };
        char m_unk1;
        bool m_targetSituationODD;
        char _spacer[2];
        soCollisionAttackData::LrCheck m_lrCheck;
        float m_hitStopFrame;
    };
    static_assert(sizeof(AttackDetails) == 16, "Class is wrong size!");

    struct SimpleEffectData {
        int m_id;
        short m_repeatFrame;
        short m_nodeIndex;
        short m_endFrame;
        short m_0xc;
    };

    struct Effect_Info {
        enum State {
            State_Inactive = 0x0,
            State_Start = 0x1,
            State_Active = 0x2,
        };

        State m_state : 16;
        short m_0x2;
        float m_framesActive;
        int m_handleId;
        int m_id;
        u32 m_repeatFrame;
        u32 m_endFrame;
        short m_nodeIndex;
        short m_generatorIndex;
        Vec2f m_offsetPos;
        float m_scale;

        inline void set(SndID sndId, u32 repeatFrame, short nodeIndex, u32 endFrame, Vec2f offsetPos) {
            m_id = sndId;
            m_repeatFrame = repeatFrame;
            m_nodeIndex = nodeIndex;
            m_endFrame = endFrame;
            m_offsetPos = offsetPos;
        }

        inline void set(EfID efId, u32 repeatFrame, short nodeIndex, u32 endFrame, Vec2f offsetPos, float scale) {
            m_id = efId;
            m_repeatFrame = repeatFrame;
            m_nodeIndex = nodeIndex;
            m_endFrame = endFrame;
            m_offsetPos = offsetPos;
            m_scale = scale;
        }
    };

    // 5C
    int m_soundGeneratorNum;
    // 60
    snd3DGenerator* m_soundGenerators;
    // 64
    int m_soundEffectNum;
    // 68
    Effect_Info* m_soundEffects;
    // 6C
    int m_effectNum;
    // 70
    Effect_Info* m_effects;
    // 74
    char _spacer6[8];
    // 7C
    void* m_gimmickData;
    // 80
    u32 m_unk1;
    // 84
    int m_nodeIndex;
    // 88
    bool m_isUpdate;
    // 89
    char unk3[3];
    // 8C
    grGimmickMotionPath* m_gimmickMotionPath;
    // 90
    grCalcWorldCallBack m_calcWorldCallBack;
    // A0
    union {
        struct {
            u8 m_motionPathFlagPadding : 6;
            bool m_isMotionPathRotate : 1;
            bool m_isMotionPathTranslate : 1;
        };
        u8 m_motionPathFlags;
    };

    // A1
    bool m_transparencyFlag;
    // A2
    char _spacer7[2];
    // A4
    union {
        struct {
            u32 m_transparencySettingPadding : 27;
            bool m_transparencySetting4 : 1;
            bool m_transparencySetting3 : 1;
            bool m_transparencySetting2 : 1;
            bool m_transparencySetting1 : 1;
            bool m_transparencySetting0 : 1;
        };
        u32 m_transparencySettings;
    };
    // A8
    char _spacer8[20];
    // BC
    grVisibleProduction* m_visibleProductions[4];
    // CC
    char _spacer9[0x40];

    grGimmick(const char* taskName);

    virtual void processUpdate();
    virtual void renderDebug();
    virtual void update(float deltaFrame);
    virtual void bindData(gfArchive* data);
    virtual void setVisibilityAttachedEffect(u32 unk1);
    virtual bool setNode();
    virtual void setMotionRatio(float ratio);
    virtual void startup(gfArchive* data, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual ~grGimmick();

    virtual void invalidatedByCameraClipping();
    virtual void setTransparencyFlag(char flag);
    virtual void updateCallback(u32 index);
    virtual void fixedPosition(float unk1);
    virtual void setTgtNode(const char* unk1);
    virtual char* getTgtNode();
    virtual void setGimmickData(void* gimmickData) { m_gimmickData = gimmickData; }
    virtual void* getGimmickData() { return m_gimmickData; }
    virtual void changeNodeAnim(u32 chrIndex, u32 modelAnimIndex);
    virtual void createFadeVisibleProduction(float unk);
    virtual void createSoundEffectVisibleProductionForExcel(u32 unk1, u32 unk2, u32 unk3);
    virtual void createEffectVisibleProductionForExcel(SimpleEffectData* simpleEffectData, u32* visProdIndexPtr, grVisibleProduction* visProds[]);
    virtual void setSimpleEffectVisibleProduction();        // TODO
    virtual void dbDispInvalidatedByCameraClippingSphere(); // TODO
    virtual void setTransparency(u32 unk1, u32 unk2);
    virtual u8 getTransparencyFlag() { return m_transparencyFlag; }

    void changeMatColAnim(u32 clrIndex, u32 modelAnimIndex);
    void changeShapeAnim(u32 shpIndex, u32 modelAnimIndex);
    void changeTexAnim(u32 patIndex, u32 modelAnimIndex);
    void changeTexSrtAnim(u32 srtIndex, u32 modelAnimIndex);
    void changeVisibleAnim(u32 visIndex, u32 modelAnimIndex);
    void createAttachMotionPath(grGimmickMotionPathInfo* motionPathInfo, stTriggerData* triggerData, const char* nodeName);
    void createEffectWork(int numEffects);
    void createIsValidTrigger(stTriggerData* triggerData);
    void createSimpleEffectData(SimpleEffectData* simpleEffectData, int effectId, const char* nodeName);
    void createSoundWork(u32 unk1, u32 unk2);
    u32 getMaterialColor(int* unk1, const char* unk2, u32* sceneModelIndex);
    u32 getMaterialTevColor(int* unk1, const char* unk2, u32* sceneModelIndex);
    void getMatrix(Matrix* matrix);
    void makeCalcuCallback(u32 numCallbackData, HeapType heapType);
    void setAttachPathdataFrame(float frame);
    void setCalcuCallbackRoot(u32 unk1);
    void setMaterialAlpha(const char* unk1, u32 unk2);
    void setMaterialColor(u32* unk1, const char* unk2, u32* unk3, u32* sceneModelIndex);
    void setMaterialTevColor(u32* unk1, const char* unk2, u32* unk3, u32* sceneModelIndex);
    void setMatrix(Matrix* matrix);
    void setPos(Matrix* matrix);
    void setPos(Vec3f* pos);
    void setPos(float x, float y, float z);
    void setPosGimmickEffect(u32 index, Vec3f* pos);
    void setPRSGimmickEffect(u32 index);
    void setRot(Vec3f* rot);
    void setRot(float x, float y, float z);
    void setScale(Vec3f* scale);
    void setScale(float x, float y, float z);
    Vec3f getPos();
    Vec3f getRot();
    Vec3f getScale();
    void startGimmickEffect(u32 index);
    void startGimmickSE(u32 index);
    void stopGimmickEffect(u32 index);
    void stopGimmickSE(u32 index);
    void updataGimmickEffect(float unk1);
    void updataGimmickSE(float unk1);
    void updateProduction(float unk1);
};
static_assert(sizeof(grGimmick) == 0x14c, "Class is wrong size!");

struct grGimmickMotionPathInfo {
    gfArchive* m_archive;
    grGimmickMotionPathData* m_motionPathData;
    union {
        struct {
            union {
                struct {
                    u8 : 6;
                    bool m_isRotate : 1;
                    bool m_isTranslate : 1;
                    u32 : 24;
                };
                struct {
                    u32 m_flags;
                };
            };
        };
    };

    grGimmick::SimpleEffectData* m_0xc;
    grGimmick::SimpleEffectData* m_0x10;
    grGimmick::SimpleEffectData* m_0x14;
    grGimmick::SimpleEffectData* m_0x18;
    grGimmick::SimpleEffectData* m_0x1c;
    grGimmick::SimpleEffectData* m_0x20;

    inline grGimmickMotionPathInfo(gfArchive* archive, grGimmickMotionPathData* motionPathData, bool isRotate, bool isTranslate) : m_archive(archive), m_motionPathData(motionPathData), m_isRotate(isRotate), m_isTranslate(isTranslate), m_0xc(NULL), m_0x10(NULL), m_0x14(NULL), m_0x18(NULL), m_0x1c(NULL), m_0x20(NULL) {}
    inline grGimmickMotionPathInfo(gfArchive* archive, grGimmickMotionPathData* motionPathData, u32 flags) : m_archive(archive), m_motionPathData(motionPathData), m_flags(flags), m_0xc(NULL), m_0x10(NULL), m_0x14(NULL), m_0x18(NULL), m_0x1c(NULL), m_0x20(NULL) {}
};