#include <cm/cm_camera_controller.h>
#include <cm/cm_subject.h>
#include <gf/gf_archive.h>
#include <gf/gf_camera.h>
#include <gr/gr_madein.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/math/math_triangular.h>
#include <snd/snd_id.h>
#include <snd/snd_system.h>
#include <st_tengan/gr_tengan.h>
#include <st_tengan/gr_tengan_bg.h>
#include <st_tengan/gr_tengan_floor.h>
#include <st_tengan/gr_tengan_ashiba.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>
#include <gf/gf_copyefb.h>
#include <gf/gf_slow_manager.h>

#include <st_tengan/st_tengan.h>
#include <st_tengan/st_tengan_data.h>


#include <gm/gm_global.h>
#include <ec/ec_mgr.h>
#include <OS/OSError.h>
#include <cm/cm_quake.h>
#include <ef/ef_screen.h>
#include <ai/ai_mgr.h>

stClassInfoImpl<Stages::Tengan, stTengan> stTengan::bss_loc_14;

stTengan::stTengan() : stMelee("stTengan", Stages::Tengan) {
    
//    void* m_shrineStageData;
    m_substage = 0;
    m_slow = -1;
    unk1d8 = 0.0;
    unk1dc = 0.0;
    m_rollTargetDegrees = 0.0;
    m_rollDegrees = 0.0;
    m_rollDirection = 0.0;
    m_rollSpeed = 0.0;
    m_reverseTargetDegrees = 0.0;
    m_reverseDegrees = 0.0;
    m_reverseDirection = 0.0;
    m_reverseSpeed = 0.0;
    unk200 = 0.0;
}

stTengan* stTengan::create() {
    return new (Heaps::StageInstance) stTengan;
}

stTengan::~stTengan() {
    releaseArchive();
    gfCopyEFBMgr::getInstance()->m_104=false;
    gfCopyEFBMgr::getInstance()->m_108=0x80;
    g_gfSceneRoot->m_transformFlag.m_mask &= 0xFFFFFF;
    if (m_slow != -1) {
        
    }
}

bool stTengan::loading() {
    return true;
}

void stTengan::createObj()
{
    testStageParamInit(m_fileData, 0xA);
    testStageDataInit(m_fileData, 0x14, 1);
    switch(g_GameGlobal->m_modeMelee->m_meleeInitData.m_subStageKind) {
        case 2:
            m_substage = 2;
            break;
        case 1:
            m_substage = 1;
            break;
        case 0:
        default:
            m_substage = 0;
            break;
    }
    
    createObjEnkei(0);
    createObjEnkei(1);
    createObjBg(2);
    grMadein* ground;
    if (m_substage == 0) {
        createObjDialga(3);
    } else {
        ground = grMadein::create(20, "dummy", "dummy",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        //ground->setType(0);
        ground->initializeEntity();
    }
    createObjAshiba(4);
    createObjAshiba(5);
    createObjFloor(6);
    createObjFloor(7);
    createObjFloor(8);
    createObjFloor(9);
    createObjFloor(10);
    createObjSkyLaser(11);
    createObjSkyLaser(12);
    createObjSkyLaser(13);
    createObjSkyLaser(14);
    createObjDialga(15);
    createObjDialga(16);
    createObjDialga(17);
    
    if (m_substage == 1) {
        createObjDialga(18);
    } else {
        ground = grMadein::create(20, "dummy", "dummy",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->initializeEntity();
    }
    
    if (m_substage == 2) {
        createObjDialga(19);
    } else {
        ground = grMadein::create(20, "dummy", "dummy",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->initializeEntity();
    }
    
    ground = grMadein::create(20, "LaserAttackPointShort", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    Vec3f offset;
    offset.m_x = 0.0;
    offset.m_y = -100.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    soCollisionAttackData* attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 100;
    attack->m_reactionFix = 70;
    attack->m_reactionAdd = 0;
    attack->m_power = 1;
    attack->m_vector = 160;
    attack->m_nodeIndex = 0;
    attack->m_size = 15.0;
    attack->m_offsetPos.m_x = offset.m_x;
    attack->m_offsetPos.m_y = offset.m_y;
    attack->m_offsetPos.m_z = offset.m_z;
    attack->m_targetSituation = 0;
    attack->m_targetPart = 0;
    attack->m_region = soCollisionAttackData::Region_None;
    attack->m_targetCategory = soCollision::CATEGORY_MASK_ALL;
    attack->m_attribute = soCollisionAttackData::Attribute_None;
    //attack->m_targetLr = true;
//    attack->m_targetPart = 0;
    attack->m_soundAttribute = soCollisionAttackData::Sound_Attribute_Elec;
    attack->m_soundLevel = soCollisionAttackData::Sound_Level_Large;
//    attack->m_setOffKind = soCollisionAttackData::SetOff_Thru;
//    attack->m_noScale = false;
    //attack->m_isShieldable = true; //need to match this somehow
//    attack->m_isReflectable = false;
//    attack->m_isAbsorbable = false;
//    attack->m_subShield = 0;
//    attack->m_isCapsule = false;
    attack->m_serialHitFrame = 2;
    attack->m_shapeType = soCollision::Shape_Capsule;
        //ground->setType(1);
    ground->initializeEntity();
    
    ground = grMadein::create(20, "LaserAttackPointLong", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = -180.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 100;
    attack->m_reactionFix = 70;
    attack->m_reactionAdd = 0;
    attack->m_power = 1;
    attack->m_vector = 160;
    attack->m_size = 15.0;
    ground->initializeEntity();
    
    ground = grMadein::create(20, "LaserAttackPointSide", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = 400.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 100;
    attack->m_reactionFix = 70;
    attack->m_reactionAdd = 0;
    attack->m_power = 1;
    attack->m_vector = 160;
    attack->m_size = 15.0;
    ground->initializeEntity();
    
    ground = grMadein::create(20, "LaserAttackPointSide", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = -100.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 150;
    attack->m_reactionFix = 0;
    attack->m_reactionAdd = 80;
    attack->m_power = 5;
    attack->m_vector = 361;
    attack->m_size = 15.0;
    ground->initializeEntity();
    
    ground = grMadein::create(20, "LaserAttackPointSide", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = -180.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 150;
    attack->m_reactionFix = 0;
    attack->m_reactionAdd = 80;
    attack->m_power = 5;
    attack->m_vector = 361;
    attack->m_size = 15.0;
    ground->initializeEntity();
    
    ground = grMadein::create(20, "LaserAttackPointSide", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = 400.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 130;
    attack->m_reactionFix = 0;
    attack->m_reactionAdd = 120;
    attack->m_power = 5;
    attack->m_vector = 30;
    attack->m_size = 15.0;
    ground->initializeEntity();
    
    ground = grMadein::create(20, "AuraAttackPoint", "AuraAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;
    offset.m_y = 0.0;
    offset.m_z = 0.0;
    ground->setAttack(30.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    attack = ground->getOverwriteAttackData();
    attack->m_reactionEffect = 50;
    attack->m_reactionFix = 0;
    attack->m_reactionAdd = 90;
    attack->m_power = 25;
    attack->m_vector = 70;
    attack->m_size = 34.0;
    attack->m_offsetPos.m_x = offset.m_x;
    attack->m_offsetPos.m_y = offset.m_y;
    attack->m_offsetPos.m_z = offset.m_z;
//    attack->m_targetCategoryGimmick = true; // Ground
//    attack-> m_targetCategory5 = true;
//    attack-> m_targetCategory4 = true;
//    attack->m_targetCategoryItem = true; // Barrel, Crate etc.
//    attack->m_targetCategory2 = true;
//    attack->m_targetCategoryEnemy = true; // SSE enemies
//    attack->m_targetCategoryFighter = true; // Fighter
    //attack->m_nodeIndex = 2;
    attack->m_attribute = soCollisionAttackData::Attribute_Electric;
    attack->m_soundLevel = soCollisionAttackData::Sound_Level_Large;
    attack->m_soundAttribute = soCollisionAttackData::Sound_Attribute_Elec;
    //attack->m_targetSituationODD = true;
    //attack->m_targetSituationAir = true;
    //attack->m_targetSituationGround = true;
    attack->m_serialHitFrame = 2;
    attack->m_shapeType = soCollision::Shape_Capsule;
//    attack->m_setOffKind = soCollisionAttackData::SetOff_Thru;
//    attack->m_noScale = false;
//    attack->m_isShieldable = false;
//    attack->m_isReflectable = false;
//    attack->m_isAbsorbable = false;
//    attack->m_subShield = 0;
//    attack->m_isCapsule = false;
    ground->initializeEntity();
    offset.m_x = 5.0;
    offset.m_y = 20.0;
    offset.m_z = 0.0;
    ground->setPos(&offset);
    
    ground = grMadein::create(20, "Gake", "Collision",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->initializeEntity();
    createCollision(m_fileData, 3, ground);
    ground->setEnableCollisionStatus(false);
    
    ground = grMadein::create(21, "Laser", "A1Sign",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->initializeEntity();
    
    ground = grMadein::create(22, "Laser", "A2Sign",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->initializeEntity();
    
    ground = grMadein::create(23, "Laser", "BSign",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->initializeEntity();
    
    if (m_substage == 2) {
        ground = grMadein::create(24, "Boomerang", "Boomerang",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        offset.m_x = 0.0;
        offset.m_y = 0.0;
        offset.m_z = 0.0;
        ground->setAttack(15.0,&offset);
        ground->setAttackPreset(grMadein::Attack_Overwrite);
        attack = ground->getOverwriteAttackData();
        attack->m_reactionEffect = 100;
        attack->m_reactionFix = 0;
        attack->m_reactionAdd = 70;
        attack->m_power = 20;
        attack->m_vector = 361;
        attack->m_size = 5.0;
        ground->initializeEntity();
        
        ground = grMadein::create(25, "RCall", "Rcall",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setAttack(15.0,&offset);
        attack = ground->getOverwriteAttackData();
        attack->m_reactionEffect = 100;
        attack->m_reactionFix = 70;
        attack->m_reactionAdd = 0;
        attack->m_power = 1;
        attack->m_vector = 160;
        attack->m_size = 15.0;
        ground->initializeEntity();
    
        ground = grMadein::create(26, "SonicWave", "SW",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->initializeEntity();
    
        ground = grMadein::create(27, "SonicWaveCutter", "SWCut",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->initializeEntity();
    
        ground = grMadein::create(27, "SonicWaveCutterPath", "SWCutPath",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->initializeEntity();
        
        ground = grMadein::create(20, "", "SWDmg",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        offset.m_x = 0.0;
        offset.m_y = -100.0;
        offset.m_z = 0.0;
        ground->setAttack(3.0,&offset);
        ground->setAttackPreset(grMadein::Attack_Overwrite);
        attack = ground->getOverwriteAttackData();
        ground->initializeEntity();
    }
    
    createCollision(m_fileData, 2, NULL);
    initCameraParam();
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x64, 0xfffe));
    if (posData.ptr())
    {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    }
    else
    {
        // if no stgPos model in pac, use defaults
        createStagePositions();
    }
    createWind2ndOnly();
    nw4r::g3d::ResFileData* scnData;
    if (m_substage == 1) {
        scnData = static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 1, 0xfffe));
        registScnAnim(scnData, 0);
    } else {
        scnData = static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xfffe));
        registScnAnim(scnData, 0);
    }
    stTenganParams* stagedata = (stTenganParams*)m_stageData;
    if (stagedata) {
        float tempf7 = randf()*2.0f;
        if (stagedata->guest_rate_guest <= 1.0f - tempf7) {
            
            event15.set(0.0,0.0);
            event14.set(0.0,0.0);
            event14.start();
        }
        event1.set(0.0,0.0);
        event2.set(0.0,0.0);
        eventLegendDisappear.set(0.0,0.0);
        eventDropStage.set(0.0,0.0);
        eventRebuildStage.set(0.0,0.0);
        eventQuake.set(stagedata->event_frame_quake,stagedata->event_frame_quake);
        eventLaser.set(100.0,100.0);
        eventCameraRoll.set(100.0,500.0);
        switch(m_substage) {
            case 0:
                eventSlow.set(stagedata->event_d_frame_slow_min+60.0f,stagedata->event_d_frame_slow_max+60.0f);
                eventAura.set(stagedata->event_d_frame_aura_min,stagedata->event_d_frame_aura_max);
                break;
            case 1:
                eventUpDownReverse.set(stagedata->event_p_frame_reversey_min+60.0f,stagedata->event_p_frame_reversey_max+60.0f);
                eventLeftRightReverse.set(stagedata->event_p_frame_reversex_min+60.0f,stagedata->event_p_frame_reversex_max+60.0f);
                eventGravityHalf.set(stagedata->event_p_frame_gravityhalf_min+60.0f,stagedata->event_p_frame_gravityhalf_min+60.0f);
                break;
            case 2:
                eventBoomerang.set(0.0,0.0);
                eventRandomCall.set(300.0,600.0);
                eventSonicWaveCall.set(300.0,600.0);
                break;
        }
        event1.start();
    }
    loadStageAttrParam(m_fileData, 0x1E);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 101, "PokeTrainer00", this->m_pokeTrainerPos, 0x0);
    createObjPokeTrainer(m_fileData, 102, "PokeTrainer01", this->m_pokeTrainerPos+2, 0x0);
}

void stTengan::createObjSkyLaser(int index) {
    grMadein *laser;
    switch(index) {
        case 11:
            laser = grMadein::create(11, "StgTenganLaserA1", "grTengan_LaserA1",Heaps::StageInstance);
            break;
        case 12:
            laser = grMadein::create(12, "StgTenganLaserA2", "grTengan_LaserA2",Heaps::StageInstance);
            break;
        case 13:
            laser = grMadein::create(13, "StgTenganLaserB", "grTengan_LaserB",Heaps::StageInstance);
            break;
        case 14:
            laser = grMadein::create(14, "StgTenganLaserCharge", "grTengan_LaserCharge",Heaps::StageInstance);
            break;
        default:
            laser = NULL;
    }
    if (laser) {
        addGround(laser);
        laser->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        laser->setStageData(m_stageData);
        laser->initializeEntity();
        laser->m_sceneModels[0]->SetPriorityDrawOpa(255);
        laser->m_sceneModels[0]->SetPriorityDrawXlu(255);
    }
}

void stTengan::createObjEnkei(int index) {
    grTengan *enkei;
    switch(index) {
        case 0:
            enkei = grTengan::create(4, "", "grTenganSky");
            break;
        case 1:
            enkei = grTengan::create(5, "", "grTenganStar");
            break;
        default:
            enkei = NULL;
    }
    if (enkei) {
        addGround(enkei);
        enkei->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        enkei->setStageData(m_stageData);
    }
}

void stTengan::createObjBg(int index) {
    grTenganBg *bg;
    switch(index) {
        case 2:
            bg = grTenganBg::create(0, "", "grTenganMainBg");
            break;
        default:
            bg = NULL;
    }
    if (bg) {
        addGround(bg);
        bg->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        bg->setStageData(m_stageData);
        bg->setPosDialgaWork(&posDialga);
        bg->setPosAshibaWork(posAshibaWork);
    }
}

void grTenganBg::setPosDialgaWork(Vec3f* pos) {
    posDialgaWork = pos;
}

void grTenganBg::setPosAshibaWork(Vec3f* pos) {
    posAshibaWork = pos;
}

void stTengan::createObjDialga(int index) {
    grMadein *legend;
    switch(index) {
        case 3:
            legend = grMadein::create(3, "dialga", "dialga",Heaps::StageInstance);
            break;
        case 18:
            legend = grMadein::create(15, "palkia", "palkia",Heaps::StageInstance);
            break;
        case 19:
            legend = grMadein::create(16, "crecelia", "crecelia",Heaps::StageInstance);
            break;
        case 15:
            legend = grMadein::create(17, "agnome", "agnome",Heaps::StageInstance);
            break;
        case 16:
            legend = grMadein::create(18, "emrit", "emrit",Heaps::StageInstance);
            break;
        case 17:
            legend = grMadein::create(19, "yuxie", "yuxie",Heaps::StageInstance);
            break;
        default:
            legend = NULL;
    }
    if (legend) {
        addGround(legend);
        legend->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        legend->setStageData(m_stageData);
        //legend->setMotion(0);
        legend->initializeEntity();
    }
}

void stTengan::createObjAshiba(int index) {
    grTenganAshiba *ashiba;
    Vec3f* posLimitWork = NULL;
    switch(index) {
        case 4:
            ashiba = grTenganAshiba::create(1, "StgTenganAshibaA", "grTenganAshibaA");
            posLimitWork = &posAshibaWork[0];
            break;
        case 5:
            ashiba = grTenganAshiba::create(2, "StgTenganAshibaB", "grTenganAshibaB");
            posLimitWork = &posAshibaWork[2];
            break;
        default:
            ashiba = NULL;
    }
    if (ashiba) {
        addGround(ashiba);
        ashiba->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ashiba->setStageData(m_stageData);
        ashiba->setPosLimitWork(posLimitWork);
    }
}

void grTenganAshiba::setPosLimitWork(Vec3f* pos) {
    m_posLimitWork = pos;
}

void stTengan::createObjFloor(int index) {
    grTenganFloor *floor;
    u8* stateWork;
    u8 type;
    switch(index) {
        case 6:
            floor = grTenganFloor::create(6, "StgTenganBrkYukaL", "grTenganFloorL");
            stateWork = &m_stateFloor[0];
            type = 0;
            break;
        case 7:
            floor = grTenganFloor::create(8, "StgTenganBrkYukaC", "grTenganFloorC");
            stateWork = &m_stateFloor[1];
            type = 1;
            break;
        case 8:
            floor = grTenganFloor::create(7, "StgTenganBrkYukaR", "grTenganFloorR");
            stateWork = &m_stateFloor[2];
            type = 2;
            break;
        case 9:
            floor = grTenganFloor::create(9, "StgTenganBrkYukaCL", "grTenganFloorCL");
            stateWork = &m_stateFloor[0];
            type = 3;
            break;
        case 10:
            floor = grTenganFloor::create(10, "StgTenganBrkYukaCR", "grTenganFloorCR");
            stateWork = &m_stateFloor[0];
            type = 4;
            break;
        default:
            floor = NULL;
            stateWork = NULL;
    }
    if (floor) {
        addGround(floor);
        floor->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        floor->setStageData(m_stageData);
        floor->setFrameWork(&m_rebuildTimer);
        floor->setStateWork(stateWork);
        floor->setType(type);
    }
}

void grTenganFloor::setFrameWork(float* frameWork)
{
    this->m_frameWork = frameWork;
}

void grTenganFloor::setStateWork(u8* stateWork)
{
    this->m_stateWork = stateWork;
}

void grTenganFloor::setType(u8 type)
{
    this->m_type = type;
}

void stTengan::update(float deltaFrame) {
    updateEvent(deltaFrame);
}

bool stTengan::eventRebuildStageUpdate() {
    float fVar1 = eventRebuildStage.m_framesLeft;
    m_rebuildTimer = fVar1;
    if (fVar1 < 0.0f) {
        m_rebuildTimer = 0.0f;
    }
    switch (eventRebuildStage.getPhase()) {
        case 0:
            if (m_stateFloor[1] == 1) {
                if (static_cast<grTenganFloor*>(getGround(7))->m_state == 3) {
                    static_cast<grMadein*>(getGround(27))->endEntity();
                    static_cast<grMadein*>(getGround(27))->setEnableCollisionStatus(false);
                    eventRebuildStage.setPhase(1);
                }
            } else {
                eventRebuildStage.setPhase(1);
            }
            break;
        case 1:
            if (m_rebuildTimer == 0.0f and eventRebuildStage.isReadyEnd() == true) {
                return 1;
            }
            break;
    }
    return 0;
}

bool stTengan::eventSlowUpdate(float deltaFrame) {
    switch (eventSlow.getPhase()) {
    case 0: {
        stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
        if (params == NULL) {
            return true;
        }

        // The copy-EFB amount rises and falls over the duration of the slow event.
        unk200 = 0.0f;
        gfCopyEFBMgr* copyEFB = gfCopyEFBMgr::getInstance();
        copyEFB->m_104 = true;
        copyEFB->m_108 = static_cast<int>(unk200);

        float rate12 = params->event_d_rate_slow_1_2 * 100.0f;
        float rate13 = params->event_d_rate_slow_1_3 * 100.0f;
        float rate14 = params->event_d_rate_slow_1_4 * 100.0f;
        int choice = randi(static_cast<int>((rate12 + rate13) + rate14) + 1);
        int event = 0;
        int cumulative = 0;
        while (true) {
            if (event == 0) {
                cumulative += static_cast<int>(rate12);
            } else if (event == 1) {
                cumulative += static_cast<int>(rate13);
            } else if (event == 2) {
                cumulative += static_cast<int>(rate14);
            } else {
                cumulative = choice;
            }
            if (cumulative >= choice) {
                break;
            }
            ++event;
        }

        if (event == 0 || event == 1) {
            m_slow = static_cast<char>(gfSlowManager::requestSlow(2) >> 24);
        } else if (event == 2) {
            m_slow = static_cast<char>(gfSlowManager::requestSlow(4) >> 24);
        }

        eventSlow.setPhase(1);
        playSeBasic(snd_se_stage_Tengan_07, 0.0f);
        GXColor color = {255, 255, 255, 128};
        g_efScreen->requestFlash(20.0f, 0, 128, 2, &color);
        break;
    }
    case 1:
        if (eventSlow.isReadyEnd()) {
            if (unk200 == 0.0f) {
                playSeBasic(snd_se_stage_Tengan_08, 0.0f);
                GXColor color = {255, 255, 255, 128};
                g_efScreen->requestFlash(20.0f, 0, 128, 2, &color);
            }
            unk200 -= 10.0f;
            if (unk200 < 0.0f) {
                unk200 = 0.0f;
            }
            if (unk200 == 0.0f) {
                if (m_slow != -1) {
                    u8 request = static_cast<u8>(m_slow);
                    gfSlowManager::removeRequest(request);
                }
                gfCopyEFBMgr* copyEFB = gfCopyEFBMgr::getInstance();
                copyEFB->m_104 = false;
                copyEFB->m_108 = static_cast<int>(unk200);
                return true;
            }
        } else {
            unk200 += 10.0f;
            if (unk200 >= 200.0f) {
                unk200 = 200.0f;
            }
        }
        gfCopyEFBMgr::getInstance()->m_108 = static_cast<int>(unk200);
        break;
    }
    return false;
}

bool stTengan::eventPokemonUpdate(float deltaFrame) {
    int groundIndex = 0;
    switch (m_substage) {
    case 0:
        groundIndex = 3;
        break;
    case 1:
        groundIndex = 18;
        break;
    case 2:
        groundIndex = 19;
        break;
    }

    switch (event1.getPhase()) {
    case 0:
        if (event1.isReadyEnd()) {
            g_ecMgr->setDrawPrio(1);
            u32 effect = g_ecMgr->setEffect(ef_ptc_stg_tengan_syutugen);
            g_ecMgr->setDrawPrio(-1);
            g_ecMgr->setPos(effect, &posDialga);
            playSeBasic(snd_se_stage_Tengan_Entry_01, 0.0f);
            event1.setPhase(1);
            event1.m_manualFramesLeft = 0.0f;
        }
        break;
    case 1:
        event1.m_manualFramesLeft += deltaFrame;
        if (event1.m_manualFramesLeft >= 70.0f) {
            playSeBasic(snd_se_stage_Tengan_Entry_02, 0.0f);
            event1.setPhase(2);
        }
        break;
    case 2:
        event1.m_manualFramesLeft += deltaFrame;
        if (event1.m_manualFramesLeft >= 140.0f) {
            static_cast<grMadein*>(getGround(groundIndex))->setMotion(3);
            static_cast<grMadein*>(getGround(groundIndex))->startEntity();
            static_cast<grMadein*>(getGround(groundIndex))->setPos(&posDialga);
            if (m_substage == 1) {
                g_ecMgr->setDrawPrio(1);
                u32 leftEye = g_ecMgr->setEffect(ef_ptc_stg_tengan_eyeglow);
                g_ecMgr->setParent(leftEye, getGround(groundIndex)->m_sceneModels[0],
                                   "StgTenganPalkia_LFlashEyeN", false);
                u32 rightEye = g_ecMgr->setEffect(ef_ptc_stg_tengan_eyeglow);
                g_ecMgr->setParent(rightEye, getGround(groundIndex)->m_sceneModels[0],
                                   "StgTenganPalkia_RFlashEyeN", false);
                g_ecMgr->setDrawPrio(-1);
            } else if (m_substage == 0) {
                g_ecMgr->setDrawPrio(1);
                u32 leftEye = g_ecMgr->setEffect(ef_ptc_stg_tengan_eyeglow);
                g_ecMgr->setParent(leftEye, getGround(groundIndex)->m_sceneModels[0],
                                   "StgTenganDialga_LFlashEyeN", false);
                u32 rightEye = g_ecMgr->setEffect(ef_ptc_stg_tengan_eyeglow);
                g_ecMgr->setParent(rightEye, getGround(groundIndex)->m_sceneModels[0],
                                   "StgTenganDialga_RFlashEyeN", false);
                g_ecMgr->setDrawPrio(-1);
            }
            event1.setPhase(3);
            unkeac = 0;
        }
        break;
    case 3:
        if (groundIndex != 19) {
            SndID stepSound = snd_se_stage_Tengan_step_01;
            bool trigger = false;
            switch (unkeac) {
            case 0:
                trigger = static_cast<grMadein*>(getGround(groundIndex))->isFrameEndOffset(180.0f);
                break;
            case 1:
                stepSound = snd_se_stage_Tengan_step_02;
                trigger = static_cast<grMadein*>(getGround(groundIndex))->isFrameEndOffset(120.0f);
                break;
            case 2:
                trigger = static_cast<grMadein*>(getGround(groundIndex))->isFrameEndOffset(60.0f);
                break;
            }
            if (trigger) {
                Vec3f offset;
                offset.m_x = 0.0f;
                offset.m_y = 0.0f;
                offset.m_z = 0.0f;
                cmReqQuake(cmQuake::Amplitude_S, &offset);
                ++unkeac;
                playSeBasic(stepSound, 0.0f);
            }
        }
        if (static_cast<grMadein*>(getGround(groundIndex))->isEndEntity()) {
            static_cast<grMadein*>(getGround(groundIndex))->setMotion(0);
            static_cast<grMadein*>(getGround(groundIndex))->startEntityAutoLoop();
            event1.setPhase(10);
            eventLegendDisappear.end();
            eventLegendDisappear.start();
            event2.end();
            event2.start();
        }
        break;
    case 10:
        if (eventLegendDisappear.isReadyEnd() &&
            static_cast<grMadein*>(getGround(groundIndex))->isEndEntity() &&
            !eventAura.isEvent() && !eventRandomCall.isEvent() && !eventSonicWaveCall.isEvent()) {
            static_cast<grMadein*>(getGround(groundIndex))->setMotion(4);
            static_cast<grMadein*>(getGround(groundIndex))->startEntity();
            event1.setPhase(11);
            event2.end();
            m_legendEventActive = 0;
        }
        break;
    case 11:
        if (static_cast<grMadein*>(getGround(groundIndex))->isEndEntity()) {
            playSeBasic(snd_se_stage_Tengan_Leave_01, 0.0f);
            g_ecMgr->setDrawPrio(1);
            u32 effect = g_ecMgr->setEffect(ef_ptc_stg_tengan_syoushitu);
            g_ecMgr->setDrawPrio(-1);
            g_ecMgr->setPos(effect, &posDialga);
            event1.setPhase(12);
            event1.m_manualFramesLeft = 0.0f;
        }
        break;
    case 12:
        event1.m_manualFramesLeft += deltaFrame;
        if (event1.m_manualFramesLeft >= 90.0f) {
            playSeBasic(snd_se_stage_Tengan_Leave_02, 0.0f);
            static_cast<grMadein*>(getGround(groundIndex))->endEntity();
            event1.setPhase(13);
        }
        break;
    case 13:
        event2.end();
        eventLegendDisappear.end();
        event1.end();
        event1.start();
        break;
    }
    return false;
}

bool stTengan::eventDropStageUpdate() {
    switch (eventDropStage.getPhase()) {
        case 0: {
            m_dropSoundHandle = playSeBasic(snd_se_stage_Tengan_06, 0.0f);
            u32 sound = randi(2);
            if (sound >= 1) {
                sound = 1;
            }
            playSeBasic(static_cast<SndID>(snd_se_stage_Tengan_01 + sound), 0.0f);
            eventDropStage.setPhase(1);
            break;
        }
        case 1:
            if (eventDropStage.isReadyEnd() == true) {
                float choice = randf();
                u32 floor;
                if (choice < 1.0f / 3.0f) {
                    floor = 0;
                } else if (choice < 2.0f / 3.0f) {
                    floor = 1;
                } else {
                    floor = 2;
                }
                // Do not drop an already broken floor or restart its rebuild event.
                if (m_stateFloor[floor] != 1 && eventRebuildStage.start() == true) {
                    m_stateFloor[floor] = 1;
                    m_rebuildTimer = eventRebuildStage.m_framesLeft;
                    if (floor == 1) {
                        static_cast<grMadein*>(getGround(27))->startEntity();
                        getGround(27)->setEnableCollisionStatus(true);
                    }
                    return true;
                }
            }
            break;
    }
    return false;
}


// HYPOTHESIS: grounds 33-36 are the Sonic Wave visual elements; their exact
// resource roles are not named by the native call sites.
bool stTengan::eventSonicWaveCallUpdate(float deltaFrame) {
    if (eventSonicWaveCall.getPhase() == 0) {
        unkeb8 = 0; unkeb9 = 0; unkeba = 0;
        eventSonicWaveCall.setPhase(eventSonicWaveCall.getPhase() + 1);
        unkebc = posDialga.m_x; unkec0 = posDialga.m_y + 50.0f;
        unkec4 = posDialga.m_z;
        int choice = randi(8);
        if (choice >= 8) choice = 7;
        unkec8 = static_cast<u8>(choice + 3);
        unkecc = 0.0f; unked0 = 0.0f; unked4 = 0.0f; unked8 = 0.0f;
    }
    unked8 += deltaFrame;
    float cycle = unked8 / 60.0f;
    if (cycle > 1.0f) { unked8 -= 60.0f; cycle -= 1.0f; }
    if (cycle < 0.0f) cycle = 0.0f;
    if (cycle > 1.0f) cycle = 1.0f;
    s16 angle = static_cast<s16>(65535.0f * cycle);
    float sinValue = nw4r::math::SinFIdx(static_cast<float>(angle) * (1.0f / 256.0f));
    float cosValue = nw4r::math::CosFIdx(static_cast<float>(angle) * (1.0f / 256.0f));
    unkecc = 20.0f + 5.0f * sinValue;
    unked0 = 40.0f * cosValue;
    unked4 = 2.5f * cosValue;
    Vec3f rotation;
    rotation.m_x = unkecc; rotation.m_y = unked0; rotation.m_z = unked4;
    static_cast<grMadein*>(getGround(33))->setRot(&rotation);
    switch (unkeb9) {
    case 0:
        if (unkeb8 >= 2) {
            Vec3f scale; scale.m_x = 1.0f; scale.m_y = 1.0f; scale.m_z = 1.0f;
            Vec3f position; position.m_x = unkebc; position.m_y = unkec0; position.m_z = unkec4;
            static_cast<grMadein*>(getGround(33))->setPos(&position); static_cast<grMadein*>(getGround(33))->setScale(&scale);
            static_cast<grMadein*>(getGround(33))->setMotion(0);
            static_cast<grMadein*>(getGround(33))->startEntity(); ++unkeb9;
        }
        break;
    case 1:
        if (static_cast<grMadein*>(getGround(33))->isEndEntity()) {
            static_cast<grMadein*>(getGround(33))->setMotion(1);
            static_cast<grMadein*>(getGround(33))->startEntityAutoLoop(); ++unkeb9;
        }
        break;
    case 2:
        if (unkeba == 2) {
            static_cast<grMadein*>(getGround(33))->setMotion(2);
            static_cast<grMadein*>(getGround(33))->startEntity(); ++unkeb9;
        }
        break;
    case 3:
        if (static_cast<grMadein*>(getGround(33))->isEndEntity()) {
            static_cast<grMadein*>(getGround(33))->endEntity(); ++unkeb9;
        }
        break;
    }
    switch (unkeba) {
    case 0:
        if (unkeb9 >= 2) {
            Vec3f scale; scale.m_x = 0.0f; scale.m_y = 0.0f; scale.m_z = 0.0f;
            unked0 = -40.0f + (10.0f * randf()) * -78.0f;
            static_cast<grMadein*>(getGround(34))->setScale(&scale); static_cast<grMadein*>(getGround(34))->setRot(&rotation);
            Vec3f position; position.m_x = unkebc; position.m_y = unkec0; position.m_z = unkec4;
            static_cast<grMadein*>(getGround(34))->setPos(&position);
            static_cast<grMadein*>(getGround(34))->setMotion(0);
            static_cast<grMadein*>(getGround(34))->startEntity();
            static_cast<grMadein*>(getGround(35))->setRot(&rotation); static_cast<grMadein*>(getGround(35))->setPos(&position);
            static_cast<grMadein*>(getGround(35))->setMotion(0);
            static_cast<grMadein*>(getGround(35))->startEntity();
            static_cast<grMadein*>(getGround(36))->setRot(&rotation);
            playSeBasic(snd_se_stage_Tengan_cres_sonic, 0.0f); ++unkeba;
        }
        break;
    case 1:
        // HYPOTHESIS: native samples the Palkia jaw node for this visual.
        {
            Vec3f nodePosition;
            static_cast<grMadein*>(getGround(35))->getNodePosition(&nodePosition, 0, "shotPosition");
            Vec3f left; left.m_x = nodePosition.m_x - 7.5f;
            left.m_y = nodePosition.m_y - 5.0f; left.m_z = nodePosition.m_z + 5.0f;
            static_cast<grMadein*>(getGround(36))->setPos(&left); static_cast<grMadein*>(getGround(36))->startEntity();
            if (static_cast<grMadein*>(getGround(33))->isEndEntity()) {
                static_cast<grMadein*>(getGround(33))->endEntity();
                static_cast<grMadein*>(getGround(34))->endEntity();
                static_cast<grMadein*>(getGround(35))->endEntity();
                static_cast<grMadein*>(getGround(36))->endEntity();
                if (unkec8 == 0) ++unkeba;
                else { --unkec8; unkeba = 0; }
            }
        }
        break;
    }
    switch (unkeb8) {
    case 0:
        if (static_cast<grMadein*>(getGround(19))->isEndEntity()) {
            static_cast<grMadein*>(getGround(19))->setMotion(6);
            static_cast<grMadein*>(getGround(19))->startEntity(); ++unkeb8;
            playSeBasic(snd_se_stage_Tengan_cres_wing, 0.0f);
        }
        break;
    case 1:
        if (static_cast<grMadein*>(getGround(19))->isEndEntity()) {
            static_cast<grMadein*>(getGround(19))->setMotion(7);
            static_cast<grMadein*>(getGround(19))->startEntityAutoLoop();
            zoomOutCamera(300.0f, 340.0f); ++unkeb8;
        }
        break;
    case 2:
        if (unkeba == 2 && unkeb9 == 4) {
            static_cast<grMadein*>(getGround(19))->setMotion(8);
            static_cast<grMadein*>(getGround(19))->startEntity(); ++unkeb8;
            zoomInCamera();
        }
        break;
    case 3:
        if (static_cast<grMadein*>(getGround(19))->isEndEntity()) {
            eventSonicWaveCall.end(); return true;
        }
        break;
    }
    return false;
}

void stTengan::setEventDialga(float deltaFrame) {
    (void)deltaFrame;
    stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
    if (params == NULL) return;
    const float scale = 100.0f;
    float weights[5] = {params->event_d_rate_rot_screen, params->event_d_rate_quake,
        params->event_d_rate_laser_y + params->event_d_rate_laser_x,
        params->event_d_rate_slow, params->event_d_rate_aura};
    float total = params->event_d_rate_rot_screen * scale + params->event_d_rate_quake * scale +
        params->event_d_rate_laser_y * scale + params->event_d_rate_laser_x * scale +
        params->event_d_rate_slow * scale + params->event_d_rate_aura * scale;
    int choice = randi(static_cast<int>(total) + 1);
    int selected = 0, cumulative = 0;
    while (selected < 5) {
        cumulative += static_cast<int>(weights[selected] * scale);
        if (cumulative >= choice) break;
        ++selected;
    }
    bool started = false;
    if (selected != m_lastCresseliaEvent) {
        switch (selected) {
        case 0: started = eventCameraRoll.start(); break;
        case 1: {
            int broken = (m_stateFloor[0] == 1) + (m_stateFloor[1] == 1) + (m_stateFloor[2] == 1);
            if (!eventDropStage.isEvent() && !eventRebuildStage.isEvent() && broken < 3) {
                started = eventQuake.start();
                eventDropStage.start();
            }
            break;
        }
        case 2:
            started = eventQuake.start();
            if (started) {
                if (!eventLaser.start()) { eventQuake.end(); started = false; }
                else unkea8 = 1;
            }
            break;
        case 3: started = eventSlow.start(); break;
        case 4: started = eventAura.start(); break;
        }
    }
    if (!started) return;
    m_lastCresseliaEvent = selected; m_legendEventActive = 1;
    static_cast<grMadein*>(getGround(3))->setMotion(1);
    static_cast<grMadein*>(getGround(3))->startEntity();
    event2.end(); event2.start();
    m_pendingLegendSound = snd_se_stage_Tengan_03; m_legendSoundDelayFrames = 45.0f;
    u32 effect = g_ecMgr->setEffect(static_cast<EfID>(0x0104004C));
    g_ecMgr->setParent(effect, getGround(3)->m_sceneModels[0], "StgTenganDialga_jaw", false);
}

void stTengan::setEventValkia(float deltaFrame) {
    (void)deltaFrame;
    stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
    if (params == NULL) return;
    const float scale = 100.0f;
    float weights[6] = {params->event_p_rate_rot_screen, params->event_p_rate_quake,
        params->event_p_rate_laser_y + params->event_p_rate_laser_x,
        params->event_p_rate_gravity_half, params->event_p_rate_reverse_y,
        params->event_p_rate_reverse_x};
    float total = params->event_p_rate_rot_screen * scale + params->event_p_rate_quake * scale +
        params->event_p_rate_laser_y * scale + params->event_p_rate_laser_x * scale +
        params->event_p_rate_gravity_half * scale + params->event_p_rate_reverse_y * scale +
        params->event_p_rate_reverse_x * scale;
    int choice = randi(static_cast<int>(total) + 1);
    int selected = 0, cumulative = 0;
    while (selected < 6) {
        cumulative += static_cast<int>(weights[selected] * scale);
        if (cumulative >= choice) break;
        ++selected;
    }
    bool started = false;
    if (selected != m_lastCresseliaEvent) {
        switch (selected) {
        case 0: started = eventCameraRoll.start(); break;
        case 1: {
            int broken = (m_stateFloor[0] == 1) + (m_stateFloor[1] == 1) + (m_stateFloor[2] == 1);
            if (!eventDropStage.isEvent() && !eventRebuildStage.isEvent() && broken < 3) {
                started = eventQuake.start();
                if (started) eventDropStage.start();
            }
            break;
        }
        case 2:
            started = eventQuake.start();
            if (started) {
                if (!eventLaser.start()) { eventQuake.end(); started = false; }
                else unkea8 = 1;
            }
            break;
        case 3: started = eventGravityHalf.start(); break;
        case 4: started = eventUpDownReverse.start(); break;
        case 5: started = eventLeftRightReverse.start(); break;
        }
    }
    if (!started) return;
    m_lastCresseliaEvent = selected; m_legendEventActive = 1;
    static_cast<grMadein*>(getGround(18))->setMotion(1);
    static_cast<grMadein*>(getGround(18))->startEntity();
    event2.end(); event2.start();
    m_pendingLegendSound = snd_se_stage_Tengan_05; m_legendSoundDelayFrames = 60.0f;
    u32 effect = g_ecMgr->setEffect(static_cast<EfID>(0x0104004C));
    g_ecMgr->setParent(effect, getGround(18)->m_sceneModels[0], "StgTenganPalkia_Jaw", false);
}

void stTengan::setEventCrecelia() {
    stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
    if (params == NULL) {
        return;
    }
    float weightScale = 100.0f;
    int event = 0;
    int choice = randi(static_cast<int>(params->event_c_rate_boomerang * weightScale +
                                       params->event_c_rate_sonicwave * weightScale) + 1);
    int cumulative = 0;
    bool selected = false;
    do {
        switch (event) {
            case 0:
                cumulative += static_cast<int>(params->event_c_rate_boomerang * weightScale);
                break;
            case 1:
                cumulative += static_cast<int>(params->event_c_rate_sonicwave * weightScale);
                break;
            case 2:
                cumulative = choice;
                break;
        }
        if (cumulative >= choice) {
            selected = true;
        }
        if (cumulative < choice) {
            ++event;
        }
    } while (selected != true);
    // A repeated choice does not start another event.
    bool started = false;
    if (m_lastCresseliaEvent != event) {
        if (event != 1) {
            started = eventBoomerang.start();
        } else {
            started = eventSonicWaveCall.start();
        }
    }
    if (started == true) {
        m_lastCresseliaEvent = event;
        m_legendEventActive = 1;
        static_cast<grMadein*>(getGround(19))->setMotion(1);
        static_cast<grMadein*>(getGround(19))->startEntity();
        event2.end();
        event2.start();
        m_pendingLegendSound = snd_se_stage_Tengan_cres_vc;
        m_legendSoundDelayFrames = 100.0f;
    }
}

bool stTengan::eventUpDownReversUpdate(float deltaFrame) {
    if (m_stageData == NULL) {
        return true;
    }
    switch (eventUpDownReverse.getPhase()) {
        case 0:
            m_reverseTargetDegrees = 180.0f;
            m_reverseDegrees = 0.0f;
            m_reverseSpeed = 0.1f;
            eventUpDownReverse.setPhase(1);
            if (randi(10) > 5) {
                m_reverseDirection = 1.0f;
            } else {
                m_reverseDirection = -1.0f;
            }
            playSeBasic(snd_se_stage_Tengan_10, 0.0f);
            break;
        case 1: {
            gfCameraManager* cameras = gfCameraManager::getManager();
            if (cameras != NULL) {
                m_reverseSpeed *= 1.1f;
                if (m_reverseSpeed >= 8.0f) {
                    m_reverseSpeed = 8.0f;
                }
                m_reverseDegrees += m_reverseSpeed * deltaFrame;
                if (m_reverseDegrees >= m_reverseTargetDegrees) {
                    m_reverseDegrees = m_reverseTargetDegrees;
                }
                cameras->m_cameras[0].m_rot.m_z =
                    (m_rollDegrees * m_rollDirection + m_reverseDegrees * m_reverseDirection) * 0.017453292f;
                cameras->m_cameras[0].unkFA.m_mask |= 0x40;
                if (m_reverseDegrees == m_reverseTargetDegrees) {
                    eventUpDownReverse.setPhase(2);
                    m_reverseSpeed = 0.1f;
                    Vec3f offset;
                    offset.m_x = 0.0f;
                    offset.m_y = 0.0f;
                    offset.m_z = 0.0f;
                    cmReqQuake(cmQuake::Amplitude_S, &offset);
                    playSeBasic(snd_se_stage_Tengan_roll_finish, 0.0f);
                }
            }
            break;
        }
        case 2:
            cmRemoveQuake(1);
            eventUpDownReverse.setPhase(3);
            break;
        case 3:
            if (eventUpDownReverse.isReadyEnd() == true) {
                playSeBasic(snd_se_stage_Tengan_10, 0.0f);
                eventUpDownReverse.setPhase(4);
            }
            break;
        case 4: {
            gfCameraManager* cameras = gfCameraManager::getManager();
            if (cameras != NULL) {
                m_reverseSpeed *= 1.1f;
                if (m_reverseSpeed >= 8.0f) {
                    m_reverseSpeed = 8.0f;
                }
                m_reverseDegrees -= m_reverseSpeed * deltaFrame;
                if (m_reverseDegrees < 0.0f) {
                    m_reverseDegrees = 0.0f;
                }
                cameras->m_cameras[0].m_rot.m_z =
                    (m_rollDegrees * m_rollDirection + m_reverseDegrees * m_reverseDirection) * 0.017453292f;
                cameras->m_cameras[0].unkFA.m_mask |= 0x40;
                if (m_reverseDegrees == 0.0f) {
                    Vec3f offset;
                    offset.m_x = 0.0f;
                    offset.m_y = 0.0f;
                    offset.m_z = 0.0f;
                    cmReqQuake(cmQuake::Amplitude_S, &offset);
                    eventUpDownReverse.setPhase(5);
                    playSeBasic(snd_se_stage_Tengan_roll_finish, 0.0f);
                }
            }
            break;
        }
        case 5:
            cmRemoveQuake(1);
            eventUpDownReverse.end();
            return true;
    }
    return false;
}

bool stTengan::eventCameraRollUpdate(float deltaFrame) {
    stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
    if (params == NULL) {
        return true;
    }
    switch (eventCameraRoll.getPhase()) {
        case 0: {
            float random = randf();
            float max = params->event_angle_rot_screen_max;
            float min = params->event_angle_rot_screen_min;
            float angle = (max - min) * random;
            m_rollDegrees = 0.0f;
            m_rollSpeed = 0.1f;
            m_rollTargetDegrees = min + angle;
            eventCameraRoll.setPhase(1);
            if (randi(10) > 5) {
                m_rollDirection = 1.0f;
            } else {
                m_rollDirection = -1.0f;
            }
            playSeBasic(snd_se_stage_Tengan_09, 0.0f);
            break;
        }
        case 1: {
            gfCameraManager* cameras = gfCameraManager::getManager();
            if (cameras != NULL) {
                m_rollSpeed *= 1.1f;
                if (m_rollSpeed >= 8.0f) {
                    m_rollSpeed = 8.0f;
                }
                m_rollDegrees += m_rollSpeed * deltaFrame;
                if (m_rollDegrees >= m_rollTargetDegrees) {
                    m_rollDegrees = m_rollTargetDegrees;
                }
                cameras->m_cameras[0].m_rot.m_z =
                    (m_rollDegrees * m_rollDirection + m_reverseDegrees * m_reverseDirection) * 0.017453292f;
                cameras->m_cameras[0].unkFA.m_mask |= 0x40;
                if (m_rollDegrees == m_rollTargetDegrees) {
                    eventCameraRoll.setPhase(2);
                    m_rollSpeed = 0.1f;
                    Vec3f offset;
                    offset.m_x = 0.0f;
                    offset.m_y = 0.0f;
                    offset.m_z = 0.0f;
                    cmReqQuake(cmQuake::Amplitude_S, &offset);
                    playSeBasic(snd_se_stage_Tengan_roll_finish, 0.0f);
                }
            }
            break;
        }
        case 2:
            cmRemoveQuake(1);
            eventCameraRoll.setPhase(3);
            break;
        case 3: {
            gfCameraManager* cameras = gfCameraManager::getManager();
            if (cameras != NULL) {
                m_rollSpeed *= 1.1f;
                if (m_rollSpeed >= params->event_angle_rot_return) {
                    m_rollSpeed = params->event_angle_rot_return;
                }
                m_rollDegrees -= m_rollSpeed * deltaFrame;
                if (m_rollDegrees < 0.0f) {
                    m_rollDegrees = 0.0f;
                }
                cameras->m_cameras[0].m_rot.m_z =
                    (m_rollDegrees * m_rollDirection + m_reverseDegrees * m_reverseDirection) * 0.017453292f;
                cameras->m_cameras[0].unkFA.m_mask |= 0x40;
                if (m_rollDegrees == 0.0f) {
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

bool stTengan::eventRandomCallUpdate() {
    switch (eventRandomCall.getPhase()) {
        case 0:
            if (static_cast<grMadein*>(getGround(19))->isEndEntity()) {
                m_randomCallEffectHandle = g_ecMgr->setEffect(ef_ptc_stg_tengan_crecelia_kona);
                static_cast<grMadein*>(getGround(19))->setMotion(5);
                static_cast<grMadein*>(getGround(19))->startEntity();
                static_cast<grMadein*>(getGround(32))->setMotion(0);
                static_cast<grMadein*>(getGround(32))->startEntity();
                static_cast<grMadein*>(getGround(1))->endEntity();
                eventRandomCall.setPhase(eventRandomCall.getPhase() + 1);
                playSeBasic(snd_se_stage_Tengan_cres_up, 0.0f);
            }
            break;
        case 1:
            if (static_cast<grMadein*>(getGround(32))->isEndEntity()) {
                static_cast<grMadein*>(getGround(32))->setMotion(1);
                static_cast<grMadein*>(getGround(32))->startEntity();
                eventRandomCall.setPhase(eventRandomCall.getPhase() + 1);
            }
            break;
        case 2:
            if (static_cast<grMadein*>(getGround(32))->isEndEntity()) {
                static_cast<grMadein*>(getGround(32))->setMotion(2);
                static_cast<grMadein*>(getGround(32))->startEntity();
                eventRandomCall.setPhase(eventRandomCall.getPhase() + 1);
            }
            break;
        case 3:
            if (static_cast<grMadein*>(getGround(32))->isEndEntity()) {
                static_cast<grMadein*>(getGround(32))->endEntity();
                static_cast<grMadein*>(getGround(1))->startEntity();
                eventRandomCall.end();
                g_ecMgr->endEffect(m_randomCallEffectHandle);
                return true;
            }
            break;
    }
    return false;
}

bool stTengan::eventAuraUpdate() {
    switch (eventAura.getPhase()) {
        case 0:
            if (static_cast<grMadein*>(getGround(3))->isEndEntity()) {
                static_cast<grMadein*>(getGround(3))->setMotion(5);
                static_cast<grMadein*>(getGround(3))->startEntity();
                eventAura.setPhase(1);
                m_auraSoundHandle = -1;
            }
            break;
        case 1:
            if (m_auraSoundHandle == -1) {
                if (getGround(3)->getMotionFrame(0) >= 48.0f) {
                    m_auraSoundHandle = playSeBasic(snd_se_stage_Tengan_Aura_01, 0.0f);
                }
            }
            if (static_cast<grMadein*>(getGround(3))->isEndEntity()) {
                g_ecMgr->setDrawPrio(1);
                u32 effect = g_ecMgr->setEffect(ef_ptc_stg_tengan_aura);
                g_ecMgr->setDrawPrio(-1);
                g_ecMgr->setParent(effect, getGround(3)->m_sceneModels[0],
                                   "StgTenganDialga_origin", false);
                static_cast<grMadein*>(getGround(3))->setMotion(6);
                static_cast<grMadein*>(getGround(3))->startEntityLoop(2);
                static_cast<grMadein*>(getGround(26))->startEntity();
                eventAura.setPhase(2);
                playSeBasic(snd_se_stage_Tengan_Aura_02, 0.0f);
            }
            break;
        case 2:
            if (static_cast<grMadein*>(getGround(3))->isEndEntity()) {
                static_cast<grMadein*>(getGround(3))->setMotion(7);
                static_cast<grMadein*>(getGround(3))->startEntity();
                static_cast<grMadein*>(getGround(26))->endEntity();
                eventAura.setPhase(3);
            }
            break;
        case 3:
            if (static_cast<grMadein*>(getGround(3))->isEndEntity()) {
                return true;
            }
            break;
    }
    return false;
}

bool stTengan::eventBoomerangUpdate() {
    switch (eventBoomerang.getPhase()) {
        case 0: {
            u32 motion = randi(3);
            if (motion >= 2) {
                motion = 2;
            }
            m_boomerangMotion = motion;
            static_cast<grMadein*>(getGround(31))->setMotion(m_boomerangMotion);
            static_cast<grMadein*>(getGround(31))->startEntity();
            zoomOutCamera(300.0f, 340.0f);
            m_boomerangSoundHandle = playSeBasic(snd_se_stage_Tengan_cres_boomerang, 0.0f);
            eventBoomerang.setPhase(1);
            m_boomerangEffectHandle = g_ecMgr->setEffect(ef_ptc_stg_tengan_crecelia_boomeran);
            g_ecMgr->setParent(m_boomerangEffectHandle, getGround(31)->m_sceneModels[0],
                               "StgTenganBoomerang1", false);
            break;
        }
        case 1:
            // Motion zero finishes its sound earlier than the other two paths.
            switch (m_boomerangMotion) {
                case 0:
                    if (getGround(31)->getMotionFrame(0) > 250.0f) {
                        stopSeBasic(m_boomerangSoundHandle, 1.0f);
                        m_boomerangSoundHandle = -1;
                        eventBoomerang.setPhase(2);
                    }
                    break;
                case 1:
                case 2:
                    if (getGround(31)->getMotionFrame(0) > 500.0f) {
                        stopSeBasic(m_boomerangSoundHandle, 1.0f);
                        m_boomerangSoundHandle = -1;
                        eventBoomerang.setPhase(2);
                    }
                    break;
            }
            break;
        case 2:
            if (static_cast<grMadein*>(getGround(31))->isEndEntity()) {
                static_cast<grMadein*>(getGround(31))->endEntity();
                g_ecMgr->endEffect(m_boomerangEffectHandle);
                eventBoomerang.end();
                zoomInCamera();
                if (m_boomerangSoundHandle != -1) {
                    stopSeBasic(m_boomerangSoundHandle, 1.0f);
                    m_boomerangSoundHandle = -1;
                }
            }
            break;
    }
    return false;
}

bool stTengan::eventGravityHalfUpdate() {
    switch (eventGravityHalf.getPhase()) {
        case 0: {
            eventGravityHalf.setPhase(1);
            setGravityHalf();
            Vec3f quakeOffset;
            quakeOffset.m_x = 0.0f;
            quakeOffset.m_y = 0.0f;
            quakeOffset.m_z = 0.0f;
            cmReqQuake(cmQuake::Amplitude_S, &quakeOffset);
            playSeBasic(snd_se_stage_Tengan_gravity_01, 0.0f);
            GXColor color = {255, 255, 255, 128};
            g_efScreen->requestFlash(20.0f, 0, 128, 2, &color);
            break;
        }
        case 1:
            if (eventGravityHalf.isReadyEnd() == true) {
                GXColor color = {255, 255, 255, 128};
                g_efScreen->requestFlash(20.0f, 0, 128, 2, &color);
                cmRemoveQuake(1);
                setGravityNormal();
                eventGravityHalf.end();
                playSeBasic(snd_se_stage_Tengan_gravity_02, 0.0f);
            }
            break;
    }
    // The handler ends its own event; the caller never receives completion.
    return false;
}

bool stTengan::eventLaserUpdate(float deltaFrame) {
    stTenganParams* params = static_cast<stTenganParams*>(m_stageData);
    if (params == NULL) return true;
    switch (eventLaser.getPhase()) {
    case 0: {
        int retry = 0;
        int choice;
        do {
            choice = randi(5);
            if (static_cast<u32>(choice) != unkeb0) break;
            ++retry;
        } while (retry < 4);
        unkeb0 = choice;
        if (choice >= 5) choice = 4;

        // HYPOTHESIS: the five node indices on ground 2 are laser origins.
        getGround(2)->getNodePosition(&posDialga, 0, choice + 8);
        grMadein* charge = static_cast<grMadein*>(getGround(14));
        charge->setPos(&posDialga);
        charge->setMotion(0);
        s32 chargeFrames;
        if (choice >= 3) {
            unke4c = 13;
            unke50 = choice - 3;
            chargeFrames = static_cast<s32>(params->unk94 / 15.0f);
        } else {
            unke4c = 12;
            unke50 = 2;
            chargeFrames = static_cast<s32>(params->unk90 / 15.0f);
        }
        unkea4 = unke50 == 0 ? 1.0f : (unke50 == 1 ? 0.0f : -1.0f);
        playSeBasic(static_cast<SndID>(unke50 == 2 ? 0x1C45 : 0x1C47), unkea4);
        charge->startEntityLoop(chargeFrames);

        if (choice < 3) {
            grMadein* warning = static_cast<grMadein*>(getGround(29));
            warning->setPos(&posDialga);
            warning->startEntity();
            Vec2f min, max;
            min.m_x = posDialga.m_x - 30.0f;
            min.m_y = posDialga.m_y;
            max.m_x = posDialga.m_x + 30.0f;
            max.m_y = posDialga.m_y - 180.0f;
            g_aiMgr->setDangerZone(&min, &max, -1, false, false);
        } else {
            Vec3f rotation; rotation.m_x = 0.0f; rotation.m_y = 0.0f; rotation.m_z = 0.0f;
            if (unke50 == 1) rotation.m_z = 180.0f;
            else if (unke50 == 2) rotation.m_z = 90.0f;
            grMadein* warning = static_cast<grMadein*>(getGround(30));
            warning->setRot(&rotation);
            warning->setPos(&posDialga);
            warning->startEntity();
            // HYPOTHESIS: these rectangle corners are the bounds passed to AI danger avoidance.
            Vec2f min, max;
            min.m_x = -300.0f;
            min.m_y = posDialga.m_y - 25.0f;
            max.m_x = 300.0f;
            max.m_y = posDialga.m_y + 15.0f;
            g_aiMgr->setDangerZone(&min, &max, -1, false, false);
        }
        eventLaser.setPhase(1);
        zoomOutCamera(16.0f, 440.0f);
        break;
    }
    case 1: {
        grMadein* charge = static_cast<grMadein*>(getGround(14));
        if (charge->isEndEntity()) {
            charge->endEntity();
            charge->setMotion(0);
            m_laserSoundHandle = playSeBasic(static_cast<SndID>(unke50 == 2 ? 0x1C46 : 0x1C48), unkea4);
            Vec3f rotation; rotation.m_x = 0.0f; rotation.m_y = 0.0f; rotation.m_z = 0.0f;
            if (unke50 == 1) rotation.m_z = 180.0f;
            else if (unke50 == 2) rotation.m_z = 90.0f;
            grMadein* target = static_cast<grMadein*>(getGround(unke4c));
            target->setRot(&rotation);
            target->setPos(&posDialga);
            target->startEntity();
            eventLaser.setPhase(2);
        }
        break;
    }
    case 2: {
        if (unke50 != 2) {
            unkea4 += unke50 == 0 ? -0.1f : 0.1f;
            if (unkea4 < -1.0f) unkea4 = -1.0f;
            if (unkea4 > 1.0f) unkea4 = 1.0f;
            setSePan(m_laserSoundHandle, unkea4);
        }
        grMadein* target = static_cast<grMadein*>(getGround(unke4c));
        if (target->isEndEntity()) {
            target->endEntity();
            target->setMotion(1);
            Vec3f rotation; rotation.m_x = 0.0f; rotation.m_y = 0.0f; rotation.m_z = 0.0f;
            target->setRot(&rotation);
            target->startEntity();
            eventLaser.setPhase(3);
        }
        break;
    }
    case 3: {
        grMadein* target = static_cast<grMadein*>(getGround(unke4c));
        if (target->isFrameEndOffset(16.0f)) {
            static_cast<grMadein*>(getGround(20))->endEntity();
            static_cast<grMadein*>(getGround(21))->endEntity();
            static_cast<grMadein*>(getGround(22))->endEntity();
            if (unke4c == 11) {
                static_cast<grMadein*>(getGround(23))->setPos(&posDialga);
                static_cast<grMadein*>(getGround(23))->startEntity();
            } else if (unke4c == 12) {
                static_cast<grMadein*>(getGround(24))->setPos(&posDialga);
                static_cast<grMadein*>(getGround(24))->startEntity();
            } else if (unke4c == 13) {
                Vec3f impact = posDialga;
                impact.m_x = -200.0f;
                static_cast<grMadein*>(getGround(25))->setPos(&impact);
                static_cast<grMadein*>(getGround(26))->setPos(&impact);
                // Native loads the Yakumono subobject from grMadein +0x14C.
                Yakumono* yakumono = *reinterpret_cast<Yakumono**>(
                    reinterpret_cast<u8*>(getGround(25)) + 0x14C);
                if (unke50 == 0) yakumono->setLr(-1.0f);
                else if (unke50 == 1) yakumono->setLr(1.0f);
                static_cast<grMadein*>(getGround(25))->startEntity();
            }
            eventLaser.setPhase(4);
        }
        break;
    }
    case 4: {
        grMadein* target = static_cast<grMadein*>(getGround(unke4c));
        if (target->isEndEntity()) {
            target->endEntity();
            zoomInCamera();
            return true;
        }
        if (target->isFrameEndOffset(32.0f)) {
            static_cast<grMadein*>(getGround(23))->endEntity();
            static_cast<grMadein*>(getGround(24))->endEntity();
            static_cast<grMadein*>(getGround(25))->endEntity();
            static_cast<grMadein*>(getGround(28))->endEntity();
            static_cast<grMadein*>(getGround(29))->endEntity();
            static_cast<grMadein*>(getGround(30))->endEntity();
            g_aiMgr->clearDangerZone(0);
        }
        break;
    }
    }
    return false;
}

void stTengan::updateEvent(float deltaFrame) {
    if (m_stageData == NULL) return;
    if (event1.isReadyEnd() && event2.isReadyEnd() && m_legendEventActive == 0) {
        if (m_substage == 0) setEventDialga(deltaFrame);
        else if (m_substage == 1) setEventValkia(deltaFrame);
        else if (m_substage == 2) setEventCrecelia();
    }
    if (m_pendingLegendSound != -1) {
        m_legendSoundDelayFrames -= deltaFrame;
        if (m_legendSoundDelayFrames < 0.0f) {
            s32 handle = snd_gen.prepareSE(m_pendingLegendSound, 0);
            if (handle != -1) {
                Vec3f position; position.m_x = 0.0f; position.m_y = 40.0f; position.m_z = 0.0f;
                snd_gen.setPos(&position);
                snd_gen.startSE(handle, 0);
            }
            m_pendingLegendSound = static_cast<SndID>(-1);
        }
    }
    event1.update(deltaFrame); event2.update(deltaFrame);
    eventLegendDisappear.update(deltaFrame); event14.update(deltaFrame);
    event15.update(deltaFrame); eventLaser.update(deltaFrame);
    eventQuake.update(deltaFrame); eventCameraRoll.update(deltaFrame);
    eventSlow.update(deltaFrame); eventDropStage.update(deltaFrame);
    eventRebuildStage.update(deltaFrame); eventAura.update(deltaFrame);
    eventUpDownReverse.update(deltaFrame); eventLeftRightReverse.update(deltaFrame);
    eventGravityHalf.update(deltaFrame); eventBoomerang.update(deltaFrame);
    eventRandomCall.update(deltaFrame); eventSonicWaveCall.update(deltaFrame);

    if (eventLaser.isEvent() && eventLaser.m_framesLeft >= 0.0f &&
        eventLaserUpdate(deltaFrame)) eventLaser.end();
    if (eventQuake.isEvent() && eventQuake.m_framesLeft >= 0.0f) {
        if (eventQuake.isReadyEnd()) {
            cmRemoveQuake(1);
            // HYPOTHESIS: this shared sound handle is reused by the quake event.
            stopSeBasic(m_dropSoundHandle, 2.0f);
            unkea8 = 0;
            eventQuake.end();
        } else {
            Vec3f offset;
            offset.m_x = 0.0f; offset.m_y = 0.0f; offset.m_z = 0.0f;
            cmReqQuake(cmQuake::Amplitude_M, &offset);
        }
    }
    if (eventCameraRoll.isEvent() && eventCameraRoll.m_framesLeft >= 0.0f &&
        eventCameraRollUpdate(deltaFrame)) eventCameraRoll.end();
    if (eventSlow.isEvent() && eventSlow.m_framesLeft >= 0.0f &&
        eventSlowUpdate(deltaFrame)) eventSlow.end();
    if (eventDropStage.isEvent() && eventDropStage.m_framesLeft >= 0.0f &&
        eventDropStageUpdate()) eventDropStage.end();
    if (eventRebuildStage.isEvent() && eventRebuildStage.m_framesLeft >= 0.0f &&
        eventRebuildStageUpdate()) eventRebuildStage.end();
    if (eventAura.isEvent() && eventAura.m_framesLeft >= 0.0f &&
        eventAuraUpdate()) eventAura.end();
    if (eventUpDownReverse.isEvent() && eventUpDownReverse.m_framesLeft >= 0.0f &&
        eventUpDownReversUpdate(deltaFrame)) eventUpDownReverse.end();
    if (eventLeftRightReverse.isEvent() && eventLeftRightReverse.m_framesLeft >= 0.0f) {
        switch (eventLeftRightReverse.getPhase()) {
        case 0: {
            cmRemoveQuake(1);
            eventLeftRightReverse.setPhase(1);
            g_gfSceneRoot->m_transformFlag.m_mask =
                (g_gfSceneRoot->m_transformFlag.m_mask & 0x00FFFFFF) | 0x01000000;
            Vec3f offset;
            offset.m_x = 0.0f; offset.m_y = 0.0f; offset.m_z = 0.0f;
            cmReqQuake(cmQuake::Amplitude_S, &offset);
            playSeBasic(static_cast<SndID>(0x1C58), 0.0f);
            break;
        }
        case 1:
            if (eventLeftRightReverse.isReadyEnd()) {
                cmRemoveQuake(1);
                g_gfSceneRoot->m_transformFlag.m_mask &= 0x00FFFFFF;
                eventLeftRightReverse.end();
                playSeBasic(static_cast<SndID>(0x1C59), 0.0f);
            }
            break;
        }
    }
    if (eventGravityHalf.isEvent() && eventGravityHalf.m_framesLeft >= 0.0f)
        eventGravityHalfUpdate();
    if (event1.isEvent() && event1.m_framesLeft >= 0.0f &&
        eventPokemonUpdate(deltaFrame)) event1.end();
    if (eventBoomerang.isEvent() && eventBoomerang.m_framesLeft >= 0.0f &&
        eventBoomerangUpdate()) eventBoomerang.end();
    if (eventRandomCall.isEvent() && eventRandomCall.m_framesLeft >= 0.0f &&
        eventRandomCallUpdate()) eventRandomCall.end();
    if (eventSonicWaveCall.isEvent() && eventSonicWaveCall.m_framesLeft >= 0.0f &&
        eventSonicWaveCallUpdate(deltaFrame)) eventSonicWaveCall.end();

    if (m_legendEventActive == 1 && !eventRandomCall.isEvent() &&
        !eventSonicWaveCall.isEvent() && !eventAura.isEvent()) {
        int groundIndex = m_substage == 0 ? 3 : (m_substage == 1 ? 18 : 19);
        grMadein* legend = static_cast<grMadein*>(getGround(groundIndex));
        if (legend->isEndEntity()) {
            legend->setMotion(0);
            legend->startEntityAutoLoop();
            m_legendEventActive = 0;
        }
    }
    if (event14.isReadyEnd() && unk210 != -1) {
        static_cast<grMadein*>(getGround(unk210))->startEntityAutoLoop();
        event14.end();
        event15.start();
    }
    if (event15.isReadyEnd() && unk210 != -1) {
        Vec3f zero;
        zero.m_x = 0.0f; zero.m_y = 0.0f; zero.m_z = 0.0f;
        switch (event15.getPhase()) {
        case 0:
            if (unk210 == 16) {
                static_cast<grMadein*>(getGround(unk210))->setMotion(unk214 == 0 ? 2 : 3);
                static_cast<grMadein*>(getGround(unk210))->startEntity();
                event15.setPhase(event15.getPhase() + 1);
            } else {
                event15.setPhase(3);
            }
            break;
        case 1:
            if (static_cast<grMadein*>(getGround(unk210))->isEndEntity()) {
                Vec3f rotation = zero;
                rotation.m_y = unk214 == 0 ? 180.0f : 0.0f;
                static_cast<grMadein*>(getGround(unk210))->setRot(&rotation);
                static_cast<grMadein*>(getGround(unk210))->setMotion(1);
                static_cast<grMadein*>(getGround(unk210))->startEntityAutoLoop();
                event15.setPhase(event15.getPhase() + 1);
            }
            break;
        case 3:
            static_cast<grMadein*>(getGround(unk210))->endEntity();
            event15.end();
            break;
        case 2: {
            grMadein* moving = static_cast<grMadein*>(getGround(unk210));
            Vec3f position = moving->getPos();
            position.m_x += unk214 == 0 ? -0.5f : 0.5f;
            moving->setPos(&position);
            if (position.m_x > 400.0f || position.m_x < -400.0f)
                event15.setPhase(event15.getPhase() + 1);
            break;
        }
        case 4:
            break;
        }
    }
}

u32 stTengan::getZoneLightSetIndex(Vec3f *position) {
    if (position == NULL) {
        return 20;
    }
    float x = position->m_x;
    float y = position->m_y;
    if (x < -78.0f) {
        return 20;
    }
    if (x > 78.0f) {
        return 20;
    }
    if (y < -60.0f) {
        return 20;
    }
    if (y > -16.0f) {
        return 20;
    }
    return 21;
}
