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

stClassInfoImpl<Stages::Tengan, stTengan> stTengan::bss_loc_14;

stTengan::stTengan() : stMelee("stTengan", Stages::Tengan) {
    
//    void* m_shrineStageData;
    m_substage = 0;
    m_slow = -1;
    unk1d8 = 0.0;
    unk1dc = 0.0;
    unk1e0 = 0.0;
    unk1e4 = 0.0;
    unk1e8 = 0.0;
    unk1ec = 0.0;
    unk1f0 = 0.0;
    unk1f4 = 0.0;
    unk1f8 = 0.0;
    unk1fc = 0.0;
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
        //ground->setType(1);
        ground->initializeEntity();
    }
    
    if (m_substage == 2) {
        createObjDialga(19);
    } else {
        ground = grMadein::create(20, "dummy", "dummy",Heaps::StageInstance);
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        //ground->setType(1);
        ground->initializeEntity();
    }
    
    ground = grMadein::create(20, "LaserAttackPointShort", "LaserAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    Vec3f offset;// = Vec3f(0.0,-100.0,0.0);
    offset.m_x = 0.0;
    offset.m_y = -100.0;
    offset.m_z = 0.0;
    ground->setAttack(15.0,&offset);
    ground->setAttackPreset(grMadein::Attack_Overwrite);
    //ground->m_attackInfo->m_preset = 4;
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
        //ground->setType(1);
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
        //ground->setType(1);
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
        //ground->setType(1);
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
        //ground->setType(1);
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
        //ground->setType(1);
    ground->initializeEntity();
    
    ground = grMadein::create(20, "AuraAttackPoint", "AuraAttackPoint",Heaps::StageInstance);
    addGround(ground);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    offset.m_x = 0.0;// Vec3f(0.0,0.0,0.0);
    offset.m_y = 0.0;// Vec3f(0.0,0.0,0.0);
    offset.m_z = 0.0;// Vec3f(0.0,0.0,0.0);
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
        //ground->setType(1);
        //ground->setType(1);
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
        //ground->setType(1);
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
        //ground->setType(1);
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
        //ground->setType(1);
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
        eventBoomerang.set(0.0,0.0);
        eventLegendDisappear.set(0.0,0.0);
        eventDropStage.set(0.0,0.0);
        eventRebuildStage.set(0.0,0.0);
        eventQuake.set(stagedata->event_frame_quake,stagedata->event_frame_quake);
        eventLaser.set(100.0,100.0);
        eventCameraRoll.set(100.0,500.0);
    //grTenganEvent event2;
    //grTenganEvent event14;
    //grTenganEvent event15;
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
        //ground->setType(1);
        laser->initializeEntity();
        laser->m_sceneModels[0]->SetPriorityDrawOpa(255);
        laser->m_sceneModels[0]->SetPriorityDrawXlu(255);
        //nw4r::g3d::ScnObj::SetPriorityDrawOpa(0);
        //nw4r::g3d::ScnObj::SetPriorityDrawXlu(0);
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
        //ground->setType(1);
        //enkei->initializeEntity();
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
        //enkei->initializeEntity();
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
        //ground->setType(1);
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
        //enkei->initializeEntity();
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
            stateWork = &m_stateFloorL;
            type = 0;
            break;
        case 7:
            floor = grTenganFloor::create(8, "StgTenganBrkYukaC", "grTenganFloorC");
            stateWork = &m_stateFloorC;
            type = 1;
            break;
        case 8:
            floor = grTenganFloor::create(7, "StgTenganBrkYukaR", "grTenganFloorR");
            stateWork = &m_stateFloorR;
            type = 2;
            break;
        case 9:
            floor = grTenganFloor::create(9, "StgTenganBrkYukaCL", "grTenganFloorCL");
            stateWork = &m_stateFloorL;
            type = 3;
            break;
        case 10:
            floor = grTenganFloor::create(10, "StgTenganBrkYukaCR", "grTenganFloorCR");
            stateWork = &m_stateFloorL;
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
        //enkei->initializeEntity();
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
            if (m_stateFloorC == 1) {
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

void stTengan::updateEvent(float deltaFrame) {
    //updateEvent(deltaFrame);
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

u32 stTengan::getZoneLightSetIndex(Vec2f *position) {
    if (position == NULL) {
        return 20;
    }
    if (position->m_x < -78.0f) {
        return 20;
    }
    if (position->m_x > 78.0f) {
        return 20;
    }
    if (position->m_y < -60.0f) {
        return 20;
    }
    if (position->m_y > -16.0f) {
        return 20;
    }
    return 21;
}
