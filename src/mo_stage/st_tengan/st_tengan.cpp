#include <cm/cm_camera_controller.h>
#include <cm/cm_subject.h>
#include <gf/gf_archive.h>
#include <gf/gf_camera.h>
#include <gr/gr_madein.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
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

#include <st_tengan/st_tengan.h>
#include <st_tengan/st_tengan_data.h>


#include <gm/gm_global.h>
#include <ec/ec_mgr.h>
#include <OS/OSError.h>
#include <cm/cm_quake.h>
#include <ef/ef_screen.h>

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

void stTengan::updateEvent(float deltaFrame) {
    if (m_stageData) {
        event1.update(deltaFrame);
        event2.update(deltaFrame);
        eventLegendDisappear.update(deltaFrame);
        event14.update(deltaFrame);
        event15.update(deltaFrame);
        eventLaser.update(deltaFrame);
        eventQuake.update(deltaFrame);
        eventCameraRoll.update(deltaFrame);
        eventSlow.update(deltaFrame);
        eventDropStage.update(deltaFrame);
        eventRebuildStage.update(deltaFrame);
        eventAura.update(deltaFrame);
        eventUpDownReverse.update(deltaFrame);
        eventLeftRightReverse.update(deltaFrame);
        eventGravityHalf.update(deltaFrame);
        eventBoomerang.update(deltaFrame);
        eventRandomCall.update(deltaFrame);
        eventSonicWaveCall.update(deltaFrame);
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
