#pragma once

#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gf/gf_model.h>
#include <gf/gf_task.h>
#include <gr/collision/gr_collision_status.h>
#include <memory.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <gf/gf_3d_scene.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <so/so_array.h>
#include <st/st_trigger.h>
#include <types.h>

class Stage;

class Ground : public gfTask {
public:
    enum CollCategory
    {
        Coll_Category_Fighter = 0x0,
        Coll_Category_Enemy = 0x1,
        Coll_Category_Item = 0x2,
    };
    typedef u32 CollCategoryMask;
    static const CollCategoryMask COLL_CATEGORY_MASK_FIGHTER = 1 << Coll_Category_Fighter;
    static const CollCategoryMask COLL_CATEGORY_MASK_ENEMY = 1 << Coll_Category_Enemy;
    static const CollCategoryMask COLL_CATEGORY_MASK_ITEM = 1 << Coll_Category_Item;
    static const CollCategoryMask COLL_CATEGORY_MASK_ALL = COLL_CATEGORY_MASK_FIGHTER | COLL_CATEGORY_MASK_ENEMY | COLL_CATEGORY_MASK_ITEM;

    struct CollCategoryFlag {
        union {
            struct {
                u32 : 29;
                bool m_item : 1;
                bool m_enemy : 1;
                bool m_fighter : 1;
            };
            CollCategoryMask m_mask;
        };
        inline CollCategoryFlag() {}
        inline CollCategoryFlag(CollCategoryMask bits) : m_mask(bits) {}
    };

    // 0
    nw4r::g3d::ResFile m_resFile;
    // 4
    nw4r::g3d::ScnMdl** m_sceneModels; // TODO: supposed to be a wrapper of some kind
    // 8
    gfModelAnimation** m_modelAnims;
    // C
    grCollision* m_collision;
    // 10
    Ground* m_nextGround;
    // 14
    char _spacer2[0x4];
    // 18
    u32 m_modelAnimNum;
    // 1C
    u16 m_mdlIndex;
    // 1E
    char _spacer3[2];
    // 20
    void* m_stageData;
    // 24
    float m_motionRatio;
    // 28
    char _align[4];
    // 2c
    bool m_isVisible : 1;
    bool m_isVisibleByClipping : 1;
    bool m_isEnableCollisionStatus : 1;
    bool m_isEnableCollisionStatusByClipping : 1;
    bool m_isEnableCalcCollision : 1;
    bool m_hasBindedData : 1;
    bool m_hasUpdatedG3dCalcWorld : 1;
    bool m_isUseMdlNameForStartAnim : 1;
    // 2d
    bool m_isCopyVisibility : 1;
    bool m_isValid : 1;
    bool m_noUpdateAnim : 1;
    bool m_isPauseAnim : 1;
    bool m_isUpdateG3dCalcWorld : 1;
    bool m_isGr2 : 1;
    bool m_isEnableBlendColor : 1;
    bool m_isSetup : 1;
    // 2e
    char _spacer[2];
    // 30
    HeapType m_heapType;
    // 34
    char _spacer5[40];

    Ground(const char* taskName);
    virtual void processAnim();
    virtual void processUpdate();
    virtual void processGameProc();
    virtual void renderPre();
    virtual void renderDebug();
    virtual ~Ground();

    virtual void update(float deltaFrame);
    virtual void loadGroundData(nw4r::g3d::ResFile, u32 unk2, gfSceneRoot::LayerType unk3);
    virtual void bindData(gfArchive* data);
    virtual void setupMelee();
    virtual void setVisibility(u32 unk1);
    virtual void setVisibilityByClipping(u32 unk1);
    virtual void setVisibilityAttachedEffect(u32 unk1);
    virtual void receiveCollMsg(int direction, grCollStatus* collStatus, grCollisionJoint* collisionJoint);
    virtual void receiveCollMsg_Landing(grCollStatus* collStatus, grCollisionJoint* collisionJoint, bool isFirstContact);
    virtual void receiveCollMsg_Heading(grCollStatus* collStatus, grCollisionJoint* collisionJoint, bool isFirstContact);
    virtual void receiveCollMsg_Wall(grCollStatus* collStatus, grCollisionJoint* collisionJoint, bool isFirstContact);
    virtual void receiveCollMsg_Attack(grCollStatus* collStatus, grCollisionJoint* collisionJoint);
    virtual void unloadData();
    virtual int getModelCount() {
        if (m_resFile.ptr()) {
            return m_resFile.GetResMdlNumEntries();
        }
        return 0;
    };
    virtual void startup(gfArchive* data, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual bool setNode();
    virtual void setStageData(void* stageData) { m_stageData = stageData; }
    virtual void* getStageData() { return m_stageData; }
    virtual void initStageData() { }
    virtual void setMdlIndex(int mdlIndex) { m_mdlIndex = mdlIndex; }
    virtual short getMdlIndex() { return m_mdlIndex; }
    virtual bool isEnableCalcCollision() { return m_isEnableCalcCollision; }
    virtual void enableCalcCollision() { m_isEnableCalcCollision = 1; }
    virtual void disableCalcCollision() { m_isEnableCalcCollision = 0; }
    virtual u32 getNodeIndex(u32 sceneModelIndex, const char* nodeName);
    virtual bool getNodePosition(Vec3f* nodePos, u32 sceneModelIndex, u32 nodeIndex);
    virtual bool getNodePosition(Vec3f* nodePos, u32 sceneModelIndex, const char* nodeName);
    virtual bool getNodeMatrix(Matrix* nodeMtx, u32 sceneModelIndex, u32 nodeIndex);
    virtual bool getNodeMatrix(Matrix* nodeMtx, u32 sceneModelIndex, const char* nodeName);
    virtual bool setNodeVisibility(bool setVisibility, u32 sceneModelIndex, u32 nodeIndex, bool recursive, bool recursive_);
    virtual bool setNodeVisibility(bool setVisibility, u32 sceneModelIndex, const char* nodeName, bool recursive, bool recursive_);
    virtual bool setNodeVisibilityAll(bool unk1, u32 sceneModelIndex);
    virtual bool isNodeVisible(u32 sceneModelIndex, u32 nodeIndex);
    virtual bool setNodeCollision(bool setCollision, u32 sceneModelIndex, u32 nodeIndex, bool recursive);
    virtual bool setNodeCollision(bool setCollision, u32 sceneModelIndex, const char* nodeName, bool recursive);
    virtual bool getNodeScale(Vec3f* nodeScale, u32 sceneModelIndex, u32 nodeIndex);
    virtual bool getNodeScale(Vec3f* nodeScale, u32 sceneModelIndex, const char* nodeName);
    virtual void setValid(u32 unk1);
    virtual void setValidAttachedEffect(u32 unk1);
    virtual void setInitializeFlag() { }
    virtual void setInitializeInfo(int initializeInfo) { }
    virtual bool getInitializeInfo(int initializeInfo) { return false; }
    virtual void setMotionRatio(float ratio);
    virtual void setMotionFrame(float frame, u32 animIndex);
    virtual float getMotionFrame(u32 anim);
    virtual void setMotionLoop(bool shouldLoop, u32 animIndex);
    virtual void setMatAlphaMul(u32 unk1, u32 sceneModelIndex); // TODO
    virtual void setMatAlpha(u32 unk1, u32 sceneModelIndex);    // TODO
    virtual void updateG3dProcCalcWorld();
    virtual void preExit();
    virtual bool adventureEventGetItem(int genParamId, stTriggerData* triggerData) { return false; }
    virtual void invalidatedByCameraClipping();
    virtual void setTransparencyFlag(char flag);

    bool getNodeIndex(u32* nodeIndex, u32 sceneModelIndex, const char* nodeName);
    void addSceneRoot(nw4r::g3d::ScnMdl* sceneModel, int unk2);
    bool isCollisionStatusOwnerTask(grCollStatus* collStatus, CollCategoryFlag*);
    bool searchNode(const char* unk1, const char* nodeName, int* unk3, u32* nodeIndex);
    void setBlendColorDisable();
    void setBlendColorEnable();
    void setDontMoveGround();
    void setEnableCollisionStatus(bool enableColl);
    void setEnableCollisionStatusByClipping(bool enableColl);
    void setVisibilityByClipping(int unk1, u32 sceneModelIndex);
    void updateG3dProcCalcWorldForce();
};
static_assert(sizeof(Ground) == 0x9C, "Class is wrong size!");

// Size: 196
