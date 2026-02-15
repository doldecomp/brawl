#include <memory.h>
#include <types.h>
#include <ec/ec_mgr.h>
#include <ft/ft_manager.h>
#include <gf/gf_archive.h>
#include <gf/gf_3d_scene.h>
#include <gm/gm_lib.h>
#include <gm/gm_global.h>
#include <gr/gr_madein.h>
#include <mt/mt_matrix.h>
#include <mt/mt_spline.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/math/math_arithmetic.h>
#include <snd/snd_id.h>
#include <snd/snd_system.h>
#include <st/stage.h>
#include <st/st_melee.h>

#include <st_emblem/st_emblem.h>

stClassInfoImpl<Stages::Emblem, stEmblem> stEmblem::bss_loc_14;

stEmblem* stEmblem::create() {
    return new (Heaps::StageInstance) stEmblem;
}

stEmblem::stEmblem() : stMelee("stEmblem", Stages::Emblem) {
    memset(m_effects,0xff,0x38);
    memset(m_scene_ground_num,0,0x14);
    memset(m_scene_grounds,0,0x14);
    m_change_scene = 0;
    m_scene_num = 0;
    m_not_first_scene = false;
    m_prev_scene_num = 0;
    unk6f8 = 0.0f;
    memset(unk6fc,0,0x8);
    memset(unk704,0,0x8);
    m_unused = 0;
    ambientSnd = -1;
    unk718 = 0.0;
    unk71C = 0.0;
    unk720 = 0.0;
    unk724 = 0.0;
    unkSnd728 = -1;
    rockTimer = 0.0;
    rockFixTime = 0.0;
    unk710 = -1;
    unk734 = NULL;
    unk738 = NULL;
    m_isKemuriHigh = 1;
    m_lampEffTimer = 0.0;
    unk744 = 0;
    quakeSnd = -1;
    m_eventType = 0;
    unk800 = 0;
    unk804 = 0.0;
    unk808 = 0.0;
    resetChangeScene();

//    bool m_show_dogfight: 1;
    s32 ambientSnd;
    s32 unkSnd728;
    float rockTimer;
    float rockFixTime;
    char padding[0xC];
    s32 quakeSnd;
    u8 m_eventType;
//    StSeUtil::SeSeqInstance<2, 2> m_se_player;
//    StSeUtil::SeSeqInstance<2, 2> m_se_player2;
}

stEmblem::~stEmblem() {

}

bool stEmblem::loading() {
    return true;
}

void stEmblem::createObj() {
    gmGlobalModeMelee* mode_melee = g_GameGlobal->m_modeMelee;
    if (mode_melee->m_meleeInitData.m_gameMode == 7u) {
        //TODO: Fix m_eventId and m_playeMode
        if (mode_melee->m_meleeInitData.m_eventId == (s8)14) {
            m_eventType = 1;
        }
        if ((mode_melee->m_meleeInitData.m_eventId == (s8)40) and (mode_melee->m_meleeInitData.m_playeMode != false))
        {
            m_eventType = 2;
        }
    }
    testStageParamInit(m_secondaryFileData, 0xA);
    //testStageDataInit(m_fileData, 0x14, 0x38);
    grMadein* stageElement;
    for (s16 i = 0; i < 9; i++) {
        stageElement = grMadein::create(i, "", "Tsunagi", Heaps::StageInstance);
        if (stageElement) {
            addGround(stageElement);
            stageElement->startup(m_secondaryFileData,false,gfSceneRoot::Layer_Ground);
            stageElement->setStageData(m_stageData);
            stageElement->m_sceneModels[0]->SetPriorityDrawXlu(200);
            stageElement->m_sceneModels[0]->SetPriorityDrawOpa(200);
        }
    }
    for (u8 i = 0; i < 7; i++) {
        stageElement = grMadein::create(0, "", "NodeOnlyCollision", Heaps::StageInstance);
        if (stageElement) {
            addGround(stageElement);
            stageElement->startup(m_fileData,false,gfSceneRoot::Layer_Ground);
            stageElement->setStageData(m_stageData);
            createCollision(m_secondaryFileData,i,stageElement);
        }
    }
    initCameraParam();
    nw4r::g3d::ResFile posData(m_secondaryFileData->getData(Data_Type_Model, 10, 0xfffe));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        // if no stgPos model in pac, use defaults
        createStagePositions();
    }
    createWind2ndOnly();    
    nw4r::g3d::ResFileData* scnData;
        scnData = static_cast<nw4r::g3d::ResFileData*>(m_secondaryFileData->getData(Data_Type_Scene, 0, 0xfffe));
        registScnAnim(scnData, 0);
    //m_wind2ndTrigger->setAreaSleep(1);
    for (size_t i = 0; i < getGroundNum(); i++) {
        static_cast<grMadein*>(getGround(i))->initializeEntity();
    }
    for (size_t i = 0; i < 7; i++) {
        static_cast<grMadein*>(getGround(i+9))->startEntityAutoLoop();
        static_cast<grMadein*>(getGround(i+9))->setEnableCollisionStatus(false);
    }
    //static_cast<grMadein*>(getGround(3))->startEntityAutoLoop();
    m_scene_ground_num[0] = 1;
    m_scene_ground_num[1] = 5;
    m_scene_ground_num[2] = 2;
    for (int i = 0; i < 14; i++) {
        m_effects[i] = -1;
    }
    m_curr_scene_effect.set(0.0f, 0.0f);
    m_scene_lifecycle.set(0.0f, 0.0f);
    event4.set(200.0f, 400.0f);
    m_curr_scene.set(100.0f, 200.0f);
    event2.set(300.0f, 600.0f);
    eventArray[0].set(30.0f, 60.0f);
    eventArray[1].set(30.0f, 60.0f);
    m_scene_lifecycle.start();
    m_se_player.registId(data_loc_11A0, SndIDTableSize);
    m_se_player2.registId(data_loc_11A0, SndIDTableSize);
    m_se_player.registSeq(0, data_loc_0, SndSeqTable1Size, Heaps::StageInstance);
    m_se_player2.registSeq(0, data_loc_20, SndSeqTable1Size, Heaps::StageInstance);
    loadStageAttrParam(m_secondaryFileData, 0x1E);
    initPosPokeTrainer(6, 0);
    createObjPokeTrainer(m_secondaryFileData, 100, "PokeTrainer00", m_pokeTrainerPos, 0);
    createObjPokeTrainer(m_secondaryFileData, 101, "PokeTrainer01", m_pokeTrainerPos+2, 0);
    createObjPokeTrainer(m_secondaryFileData, 102, "PokeTrainer02", m_pokeTrainerPos+4, 0);
    createObjPokeTrainer(m_secondaryFileData, 103, "PokeTrainer03", m_pokeTrainerPos+6, 0);
    createObjPokeTrainer(m_secondaryFileData, 104, "PokeTrainer04", m_pokeTrainerPos+8, 0);
    createObjPokeTrainer(m_secondaryFileData, 105, "PokeTrainer05", m_pokeTrainerPos+10, 0);
}

void stEmblem::setSceneCollision() {
    for (size_t i = 0; i < 6; i++) {
        static_cast<grMadein*>(getGround(i+9))->setEnableCollisionStatus(false);
    }
    switch (m_scene_num) {
        case 0:
            static_cast<grMadein*>(getGround(9))->setEnableCollisionStatus(true);
            break;
        case 1:
            static_cast<grMadein*>(getGround(10))->setEnableCollisionStatus(true);
            static_cast<grMadein*>(getGround(11))->setEnableCollisionStatus(true);
            static_cast<grMadein*>(getGround(12))->setEnableCollisionStatus(true);
            break;
        case 2:
            unk734 = createCollision(m_secondaryFileData,7,m_scene_grounds[1]);
            unk738 = createCollision(m_secondaryFileData,8,m_scene_grounds[0]);
            break;
    }
}

grMadein* stEmblem::createSceneGround(s16 index) {
    grMadein* stageElement = grMadein::create(index, "", "SceneGround", Heaps::StageInstance);
    if (stageElement == NULL) {
        return NULL;
    } else {
        addGround(stageElement);
        stageElement->startup(unk1A8,false,gfSceneRoot::Layer_Ground);
        stageElement->setStageData(m_stageData);
        if (m_scene_num == 1 and index == 1) {
            Vec3f leftPosTop;// = Vec3f(-30.0,40.0,0.0);
            leftPosTop.m_x = -30.0;
            leftPosTop.m_y = 40.0;
            leftPosTop.m_z = 0.0;
            Vec3f leftPosBot;// = Vec3f(-30.0,0.0,0.0);
            leftPosBot.m_x = -30.0;
            leftPosBot.m_y = 0.0;
            leftPosBot.m_z = 0.0;
            stageElement->setHitPoint(8.0f,&leftPosTop,&leftPosBot,1,0);
        }
        if (m_scene_num == 1 and index == 3) {
            Vec3f leftPosTop;// = Vec3f(50.0,40.0,0.0);
            leftPosTop.m_x = 50.0;
            leftPosTop.m_y = 40.0;
            leftPosTop.m_z = 0.0;
            Vec3f leftPosBot;// = Vec3f(50.0,00.0,0.0);
            leftPosBot.m_x = 50.0;
            leftPosBot.m_y = 0.0;
            leftPosBot.m_z = 0.0;
            stageElement->setHitPoint(8.0f,&leftPosTop,&leftPosBot,1,0);
        }
        stageElement->initializeEntity();
        stageElement->startEntityAutoLoop();
        m_scene_grounds[index] = stageElement;
    }
    return stageElement;
}

void stEmblem::setChangeSceneNumber(s32 n) {
    m_scene_num = n;
}

bool stEmblem::checkChangeScene() {
    return m_change_scene;
}

void stEmblem::resetChangeScene() {
    m_change_scene = false;
}

void stEmblem::startScene() {
    if (m_eventType != 0) {
        switch (m_scene_num) {
            case 0:
            case 1:
            case 2:
                event2.set(1620.0f, 1620.0f);
                break;
            default:
                break;
        }
    } else {
        switch (m_scene_num) {
            case 0:
            case 1:
            case 2:
                event2.set(2400.0f, 2400.0f);
                break;
            default:
                break;
        }
    }
    event2.start();
    setSceneCollision();
    //m_curr_scene_effect.start();
    if (m_scene_num == 1) {
        m_scene_grounds[2]->endEntity();
        m_scene_grounds[4]->endEntity();
        //m_scene_grounds[3]->endEntity();
        unk704[1] = 0;
        unk704[0] = 0;
        unk6fc[1] = 70;
        unk6fc[0] = 70;
    }
    //m_unused = 0;
}

void stEmblem::moveGround(float param3,bool isStartHigh, Vec3f* pos) {
    Vec3f moveSpline[4];
    if (isStartHigh) {
        moveSpline[0].m_x = 0.0;
        moveSpline[0].m_y = 0.0;
        moveSpline[0].m_z = 0.0;
        moveSpline[1].m_x = 0.0;
        moveSpline[1].m_y = 0.0;
        moveSpline[1].m_z = 0.0;
        moveSpline[2].m_x = 0.0;
        moveSpline[2].m_y = 0.0;
        moveSpline[2].m_z = 0.0;
        moveSpline[3].m_x = 0.0;
        moveSpline[3].m_y = -100.0;
        moveSpline[3].m_z = 0.0;
    } else {
        moveSpline[0].m_x = 0.0;
        moveSpline[0].m_y = -100.0;
        moveSpline[0].m_z = 0.0;
        moveSpline[1].m_x = 0.0;
        moveSpline[1].m_y = 0.0;
        moveSpline[1].m_z = 0.0;
        moveSpline[2].m_x = 0.0;
        moveSpline[2].m_y = 0.0;
        moveSpline[2].m_z = 0.0;
        moveSpline[3].m_x = 0.0;
        moveSpline[3].m_y = 0.0;
        moveSpline[3].m_z = 0.0;
    }
    Vec3f splinePos;
    mtBezierCurve(param3, moveSpline, &splinePos);
    pos->m_x = splinePos.m_x;
    pos->m_y = splinePos.m_y;
    pos->m_z = splinePos.m_z;
}

void stEmblem::updateScene(float deltaFrame) {
    nw4r::g3d::ResFileData* scn;
    switch(m_scene_lifecycle.getPhase()) {
        case 0: // Ready to start next scene
            if (unk1A8 == NULL) {
                break;
            }
                grMadein* scene_ground;
                m_scene_grounds[4] = 0;
                m_scene_grounds[3] = 0;
                m_scene_grounds[2] = 0;
                m_scene_grounds[1] = 0;
                m_scene_grounds[0] = 0;
                for (s32 i = 0; i < m_scene_ground_num[m_scene_num]; i++) {
                    createSceneGround(i);
                }
                stageParamChange();
                setSoundParameters(m_stageParam);
                clearCameraParam();
                initCameraParam();
                nw4r::g3d::ResFile posData(m_secondaryFileData->getData(Data_Type_Model, m_scene_num+30, 0xfffe));
                if (posData.ptr()) {
                    nw4r::g3d::ResFile copyPosData = posData;
                    m_stagePositions->loadPositionData(&copyPosData);
                }
                updateStagePositions();
                stTrigger* wind2ndTrigger = m_wind2ndTrigger;
                if (wind2ndTrigger) {
                    if (m_scene_num == 0) {
                        wind2ndTrigger->setAreaSleep(false);
                    } else {
                        wind2ndTrigger->setAreaSleep(true);
                    }
                }
                u8 temp_i = (m_scene_num &0x7f) << 1;
                m_pokeTrainerPosIndex = temp_i;
                g_ftManager->notifyReplacePokeTrainer(temp_i);
                unk800 = 0;
                unk804 = 90.0;
                startScene();
                if (m_not_first_scene == true) {
                    static_cast<grMadein*>(getGround(m_prev_scene_num*3+1))->endEntity();
                    static_cast<grMadein*>(getGround(m_prev_scene_num*3+2))->startEntity();
                    g_gfSceneRoot->removeResAnmScn();
                    scn = (nw4r::g3d::ResFileData*)
                        m_secondaryFileData->getData(Data_Type_Scene, m_prev_scene_num*3 + 2, 0xFFFE);
                    registScnAnim(scn, 0);
                    //static_cast<grMadein*>(getGround(1))->endEntity();
                    //static_cast<grMadein*>(getGround(2))->startEntity();
                    m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
                    //playSeBasic(snd_se_stage_Starfox_warp_out, 0.0f);
                    unk6f8 = 0.0;
                } else {
                    m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 2);
                    scn = (nw4r::g3d::ResFileData*)
                        unk1A8->getData(Data_Type_Scene, 0, 0xFFFE);
                    registScnAnim(scn, 0);
                    m_curr_scene_effect.start();
                    unk6f8 = 1.0;
            //    }
            }
        case 1:
            Vec3f groundMovePos;
            moveGround(unk6f8,false, &groundMovePos);
            for (int i = 0;i<m_scene_ground_num[m_scene_num];i++) {
                m_scene_grounds[i]->setPos(&groundMovePos);
            }
            for (u32 i = 0;i<6;i++) {
                static_cast<grGimmick*>(getGround(i+9))->setPos(&groundMovePos);
            }
            moveGround(unk6f8,true, &groundMovePos);
            static_cast<grGimmick*>(getGround(15))->setPos(&groundMovePos);
            unk6f8 += deltaFrame/100.0f;
            if (unk6f8 >= 1.0f) {
                unk6f8 = 1.0f;
            }
            if (static_cast<grMadein*>(getGround(m_prev_scene_num*3+2))->isEndEntity() == 1u) {
                static_cast<grMadein*>(getGround(m_prev_scene_num*3+2))->endEntity();
                g_gfSceneRoot->removeResAnmScn();
                scn = (nw4r::g3d::ResFileData*)
                    unk1A8->getData(Data_Type_Scene, 0, 0xFFFE);
                registScnAnim(scn, 0);
                m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
                getGround(15)->setEnableCollisionStatus(false);
                m_curr_scene_effect.start();
            }
            break;
        case 2:
            Vec3f groundEnterPos;
            moveGround(unk6f8,false, &groundEnterPos);
            for (int i = 0;i<m_scene_ground_num[m_scene_num];i++) {
                m_scene_grounds[i]->setPos(&groundEnterPos);
            }
            for (u32 i = 0;i<6;i++) {
                static_cast<grGimmick*>(getGround(i+9))->setPos(&groundEnterPos);
            }
            moveGround(unk6f8,true, &groundEnterPos);
            static_cast<grGimmick*>(getGround(15))->setPos(&groundEnterPos);
            unk6f8 += deltaFrame/100.0f;
            if (unk6f8 >= 1.0f) {
                unk6f8 = 1.0f;
            }
            if (event2.isReadyEnd() == true) {
                event2.end();
                event4.start();
                m_curr_scene.start();
                unk710 = playSeBasic(snd_se_stage_Emblem_low_rumble,0.0);
                m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
                m_curr_scene_effect.end();
                s32 i = 0;
                s32 arrSz = sizeof(m_effects)/sizeof(m_effects[0]);
                for (i = 0; i < arrSz;i++) {
                    if (m_effects[i] != -1) {
                        g_ecMgr->endEffect(m_effects[i]);
                    }
                }
                if (m_scene_num == 1) {
                    m_scene_grounds[1]->deleteHitPoint();
                    m_scene_grounds[3]->deleteHitPoint();
                }
                //static_cast<grMadein*>(getGround(0))->endEntity();
                //static_cast<grMadein*>(getGround(1))->startEntityAutoLoop();
                
            }
            break;
        case 3: // Scene is in progress, waiting for timer to run out
            if (m_curr_scene.isReadyEnd() == 1u) {
                m_curr_scene.end();
                m_prev_scene_num = m_scene_num;
                static_cast<grMadein*>(getGround(m_scene_num*3))->startEntity();
                m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
                //m_not_first_scene = true;      
                g_gfSceneRoot->removeResAnmScn();
                scn = (nw4r::g3d::ResFileData*)
                    m_secondaryFileData->getData(Data_Type_Scene, m_prev_scene_num*3, 0xFFFE);
                registScnAnim(scn, 0);
                unk6f8 = 0.0;
                playSeBasic(snd_se_stage_Emblem_sequence_move, 0.0f);
                stopSeBasic(ambientSnd, 2.0f);
                ambientSnd = -1;
                static_cast<grMadein*>(getGround(15))->setEnableCollisionStatus(true);
            }
            break;
        case 4: // Scene transition (warp) in progress?
            Vec3f groundLeavePos;
            moveGround(unk6f8,true, &groundLeavePos);
            for (int i = 0;i<m_scene_ground_num[m_scene_num];i++) {
                m_scene_grounds[i]->setPos(&groundLeavePos);
            }
            for (size_t i = 0;i<6;i++) {
                static_cast<grGimmick*>(getGround(i+9))->setPos(&groundLeavePos);
            }
            moveGround(unk6f8,false, &groundLeavePos);
            static_cast<grGimmick*>(getGround(15))->setPos(&groundLeavePos);
            unk6f8 += deltaFrame/100.0f;
            if (unk6f8 >= 1.0f) {
                unk6f8 = 1.0f;
            }
            if (static_cast<grMadein*>(getGround(m_prev_scene_num*3))->isEndEntity() == 1u) {
                static_cast<grMadein*>(getGround(m_prev_scene_num*3))->endEntity();
                static_cast<grMadein*>(getGround(m_prev_scene_num*3+1))->startEntityAutoLoop();
                m_not_first_scene = true;
                m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
                g_gfSceneRoot->removeResAnmScn();
                scn = (nw4r::g3d::ResFileData*)
                    m_secondaryFileData->getData(Data_Type_Scene, m_prev_scene_num*3 + 1, 0xFFFE);
                registScnAnim(scn, 0);
                for (u32 i = 0; i < 6; i++) {
                    getGround(i+9)->setEnableCollisionStatus(false);
                }
                if (m_scene_num == 2) {
                    m_scene_grounds[0]->setEnableCollisionStatus(false);
                    m_scene_grounds[1]->setEnableCollisionStatus(false);
                }
            }
            break;
        case 5: // Teardown phase for scene effects and grounds
            if (quakeSnd != -1) {
                stopSeBasic(quakeSnd,1.0);
                quakeSnd = -1;
            }
            m_curr_scene_effect.end();
            // TODO: figure out how to pass 1 to the destructors insead of -1
            if (unk734 != NULL) {
                delete(unk734);
                //unk734->~grCollision();
                unk734 = NULL;
            }
            if (unk738 != NULL) {
                delete(unk738);
                //unk738->~grCollision();
                unk738 = NULL;
            }
            s32 i = 0;
            s32 arrSz = sizeof(m_effects)/sizeof(m_effects[0]);
            //u32* m_effects_ptr = reinterpret_cast<u32*>(this);
            for (i = 0; i < arrSz;i++) {
                if (m_effects[i] != -1) {
                    g_ecMgr->killEffect(m_effects[i], 1, 1);
                    m_effects[i] = -1;
                }
            }
            s32 j = 0;
            //grMadein** m_scene_grounds_ptr = reinterpret_cast<grMadein**>(this);
            for (j = 0; j < m_scene_ground_num[m_scene_num]; j++) {
                if (m_scene_grounds[j]) {
                    removeGround(m_scene_grounds[j]);
                    (m_scene_grounds[j])->preExit();
                    (m_scene_grounds[j])->exit();
                }
            }
            g_gfSceneRoot->removeResAnmScn();
            scn = (nw4r::g3d::ResFileData*)
                    m_secondaryFileData->getData(Data_Type_Scene, 0, 0xFFFE);
                registScnAnim(scn, 0);
            m_scene_lifecycle.setPhase(m_scene_lifecycle.getPhase() + 1);
            break;
        case 6: // Indicate to user that the scene is ready to change again
            m_change_scene = true;
            m_isKemuriHigh = false;
            m_scene_lifecycle.end();
            m_scene_lifecycle.start();
            break;
        default:
            break;
    }
}

void stEmblem::updateScene00(float deltaFrame) {
    switch (m_curr_scene_effect.getPhase()) {
        case 0:
            for (int i = 0; i < 14; i++) {
            m_effects[i] = -1;
            }
            if (m_isKemuriHigh == true) {
                m_effects[0] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_kemuri_b_hi);
                m_effects[1] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_kemuri_c_hi);
            } else {
                m_effects[0] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_kemuri_b);
                m_effects[1] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_kemuri_c);
            }
            m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
            ambientSnd = -1;
            unk720 = 0.0;
            unk724 = 0.0;
            float fVar1 = (randf()*100.0f);
            float fVar2 = 50.0f-fVar1;
            unk71C = fVar2 + 130.0f;
            unkSnd728 = -1;
            
            break;
        default:
            break;
    }
    unk724+=deltaFrame;
    if(unk724 >= unk71C and unk720 == 0.0f) {
        m_effects[2] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_ishi);
        unk720 = -1.0;
        u32 rand = randi(5);
        if (rand >= 4) {
            rand = 4;
        }
        unkSnd728 = playSeBasic((SndID)(rand + snd_se_stage_Emblem_touseki_01),unk720);
        float fVar1 = (randf()*100.0f);
        float fVar2 = 50.0f - fVar1;
        unk724 = 0.0;
        unk71C = fVar2 + 130.0f;
    }
    unk720+=0.05f;
    if (unk720 >= 0.0f) {
        unk720 = 0.0;
    }
    setSePan(unkSnd728,unk720);
    if (ambientSnd == -1) {
        ambientSnd = playSeBasic(snd_se_stage_Emblem_out_amb,0.0);
    }
    if (m_isDevil == true) {
        setCameraLimitRange(-110.0,3.4028235e38,110.0,-3.4028235e38);
    } else {
        resetCameraLimitRange();
    }
}

char* const effectStrings[10] = {
    "eff01",
    "eff02",
    "eff03",
    "eff04",
    "eff05",
    "eff06",
    "eff07",
    "eff08",
    "eff09",
    "eff10"
};

const int statueGrounds[2] = {
    1,3
};

void stEmblem::updateScene01(float deltaFrame) {
    char* effectNames[10];
    float fVar1 = unk808 - deltaFrame;
    unk808 = fVar1;
    if (fVar1 < 0.0f) {
        unk808 = 0.0f;
    }
    switch (m_curr_scene_effect.getPhase()) {
        case 0:
            for (int i = 0; i < 14; i++) {
            m_effects[i] = -1;
            }
            m_lampEffTimer = 0.0;
            unk744 = 0;
            m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
            break;
        case 1:
            //effectNames = &effectStrings[1];
            effectNames[0] = effectStrings[0];
            effectNames[1] = effectStrings[1];
            effectNames[2] = effectStrings[2];
            effectNames[3] = effectStrings[3];
            effectNames[4] = effectStrings[4];
            effectNames[5] = effectStrings[5];
            effectNames[6] = effectStrings[6];
            effectNames[7] = effectStrings[7];
            effectNames[8] = effectStrings[8];
            effectNames[9] = effectStrings[9];
            if (m_lampEffTimer >= 10.0f) {
                u32 rand = randi(3);
                if (rand >= 2) {
                    rand = 2;
                }
                switch(rand) {
                    default:
                    case 0:
                        m_effects[unk744] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_a);
                        break;
                    case 1:
                        m_effects[unk744] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_b);
                        break;
                    case 2:
                    //case 3:
                        m_effects[unk744] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_c);
                        break;
                }
                rand = randi(3);
                if (rand >= 2) {
                    rand = 2;
                }
                // TODO: load from 0x68c[unk744+5] 0x6A0[unk744]
                switch(rand) {
                    default:
                    case 0:
                        m_effects[unk744+5] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_a);
                        break;
                    case 1:
                        m_effects[unk744+5] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_b);
                        break;
                    case 2:
                        m_effects[unk744+5] = g_ecMgr->setEffect(ef_ptc_stg_emblem_01_lamp_fire_c);
                        break;
                }
                g_ecMgr->setParent(m_effects[unk744],m_scene_grounds[0]->m_sceneModels[0],effectNames[unk744],0);
                //u32 temp1 = unk744 + 5;
                g_ecMgr->setParent(m_effects[unk744],m_scene_grounds[0]->m_sceneModels[0],effectNames[unk744+5],0);
                int iVar1 = unk744 + 1;
                unk744 = iVar1;
                if (iVar1 >= 5) {
                    m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
                }
                m_lampEffTimer = 0.0f;
            } else {
                m_lampEffTimer += deltaFrame;
            }
            //m_lampEffTimer = 0.0;
            //unk744 = 0;
            break;
        default:
            break;
    }
    int locald8[2];
    locald8[0] = statueGrounds[0];
    locald8[1] = statueGrounds[1];
    //int iVar2 = 0
    for (int i = 0; i < 2; i++) {
        switch(unk704[i]) {
            case 0:
                if (m_scene_grounds[locald8[i]]->isHit()) {
                if (unk808 == 0.0f) {
                    if (i == 0) {
                        m_effects[12] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_zou_damage_l);
                        g_ecMgr->setParent(m_effects[12],m_scene_grounds[0]->m_sceneModels[0],"StgEmblem01ZouANormal",0);
                    } else {
                        m_effects[13] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_zou_damage_r);
                        g_ecMgr->setParent(m_effects[13],m_scene_grounds[0]->m_sceneModels[0],"StgEmblem01ZouBNormal",0);
                    }
                    unk808 = 10.0f + (5.0f*randf());
                }
                    //m_scene_grounds[locald8[i]]
                    int damage = m_scene_grounds[locald8[i]]->getLastDamageTaken();
                    int iVar = unk6fc[i] -= damage;
                    unk6fc[i] = iVar;
                    if (iVar < 0) {
                        unk6fc[i] = 0;
                    }
                    
                    if (unk6fc[i] == 0) {
                        m_scene_grounds[locald8[i]]->endEntity();
                        getGround(i+11)->setEnableCollisionStatus(false);
                        m_scene_grounds[locald8[i]+1]->startEntity();
                        unk704[i]++;
                        eventArray[i].end();
                        if (i == 0) {
                            m_effects[11] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_zoucrash_l);
                            g_ecMgr->setParent(m_effects[11],m_scene_grounds[0]->m_sceneModels[0],"StgEmblem01ZouAClash",0);
                        } else {
                            m_effects[10] = g_ecMgr->setEffect(ef_ptc_stg_emblem_00_zoucrash_r);
                            g_ecMgr->setParent(m_effects[10],m_scene_grounds[0]->m_sceneModels[0],"StgEmblem01ZouBClash",0);
                        }
                        Vec3f quake;// = Vec3f(0.0,0.0,0.0);
                        quake.m_x = 0.0f;
                        quake.m_y = 0.0f;
                        quake.m_z = 0.0f;
                        cmReqQuake(cmQuake::Amplitude_Large,&quake);
                    } else {
                        eventArray[i].start();
                        playSeBasic(snd_se_stage_Emblem_statue_hit,0.0f);
                    }
                }
                break;
            case 1:
                if (i == 0) {
                    //m_se_player.playFrame(m_scene_grounds[0]->getEntityFrame,0);
                    m_se_player.playFrame(0, m_scene_grounds[locald8[i]+1]->getEntityFrame());
                } else {
                    m_se_player2.playFrame(0, m_scene_grounds[locald8[i]+1]->getEntityFrame());
                }
                if(m_scene_grounds[locald8[i]+1]->isEndEntity() == true) {
                    m_scene_grounds[locald8[i]+1]->endEntity();
                    unk704[i]++;
                }
            }
            if (eventArray[i].isEvent()) {
                Vec3f groundPos;
                float one = 1.0f;
                float fVar1 = (one*randf());
                groundPos.m_x = (0.5f-fVar1);
                fVar1 = (one*randf());
                groundPos.m_y = (0.5f-fVar1);
                fVar1 = (one*randf());
                groundPos.m_z = (0.5f-fVar1);
                m_scene_grounds[locald8[i+1]]->setPos(&groundPos);
                if (eventArray[i].isReadyEnd()) {
                    Vec3f pos;
                    pos.m_x = 0.0f;
                    pos.m_y = 0.0f;
                    pos.m_z = 0.0f;
                    m_scene_grounds[locald8[i+1]]->setPos(&pos);
                    eventArray[i].end();
                }
        }
    }
    if (m_isDevil == true) {
        setCameraLimitRange(-110.0f,200.0f,110.0f,0.0f);
    } else {
        resetCameraLimitRange();
    }
}

void stEmblem::updateScene02(float deltaFrame) {
    switch (m_curr_scene_effect.getPhase()) {
        case 0:
            m_effects[0] = -1;
            m_effects[1] = -1;
            m_effects[2] = -1;
            m_effects[3] = -1;
            m_effects[4] = -1;
            m_effects[5] = -1;
            m_effects[6] = -1;
            m_effects[7] = -1;
            m_effects[8] = -1;
            m_effects[9] = -1;
            m_effects[10] = -1;
            m_effects[11] = -1;
            m_effects[12] = -1;
            m_effects[13] = -1;
            m_effects[0] = g_ecMgr->setEffect(ef_ptc_stg_emblem_02_kemuri);
            m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
            ambientSnd = playSeBasic(snd_se_stage_Emblem_under_amb,0.0f);
            rockTimer = 0.0f;
            float fVar1 = randf() * 180.0f;
            rockFixTime = fVar1 + 300.0f;
            break;
        case 1:
            rockTimer += deltaFrame;
            if (rockTimer > rockFixTime) {
                m_scene_grounds[1]->setMotion(1);
                m_scene_grounds[1]->startEntity();
                m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
                rockTimer = 0.0f;
                rockFixTime = 180.0;
            }
            break;
        case 2:
            rockTimer += deltaFrame;
            if (rockTimer > rockFixTime) {
                quakeSnd = playSeBasic(snd_se_stage_Emblem_quake,0.0f);
                m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
                rockTimer = 0.0f;
                rockFixTime = 1650.0;
            }
            rockFixTime;
            break;
        case 3:
            rockTimer += deltaFrame;
            if (rockTimer > rockFixTime) {
                if (quakeSnd != -1) {
                    stopSeBasic(quakeSnd,60.0f);
                    quakeSnd = -1;
                }
                m_curr_scene_effect.setPhase(m_curr_scene_effect.getPhase() + 1);
            }
            break;
        default:
            break;
    }
    if (m_isDevil == true) {
        setCameraLimitRange(-110.0f,3.4028235e38,110.0f,-3.4028235e38);
    } else {
        resetCameraLimitRange();
    }
}

void stEmblem::update(float deltaFrame) {
    g_ecMgr->setDrawPrio(1);
    updateScene(deltaFrame);
    if (m_curr_scene_effect.isEvent() == 1u) {
        //if (m_show_dogfight || m_scene_num != SCENE_SPACE) {
        //    m_se_player.playFrame(m_scene_num, m_scene_grounds[0]->getEntityFrame());
        //}
        switch (m_scene_num) {
            case 0:
                updateScene00(deltaFrame);
                break;
            case 1:
                updateScene01(deltaFrame);
                break;
            case 2:
                updateScene02(deltaFrame);
                break;
            default:
                break;
        }
    }
    if (event4.isEvent()) {
        if (event4.isReadyEnd() == 1u) {
            cmRemoveQuake(1);
            stopSeBasic(unk710,2.0f);
            event4.end();
        } else {
            if(event4.m_manualFramesLeft == 0.0f) {
                Vec3f quake;// = Vec3f(0.0,0.0,0.0);
                quake.m_x = 0.0;
                quake.m_y = 0.0;
                quake.m_z = 0.0;
                cmReqQuake(cmQuake::Amplitude_Middle,&quake);
            }
            event4.m_manualFramesLeft += 1.0f;
            if (event4.m_manualFramesLeft >= 10.0f) {
                event4.m_manualFramesLeft = 0.0f;
            }
        }
    }
//    static_cast<grGimmick*>(getGround(3))->setRot(&m_slope_rotate);
    if (m_eventType != 1 || m_scene_num != 2) {
        event2.update(deltaFrame);
    }
    m_curr_scene_effect.update(deltaFrame);
    event4.update(deltaFrame);
    m_curr_scene.update(deltaFrame);
    eventArray[0].update(deltaFrame);
    eventArray[1].update(deltaFrame);
    g_ecMgr->setDrawPrio(-1);
    updateSE(deltaFrame);
}

inline float FSub(float param1, float param2) {
    return param1 - param2;
}

void stEmblem::updateSE(float deltaFrame) {
    float fVar1 = unk804 -= deltaFrame;
    if (fVar1 < 0.0f) {
        unk804 = 0.0f;
    }
    if (unk800 == (s8)1) {
         return;
    }
    if (unk800 >= (s8)0x1) {
         return;
    }
    if (unk800 < (s8)0x0) {
         return;
    }
    float fVar4;
    float fVar5;
    switch(m_scene_num) {
        case 0:
            fVar4 = 25.0f;
            fVar5 = 0.0f;
            break;
        case 1:
            fVar4 = 0.0f;
            fVar5 = 50.0f;
            break;
        case 2:
            fVar4 = 50.0f;
            fVar5 = 25.0f;
            break;
        default:
            return;
    }
    fVar1 = 1.0f - unk804/90.0f;
    float fVar2;
    fVar1 = nw4r::math::FSelect(FSub(fVar1,0.0f),fVar1,0.0f);
    fVar2 = nw4r::math::FSelect(FSub(fVar1,1.0f),1.0f,fVar1);
    if (fVar2 == 1.0f) {
        unk800++;
    }
    float fVar6 = fVar2 * (fVar5 - fVar4);
    g_sndSystem->setEffectVol(0,1,(fVar4 + fVar6) * 0.01f);
}

bool stEmblem::isEventEnd(int param1, int* eventState, int* eventDecision) {
    if (m_eventType == 1) {
        if (m_scene_num != 2) {
            return 0;
        }
    } else {
        *eventState = m_scene_num;
    }
    return 1;
}

GXColor stEmblem::getFinalTechniqColor() {
    nw4r::ut::Color color = nw4r::ut::Color(0x14000496);
    if (m_scene_num == 0) return color;
    return nw4r::ut::Color(0x1400047d);
}