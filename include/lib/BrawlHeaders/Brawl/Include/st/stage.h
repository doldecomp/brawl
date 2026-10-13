#pragma once

#include <StaticAssert.h>
#include <GX.h>
#include <cm/cm_camera_controller.h>
#include <em/em_create.h>
#include <gf/gf_archive.h>
#include <gf/gf_task.h>
#include <gm/gm_lib.h>
#include <gr/gr_yakumono.h>
#include <if/if_smash_appear.h>
#include <it/item.h>
#include <memory.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <snd/snd_3d_generator.h>
#include <st/st_collision_attr_param.h>
#include <st/st_positions.h>
#include <st/st_trigger.h>
#include <st/st_shadow.h>
#include <types.h>

struct stGameFrame {
    float m_frameDelta;
    bool m_isJust;
    char _[3];
};

extern stGameFrame g_stGameFrame;

class stParam { // STPM
public:
    u8 m_echo;
    u8 m_id1;
    u8 m_id2;
    char _3;
    float _4;
    float _8;
    float _12;
    float _16;
    u8 m_bgmVolume;
    u8 m_sfxVolume;
    char _22;
    char _23;
    float m_shadowPitch;
    float m_shadowYaw;
    char _26[8];
    float m_camFOV;
    float m_camMinZ;
    float m_camMaxZ;
    float m_camMinTilt;
    float m_camMaxTilt;
    float m_camHorizontalRotationFactor;
    float m_camVerticalRotationFactor;
    float m_fighterBubbleBufferMultiplier;
    float _72;
    float m_cameraSpeed;
    float m_starKOCamTilt;
    float m_finalSmashCamTilt;
    float m_camRight;
    float m_camLeft;
    Vec3f m_pauseCamCenterPos;
    float m_pauseCamAngle;
    float m_pauseCamZoomIn;
    float m_pauseCamZoomDefault;
    float m_pauseCamZoomOut;
    float m_pauseCamRotYMin;
    float m_pauseCamRotYMax;
    float m_pauseCamRotXMin;
    float m_pauseCamRotXMax;
    Vec3f m_fixedCamCenterPos;
    float m_fixedCamFOV;
    float m_fixedHorizontalAngle;
    float m_fixedVerticalAngle;
    char _164[4];
    float m_olimarFinalCamAngle;
    Vec3f m_iceClimbersFinalPos;
    Vec2f m_iceClimbersFinalScale;
    Vec2f m_pitFinalPalutenaScale;
    u8 m_kirifudaModelType;
    bool m_characterWindEnabled;
    char _202[2];
    float m_windStrength;
    float m_horizontalWindRotation;
    float m_verticalWindRotation;
    float _216;
    GXColor _220;
    char _224[4];
    bool _228;
    bool _229;
    u8 m_effectVol;
    u8 m_reverbLPF;
    u8 m_reverbType;
    u8 m_reverbColoration;
    u8 m_reverbDamping;
    u8 m_reverbPreDelay;
    u8 m_reverbBalance;
    u8 m_delayFeedback;
    u8 m_delayOutput;
    char _239;
    s16 m_reverbTime;
    u16 m_delayTime;
    char _244[16];
};
static_assert(sizeof(stParam) == 260, "Class is wrong size!");

struct stDestroyBossParamCommon {
    char _[0x18];
};
static_assert(sizeof(stDestroyBossParamCommon) == 0x18, "Class is wrong size!");

class Stage;
extern Stage* g_Stage;
class Stage : public gfTask {
public:
    // 0
    u32 unk40;
    // 4
    srStageKind m_stageKind;
    // 8
    char _spacer1[0x10];
    // 18
    Rect2D m_deadRange;
    // 28
    Rect2D m_aiRange;
    // 38
    cmStageParam* m_cameraParam1;
    // 3c
    char _3c[0x4];
    // 40
    cmStageParam* m_cameraParam2;
    // 44
    char _spacer2[4];
    // 48
    Ground* m_headGround;
    // 4c
    void* m_collConv;
    // 50
    stPositions* m_stagePositions;
    // 54
    char _spacer3[4];
    // 58
    stParam* m_stageParam;
    // 5C
    void* m_stageData;
    // 60
    stTriggerMng* m_triggerMng;
    // 64
    char _spacer4[0x18];
    // 7C
    Vec3f* m_pokeTrainerPos;
    // 80
    u8 m_pokeTrainerPosIndex;
    // 81
    u8 m_pokeTrainerPosCount;
    // 82
    u8 m_pokeTrainerPosType;
    // 83
    char _0x83[1];
    // 84
    stShadow* m_shadow;
    // 88
    float _0x88[6];
    // A0
    char _0xA0[11];
    // AB
    bool m_isDevil;
    // AC
    Vec2f m_devilOffset;
    // B4
    char _0xB4[4];
    // B8
    char collisionAttrs[0xC];
    // C4
    gfArchive m_itemSheetArchive;
    // 144
    bool m_unk2;
    // 145
    char _spacer6[3];
    // 148
    u32 m_unk3;
    // 14C
    float m_unk4;
    // 150
    float m_frameRuleTime;
    // 154
    u32 unk194;
    // 158
    char _spacer7[0x8];
    // TOTAL_SIZE == 0x160

    void testStageParamInit(gfArchive* archive, int fileIndex);
    void testCollDataInit(gfArchive* archive, grCollData* collData, u32 index);
    void setCollision(grCollision* coll);
    void stageParamChange();
    void testStageDataInit(gfArchive* archive, int fileIndex, int unk2);
    void initSoundParameters();
    void setSoundParameters(stParam* stpm);
    void addGround(Ground* Ground);
    Ground* getGround(int index);
    u32 getGroundNum();
    grCollision* createCollision(gfArchive* archive, int index, Ground* ground);
    void createStagePositions();
    void createStagePositions(nw4r::g3d::ResFile* resFile);
    void loadStageAttrParam(gfArchive* filedata, int fileIndex);
    void registScnAnim(nw4r::g3d::ResFileData* scnData, u32 index);
    void initPosPokeTrainer(int unk1, int unk2);
    void setStageAttackData(grGimmickDamageFloor* attackData, u32 index);
    void removeGround(Ground*);
    bool isPokemonTrainer();

    Stage(const char* name, srStageKind stageKind);
    virtual void processBegin();
    virtual void processAnim();
    virtual void processUpdate();
    virtual void processMapCorrection();
    virtual void processFixCamera();
    virtual void processEnd();
    virtual void renderPre();
    virtual void renderDebug();
    virtual ~Stage();

    virtual void createObj();
    virtual void createObjPokeTrainer(gfArchive* filedata, int fileindex, const char* name, Vec3f* pokeTrainerPos, Vec3f* unk2);
    virtual int getPokeTrainerPointNum() { return 0; }
    virtual void getPokeTrainerPointData(int* unk1, int unk2) {}
    virtual float getPokeTrainerPositionZ() { return 0.0f; }
    virtual int getPokeTrainerDrawLayer() { return 0; }
    virtual bool isAdventureStage() { return false; }
#ifdef MATCHING
    virtual void getItemPac(gfArchive** brres, gfArchive** param, itKind itemID, int variantID);
#else
    virtual void getItemPac(gfArchive** brres, gfArchive** param, itKind itemID, int variantID, gfArchive** commonParam = NULL, itCustomizerInterface** customizer = NULL); // Note: Optional parameters for modding purposes to use custom itmParams and customizers
#endif
    virtual void getItemGenPac(gfArchive** archive);
    virtual void getItemPacEnemyFigure(gfArchive** archive);
    virtual void getEnemyPac(gfArchive** brres, gfArchive** param, gfArchive** enmCommon, gfArchive** primFaceBrres, EnemyKind enemyKind);
    virtual void getAdvRadarData(gfArchive**, gfArchive**);
    virtual void initializeStage();
    virtual void closeStage();
    virtual void renderDebugPositions();
    virtual bool loading();
    virtual void process();
    virtual void updateStagePositions();
    virtual void debugCollision();
    virtual Rect2D* getAIRange() { return &m_aiRange; }
    virtual int getDefaultLightSetIndex() { return 0x14; }
    virtual int getZoneLightSetIndex();
    virtual int getScrollDir(Vec3f* unk1)
    {
        unk1->m_x = 0.0f;
        unk1->m_y = 0.0f;
        unk1->m_z = 0.0f;
        return 0;
    }
    virtual void clearCameraParam();
    virtual void initCameraParam();
    virtual void startLoadLocalData();
    virtual bool isLoadLocalData();
    virtual int entryLocalData();
    virtual void removeLocalData();
    virtual void appearanceFighterLocal() {}
    virtual void getFighterStartPos(Vec3f* startPos, int fighterIndex);
    virtual void getFighterReStartPos(Vec3f* startPos, int fighterIndex);
    virtual bool isReStartSamePoint();
    virtual void getPokeTrainerStartPos(Vec3f* pos, u32);
    virtual u8 getItemPosCount();
    virtual void getItemPos(Vec3f*, Vec3f*, u32 index);
    virtual void getRandItemPos(Vec3f* pos);
    virtual void getKirifudaPos(Vec3f* pos, u32);
    virtual float getKirifudaAngle(u32);
    virtual void getKirifudaScale(Vec3f* scale, u32);
    virtual u8 getKirifudaModelType(u32);
    virtual u8 getPokeTrainerPosCount();
    virtual void getPokeTrainerPos(Vec3f*, Vec3f*, u32 index);
    virtual float getFighterDeadEffectSizeRate();
    virtual float getEnemyDeadEffectSizeRate();
    virtual float getEnableZ();
    virtual int getBgmID() { return 0; }
    virtual int getBgmID() const { return 0; }
    virtual int getNowStepBgmID() { return 0; }
    virtual int getBgmOptionID() { return 0; }
    virtual bool isBgmChange() { return m_unk2; }
    virtual void getBgmChangeID(u32* unk1, float* unk2)
    {
        *unk1 = m_unk3;
        *unk2 = m_unk4;
    }
    virtual void setBgmChange(float unk1, bool unk2, u32 unk3)
    {
        m_unk2 = unk2;
        m_unk3 = unk3;
        m_unk4 = unk1;
    }
    virtual float getBgmVolume() { return 1.0f; }
    virtual float getBgmPlayOffsetFrame() { return 0.0f; }
    virtual bool isNextStepBgmEqualNowStepBgmFromFlag() { return false; }
    virtual void setFrameRuleTime(float unk1) { m_frameRuleTime = unk1; }
    virtual float getFrameRuleTime() { return m_frameRuleTime; }
    virtual void notifyTimmingGameStart() {}
    virtual bool isEnd();
    virtual bool isEventEnd(int param1, int* eventState, int* eventDecision);
    virtual void enableDevil();
    virtual void disableDevil();
    virtual bool isDevil();
    virtual void setDevilScrool(float x, float y);
    virtual void getLucarioFinalTechniquePosition(Vec3f* pos);
    virtual bool startAppear();                              // TODO
    virtual void setAppearKind(u8 kind);                     // TODO
    virtual void endAppear();                                // TODO
    virtual IfSmashAppearTask* getAppearTask();              // TODO
    virtual void forceStopAppear();                          // TODO
    virtual GXColor getFinalTechniqColor();
    virtual void setMotionRatio(float unk1, float unk2);     // TODO
    virtual void saveMotionRatio(int unk1);                  // TODO
    virtual void restoreMotionRatio(int unk1);               // TODO
    virtual void setMotionSubRatio(float unk1, float unk2);  // TODO
    virtual void saveMotionSubRatio(int unk1);               // TODO
    virtual void restoreMotionSubRatio(int unk1);            // TODO
    virtual bool isCameraLocked() { return true; }
    virtual bool isBossBattleMode() { return false; }
    virtual bool isSimpleBossBattleMode() { return false; }
    virtual bool isAppear();             // TODO
    virtual bool isStartAppearTimming();  // TODO
    virtual void* getMadeinAiData();      // TODO
    virtual bool isBamperVector();       // TODO
    virtual void getBamperVector(Vec3f*);
    virtual void notifyEventInfoReady();                           // TODO
    virtual void notifyEventInfoGo();                              // TODO
#ifdef MATCHING
    virtual stDestroyBossParamCommon getDestroyBossParamCommon(u32);
#else
    virtual stDestroyBossParamCommon getDestroyBossParamCommon(u32, int enemyCreateId = -1, int enemyMessageKind = -1);
#endif
    virtual void stAdventureEventGetItem(int entryId, itKind kind, int itVariation, int genParamId, int instanceId);
    virtual void setStageOutEffectInit();                          // TODO
    virtual void setStageInEffectInit();                           // TODO
    virtual int helperStarWarp() { return 0; }
    virtual int initializeFighterAttackRatio() { return 0; }
    virtual void startFighterEvent() {}
    virtual int getZoneState(); // TODO
    virtual void getZonePos(Vec3f* pos);
    virtual float getMagmaHeight();   // TODO
    virtual float getAcidHeight();    // TODO
    virtual u8 getIteamDropStatus();
    virtual bool createWind2ndOnly();
    virtual grGimmickWindData2nd* getWind2ndOnlyData(); // TODO
    virtual void updateWind2ndOnly();
    virtual void setVision(u8);

    inline static Stage* getInstance() { return g_Stage; }
};


ENUM_U32(ArchiveOverrideSetting,
    Archive_Override_None = 0x0,
    Archive_Override_Brres = 0x1,
    Archive_Override_Param = 0x2,
    Archive_Override_Both = 0x3,
);

struct ItemOverride { // Custom Misc Data node
    char _header[4];
    char m_itmOverrideName[12];
    char m_pkmOverrideName[12];
    s8 m_pokemonOverload;
    ArchiveOverrideSetting m_overrideCommon : 8;
    ArchiveOverrideSetting m_overrideTorchic : 8;
    ArchiveOverrideSetting m_overrideCelebi : 8;
    ArchiveOverrideSetting m_overrideChikorita : 8;
    ArchiveOverrideSetting m_overrideChikoritaShot : 8;
    ArchiveOverrideSetting m_overrideEntei : 8;
    ArchiveOverrideSetting m_overrideMoltres : 8;
    ArchiveOverrideSetting m_overrideMunchlax : 8;
    ArchiveOverrideSetting m_overrideDeoxys : 8;
    ArchiveOverrideSetting m_overrideGroudon : 8;
    ArchiveOverrideSetting m_overrideGulpin : 8;
    ArchiveOverrideSetting m_overrideStaryu: 8;
    ArchiveOverrideSetting m_overrideStaryuShot : 8;
    ArchiveOverrideSetting m_overrideHoOh : 8;
    ArchiveOverrideSetting m_overrideHoOhShot : 8;
    ArchiveOverrideSetting m_overrideJirachi : 8;
    ArchiveOverrideSetting m_overrideSnorlax : 8;
    ArchiveOverrideSetting m_overrideBellosom : 8;
    ArchiveOverrideSetting m_overrideKyogre : 8;
    ArchiveOverrideSetting m_overrideKyogreShot : 8;
    ArchiveOverrideSetting m_overrideLatiasLatios : 8;
    ArchiveOverrideSetting m_overrideLugia : 8;
    ArchiveOverrideSetting m_overrideLugiaShot : 8;
    ArchiveOverrideSetting m_overrideManaphy : 8;
    ArchiveOverrideSetting m_overrideWeavile : 8;
    ArchiveOverrideSetting m_overrideElectrode : 8;
    ArchiveOverrideSetting m_overrideMetagross : 8;
    ArchiveOverrideSetting m_overrideMew : 8;
    ArchiveOverrideSetting m_overrideMeowth : 8;
    ArchiveOverrideSetting m_overrideMeowthShot : 8;
    ArchiveOverrideSetting m_overridePiplup : 8;
    ArchiveOverrideSetting m_overrideTogepi : 8;
    ArchiveOverrideSetting m_overrideGoldeen : 8;
    ArchiveOverrideSetting m_overrideGardevoir : 8;
    ArchiveOverrideSetting m_overrideWobbuffet : 8;
    ArchiveOverrideSetting m_overrideSuicune : 8;
    ArchiveOverrideSetting m_overrideBonsly : 8;
    ArchiveOverrideSetting m_overrideAndross : 8;
    ArchiveOverrideSetting m_overrideAndrossShot : 8;
    ArchiveOverrideSetting m_overrideBarbara : 8;
    ArchiveOverrideSetting m_overrideGrayFox : 8;
    ArchiveOverrideSetting m_overrideRayMKII : 8;
    ArchiveOverrideSetting m_overrideRayMKIIBomb : 8;
    ArchiveOverrideSetting m_overrideRayMKIIGun : 8;
    ArchiveOverrideSetting m_overrideSamuraiGoroh : 8;
    ArchiveOverrideSetting m_overrideDevil : 8;
    ArchiveOverrideSetting m_overrideExcitebike : 8;
    ArchiveOverrideSetting m_overrideJeff : 8;
    ArchiveOverrideSetting m_overrideJeffPencilBullet : 8;
    ArchiveOverrideSetting m_overrideJeffPencilRocket : 8;
    ArchiveOverrideSetting m_overrideLakitu : 8;
    ArchiveOverrideSetting m_overrideKnuckleJoe : 8;
    ArchiveOverrideSetting m_overrideKnuckleJoeShot : 8;
    ArchiveOverrideSetting m_overrideHammerBro : 8;
    ArchiveOverrideSetting m_overrideHammerBroHammer : 8;
    ArchiveOverrideSetting m_overrideHelirin : 8;
    ArchiveOverrideSetting m_overrideKat : 8;
    ArchiveOverrideSetting m_overrideAna : 8;
    ArchiveOverrideSetting m_overrideJillDozer : 8;
    ArchiveOverrideSetting m_overrideLyn : 8;
    ArchiveOverrideSetting m_overrideLittleMac : 8;
    ArchiveOverrideSetting m_overrideMetroid : 8;
    ArchiveOverrideSetting m_overrideNintendog : 8;
    ArchiveOverrideSetting m_overrideNintendogFull : 8;
    ArchiveOverrideSetting m_overrideMrResetti : 8;
    ArchiveOverrideSetting m_overrideIsaac : 8;
    ArchiveOverrideSetting m_overrideIsaacShot : 8;
    ArchiveOverrideSetting m_overrideSaki : 8;
    ArchiveOverrideSetting m_overrideSakiShot1 : 8;
    ArchiveOverrideSetting m_overrideSakiShot2 : 8;
    ArchiveOverrideSetting m_overrideShadow : 8;
    ArchiveOverrideSetting m_overrideWarInfantry : 8;
    ArchiveOverrideSetting m_overrideWarInfantryShot : 8;
    ArchiveOverrideSetting m_overrideStarfy : 8;
    ArchiveOverrideSetting m_overrideWarTank : 8;
    ArchiveOverrideSetting m_overrideWarTankShot : 8;
    ArchiveOverrideSetting m_overrideTingle : 8;
    ArchiveOverrideSetting m_overrideLakituSpiny : 8;
    ArchiveOverrideSetting m_overrideWaluigi : 8;
    ArchiveOverrideSetting m_overrideDrWright : 8;
    ArchiveOverrideSetting m_overrideDrWrightBuilding : 8;
    char m_stageItemFolder[12];
};

struct EnemyOverride { // Custom Misc Data node
    char _header[4];
    char m_enmOverrideFolder[12];
    char m_stageItemFolder[12];

    // HeapType instanceHeapType
    // HeapType resourceHeapType

    char _ : 4;
    bool m_useIndividualFolders : 1; // for Primids/Glire/Gamygabase
    bool m_overrideModuleCommon : 1;
    ArchiveOverrideSetting m_overrideCommon : 2;

    u8 m_faceIndexGoomba : 5;
    bool m_overrideModuleGoomba : 1;
    ArchiveOverrideSetting m_overrideGoomba : 2;

    u8 m_faceIndexPoppant : 5;
    bool m_overrideModulePoppant : 1;
    ArchiveOverrideSetting m_overridePoppant : 2;

    u8 m_faceIndexFeyesh : 5;
    bool m_overrideModuleFeyesh : 1;
    ArchiveOverrideSetting m_overrideFeyesh : 2;

    u8 m_faceIndexJyk : 5;
    bool m_overrideModuleJyk : 1;
    ArchiveOverrideSetting m_overrideJyk : 2;

    u8 m_faceIndexAuroros : 5;
    bool m_overrideModuleAuroros : 1;
    ArchiveOverrideSetting m_overrideAuroros : 2;

    u8 m_faceIndexCymul : 5;
    bool m_overrideModuleCymul : 1;
    ArchiveOverrideSetting m_overrideCymul : 2;

    u8 m_faceIndexRoturret : 5;
    bool m_overrideModuleRoturret : 1;
    ArchiveOverrideSetting m_overrideRoturret : 2;

    u8 m_faceIndexBorboras : 5;
    bool m_overrideModuleBorboras : 1;
    ArchiveOverrideSetting m_overrideBorboras : 2;

    u8 m_faceIndexGiantGoomba : 5;
    bool m_overrideModuleGiantGoomba : 1;
    ArchiveOverrideSetting m_overrideGiantGoomba : 2;

    u8 m_faceIndexBuckot : 5;
    bool m_overrideModuleBuckot : 1;
    ArchiveOverrideSetting m_overrideBuckot : 2;

    u8 m_faceIndexBucculus : 5;
    bool m_overrideModuleBucculus : 1;
    ArchiveOverrideSetting m_overrideBucculus : 2;

    u8 m_faceIndexGreap : 5;
    bool m_overrideModuleGreap : 1;
    ArchiveOverrideSetting m_overrideGreap : 2;

    u8 m_faceIndexArmight : 5;
    bool m_overrideModuleArmight : 1;
    ArchiveOverrideSetting m_overrideArmight : 2;

    u8 m_faceIndexBulletBill : 5;
    bool m_overrideModuleBulletBill : 1;
    ArchiveOverrideSetting m_overrideBulletBill : 2;

    u8 m_faceIndexRoader : 5;
    bool m_overrideModuleRoader : 1;
    ArchiveOverrideSetting m_overrideRoader : 2;

    u8 m_faceIndexSpaak : 5;
    bool m_overrideModuleSpaak : 1;
    ArchiveOverrideSetting m_overrideSpaak : 2;

    u8 m_faceIndexMite : 5;
    bool m_overrideModuleMite : 1;
    ArchiveOverrideSetting m_overrideMite : 2;

    u8 m_faceIndexTicken : 5;
    bool m_overrideModuleTicken : 1;
    ArchiveOverrideSetting m_overrideTicken : 2;

    u8 m_faceIndexTowtow : 5;
    bool m_overrideModuleTowtow : 1;
    ArchiveOverrideSetting m_overrideTowtow : 2;

    u8 m_faceIndexHammerBro : 5;
    bool m_overrideModuleHammerBro : 1;
    ArchiveOverrideSetting m_overrideHammerBro : 2;

    u8 m_faceIndexBytan : 5;
    bool m_overrideModuleBytan : 1;
    ArchiveOverrideSetting m_overrideBytan : 2;

    u8 m_faceIndexFloow : 5;
    bool m_overrideModuleFloow : 1;
    ArchiveOverrideSetting m_overrideFloow : 2;

    u8 m_faceIndexPuppit : 5;
    bool m_overrideModulePuppit : 1;
    ArchiveOverrideSetting m_overridePuppit : 2;

    u8 m_faceIndexPrimid : 5;
    bool m_overrideModulePrimid : 1;
    ArchiveOverrideSetting m_overridePrimid : 2;

    u8 m_faceIndexShellpod : 5;
    bool m_overrideModuleShellpod : 1;
    ArchiveOverrideSetting m_overrideShellpod : 2;

    u8 m_faceIndexKoopa : 5;
    bool m_overrideModuleKoopa : 1;
    ArchiveOverrideSetting m_overrideKoopa : 2;

    u8 m_faceIndexShaydas : 5;
    bool m_overrideModuleShaydas : 1;
    ArchiveOverrideSetting m_overrideShaydas : 2;

    u8 m_faceIndexBombed : 5;
    bool m_overrideModuleBombed : 1;
    ArchiveOverrideSetting m_overrideBombed : 2;

    u8 m_faceIndexPrimidMetal : 5;
    bool m_overrideModulePrimidMetal : 1;
    ArchiveOverrideSetting m_overridePrimidMetal : 2;

    u8 m_faceIndexNagagog : 5;
    bool m_overrideModuleNagagog : 1;
    ArchiveOverrideSetting m_overrideNagagog : 2;

    u8 m_faceIndexTrowlon : 5;
    bool m_overrideModuleTrowlon : 1;
    ArchiveOverrideSetting m_overrideTrowlon : 2;

    u8 m_faceIndexPrimidBig : 5;
    bool m_overrideModulePrimidBig : 1;
    ArchiveOverrideSetting m_overridePrimidBig : 2;

    u8 m_faceIndexPrimidBoom : 5;
    bool m_overrideModulePrimidBoom : 1;
    ArchiveOverrideSetting m_overridePrimidBoom : 2;

    u8 m_faceIndexPrimidFire : 5;
    bool m_overrideModulePrimidFire : 1;
    ArchiveOverrideSetting m_overridePrimidFire : 2;

    u8 m_faceIndexPrimidScope : 5;
    bool m_overrideModulePrimidScope : 1;
    ArchiveOverrideSetting m_overridePrimidScope : 2;

    u8 m_faceIndexPrimidSword : 5;
    bool m_overrideModulePrimidSword : 1;
    ArchiveOverrideSetting m_overridePrimidSword : 2;

    u8 m_faceIndexGamyga : 5;
    bool m_overrideModuleGamyga : 1;
    ArchiveOverrideSetting m_overrideGamyga : 2;

    u8 m_faceIndexROBBlaster : 5;
    bool m_overrideModuleROBBlaster : 1;
    ArchiveOverrideSetting m_overrideROBBlaster : 2;

    u8 m_faceIndexROBDistance : 5;
    bool m_overrideModuleROBDistance : 1;
    ArchiveOverrideSetting m_overrideROBDistance : 2;

    u8 m_faceIndexROBLauncher : 5;
    bool m_overrideModuleROBLauncher : 1;
    ArchiveOverrideSetting m_overrideROBLauncher : 2;

    u8 m_faceIndexROBSentry : 5;
    bool m_overrideModuleROBSentry : 1;
    ArchiveOverrideSetting m_overrideROBSentry : 2;

    u8 m_faceIndexAutolance : 5;
    bool m_overrideModuleAutolance : 1;
    ArchiveOverrideSetting m_overrideAutolance : 2;

    u8 m_faceIndexArmank : 5;
    bool m_overrideModuleArmank : 1;
    ArchiveOverrideSetting m_overrideArmank : 2;

    u8 m_faceIndexGlire : 5;
    bool m_overrideModuleGlire : 1;
    ArchiveOverrideSetting m_overrideGlire : 2;

    u8 m_faceIndexGlice : 5;
    bool m_overrideModuleGlice : 1;
    ArchiveOverrideSetting m_overrideGlice : 2;

    u8 m_faceIndexGlunder : 5;
    bool m_overrideModuleGlunder : 1;
    ArchiveOverrideSetting m_overrideGlunder : 2;

    u8 m_faceIndexPeteyPiranha : 5;
    bool m_overrideModulePeteyPiranha : 1;
    ArchiveOverrideSetting m_overridePeteyPiranha : 2;

    u8 m_faceIndexGamygaBase01 : 5;
    bool m_overrideModuleGamygaBase01 : 1;
    ArchiveOverrideSetting m_overrideGamygaBase01 : 2;

    u8 m_faceIndexGamygaBase02 : 5;
    bool m_overrideModuleGamygaBase02 : 1;
    ArchiveOverrideSetting m_overrideGamygaBase02 : 2;

    u8 m_faceIndexGamygaBase03 : 5;
    bool m_overrideModuleGamygaBase03 : 1;
    ArchiveOverrideSetting m_overrideGamygaBase03 : 2;

    u8 m_faceIndexGamygaBase04 : 5;
    bool m_overrideModuleGamygaBase04 : 1;
    ArchiveOverrideSetting m_overrideGamygaBase04 : 2;

    u8 m_faceIndexGalleom : 5;
    bool m_overrideModuleGalleom : 1;
    ArchiveOverrideSetting m_overrideGalleom : 2;

    u8 m_faceIndexRidley : 5;
    bool m_overrideModuleRidley : 1;
    ArchiveOverrideSetting m_overrideRidley : 2;

    u8 m_faceIndexRayquaza : 5;
    bool m_overrideModuleRayquaza : 1;
    ArchiveOverrideSetting m_overrideRayquaza : 2;

    u8 m_faceIndexDuon : 5;
    bool m_overrideModuleDuon : 1;
    ArchiveOverrideSetting m_overrideDuon : 2;

    u8 m_faceIndexPorky : 5;
    bool m_overrideModulePorky : 1;
    ArchiveOverrideSetting m_overridePorky : 2;

    u8 m_faceIndexMetaRidley : 5;
    bool m_overrideModuleMetaRidley : 1;
    ArchiveOverrideSetting m_overrideMetaRidley : 2;

    u8 m_faceIndexFalconFlyer : 5;
    bool m_overrideModuleFalconFlyer : 1;
    ArchiveOverrideSetting m_overrideFalconFlyer : 2;

    u8 m_faceIndexTabuu : 5;
    bool m_overrideModuleTabuu : 1;
    ArchiveOverrideSetting m_overrideTabuu : 2;

    u8 m_faceIndexMasterhand : 5;
    bool m_overrideModuleMasterhand : 1;
    ArchiveOverrideSetting m_overrideMasterHand : 2;

    u8 m_faceIndexCrazyhand : 5;
    bool m_overrideModuleCrazyhand : 1;
    ArchiveOverrideSetting m_overrideCrazyHand : 2;
};
extern EnemyOverride g_EnemyOverride;
